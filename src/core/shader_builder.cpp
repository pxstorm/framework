#include "core/shader_builder.h"

#include <cassert>
#include <cstring>
#include <cstdio>

pxs::ShaderBuilder::ShaderBuilder() {
    this->glProgram = nullptr;
}

pxs::ShaderBuilder &pxs::ShaderBuilder::attach(const char *path, pxs::Shader::Type type) {
    if(glProgram == nullptr) {
        glProgram = glCreateProgram();
        assert(glProgram != nullptr && "Method glCreateProgram return null.");
    }

    // FIXME: Read file source
    const GLchar* source = nullptr;

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


ptr<Shader> pxs::ShaderBuilder::build() {
    assert(glProgram != nullptr && "Attach sources before building shader.");

    // Build shader program from attached shader sources
    link();

    ptr<Shader> result = std::make_shared<Shader>(glProgram);

    // We cannot call dispose method, because shader class will manage
    // OpenGL object instance and dispose when no more needed
    glProgram = nullptr;

    // We can detach shader, because they'll be destroyed only when
    // all program that they belongs to are destroyed
    detachAll();

    return result;
}

pxs::ShaderBuilder::~ShaderBuilder() {
    dispose();
}

GLuint pxs::ShaderBuilder::compile(const GLchar* source, pxs::Shader::Type type) {
    GLint length = (GLint) strlen(source);
    const GLchar* content = source;
    assert(length > 0 && "Empty shader source given.");

    // Create shader and copy source
    GLuint shader = glCreateShader(type);
    assert(shader != nullptr && "Method glCreateShader return null.");

    glShaderSource(shader, 1, &content, &length);

    // Compile and validate
    GLint param;
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
    if (param != GL_TRUE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param);
        std::vector<GLchar> log((uint) param);

        glGetShaderInfoLog(shader, param, NULL, &(log[0]));
        fprintf(stderr, "%s\n", &log[0]);

        glDeleteShader(shader);
        assert(false && "Shader compilation failed.");
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
        std::vector<GLchar> log((uint) param);

        glGetProgramInfoLog(glProgram, param, NULL, &(log[0]));
        fprintf(stderr, "%s\n", &log[0]);

        assert(false && "Linking shader program error.");
    }
}

void pxs::ShaderBuilder::dispose() {
    detachAll();

    if(glProgram != nullptr) {
        glDeleteProgram(glProgram);
        glProgram = nullptr;
    }
}
