#include "pxs/core/directives.h"
#include "pxs/graphics/shader.h"

pxs::Shader::Shader(GLuint glProgram) {
    this->glProgram = glProgram;
}

pxs::ShaderVariable pxs::Shader::findAttribute(const GLchar *name) const {
    GLint location = glGetAttribLocation(glProgram, name);
    EXPECT(location != ShaderVariable::INVALID_LOCATION, "Cannot find attribute with the given name.");

    return pxs::ShaderVariable(location);
}

pxs::ShaderVariable pxs::Shader::findUniform(const GLchar *name) const {
    GLint location = glGetUniformLocation(glProgram, name);
    EXPECT(location != ShaderVariable::INVALID_LOCATION, "Cannot find uniform with the given name.");

    return pxs::ShaderVariable(location);
}

void pxs::Shader::use() const {
    glUseProgram(glProgram);
}

pxs::Shader::~Shader() {
    glDeleteProgram(glProgram);
}
