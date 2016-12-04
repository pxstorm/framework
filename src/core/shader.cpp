#include "core/shader.h"

#include <cassert>

pxs::Shader::Shader(GLuint glProgram) {
    this->glProgram = glProgram;
}

pxs::ShaderVariable pxs::Shader::findAttribute(const GLchar *name) const {
    GLint location = glGetAttribLocation(glProgram, name);
    assert(location != -1 && "Cannot find attribute with the given name.");

    return pxs::ShaderVariable(location);
}

pxs::ShaderVariable pxs::Shader::findUniform(const GLchar *name) const {
    GLint location = glGetUniformLocation(glProgram, name);
    assert(location != -1 && "Cannot find uniform with the given name.");

    return pxs::ShaderVariable(location);
}

void pxs::Shader::use() const {
    glUseProgram(glProgram);
}

pxs::Shader::~Shader() {
    glDeleteProgram(glProgram);
}
