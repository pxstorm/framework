#include "pxs/core/directives.h"
#include "pxs/graphics/shader_builder.h"

#include <cstring>
#include <cstdio>

pxs::ShaderBuilder::ShaderBuilder() {
    this->glProgram = GL_NULL;
}

pxs::ShaderBuilder &pxs::ShaderBuilder::attach(const char *path, pxs::Shader::Type type) {
    if(glProgram == GL_NULL) {
        glProgram = glCreateProgram();
        EXPECT(glProgram != GL_NULL, "Method glCreateProgram return null.");
    }

    ShaderSource source = readFile(path);
    GLuint shader = compile(source, type);
    glAttachShader(glProgram, shader);

    return *this;
}

pxs::ShaderBuilder &pxs::ShaderBuilder::detachAll() {
    for(GLuint shader : glShaders) {
        glDeleteShader(shader);
    }

    glShaders.clear();

    return *this;
}


pxs::Shader::ptr pxs::ShaderBuilder::build() {
    EXPECT(glProgram != GL_NULL, "Attach sources before building shader.");

    // Build shader program from attached shader sources
    link();

    Shader::ptr result = std::make_shared<Shader>(glProgram);

    // We cannot call dispose method, because shader class will manage
    // OpenGL object instance and dispose when no more needed.
    glProgram = GL_NULL;

    // We can detach shader, because they'll be destroyed only when
    // all program that they belongs to are destroyed.
    detachAll();

    return result;
}

pxs::ShaderBuilder::~ShaderBuilder() {
    dispose();
}

pxs::ShaderBuilder::ShaderSource pxs::ShaderBuilder::readFile(const char *path) {
    ShaderSource source;

    FILE* file = fopen(path, "r");
    EXPECT(file != NULL, "Cannot open file '%s'.", path);

    // Set cursor at the end of file to read length
    fseek(file, 0, SEEK_END);
    source.length = ftell(file);

    // Set cursor back at the beginning and read whole file
    fseek(file, 0, SEEK_SET);
    source.content = new char[source.length + 1];
    size_t status = fread(source.content, (size_t) source.length, 1, file);
    EXPECT(status == 1, "Error reading content of the file '%s' (%u bytes).", path, source.length);

    fclose(file);
    return source;
}

GLuint pxs::ShaderBuilder::compile(const ShaderSource source, pxs::Shader::Type type) {
    EXPECT(source.length > 0, "Empty shader source given.");

    // Create shader and copy source
    GLuint shader = glCreateShader(type);
    EXPECT(shader != GL_NULL, "Method glCreateShader return null.");

    glShaderSource(shader, 1, (const GLchar* const*) &(source.content), &(source.length));

    // Compile and validate
    GLint param;
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
    if (param != GL_TRUE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param);
        std::vector<GLchar> log((unsigned) param);

        glGetShaderInfoLog(shader, param, NULL, &(log[0]));
        UNEXPECTED("Shader compilation error: %s.", log);
    }

    glShaders.push_back(shader);
    return shader;
}

void pxs::ShaderBuilder::link() {
    GLint param;

    // Link
    glLinkProgram(glProgram);
    glGetProgramiv(glProgram, GL_LINK_STATUS, &param);

    // Validate
    if (param == GL_TRUE) {
        glValidateProgram(glProgram);
        glGetProgramiv(glProgram, GL_VALIDATE_STATUS, &param);
    }

    // Check for errors
    if (param != GL_TRUE) {
        glGetProgramiv(glProgram, GL_INFO_LOG_LENGTH, &param);
        std::vector<GLchar> log((unsigned) param);

        glGetProgramInfoLog(glProgram, param, NULL, &(log[0]));
        UNEXPECTED("Linking shader program error: %s.", log);
    }
}

void pxs::ShaderBuilder::dispose() {
    detachAll();

    if(glProgram != GL_NULL) {
        UNEXPECTED("Redundant usage of ShaderBuilder, compiled shader(s) is not used.");
        glDeleteProgram(glProgram);
        glProgram = GL_NULL;
    }
}