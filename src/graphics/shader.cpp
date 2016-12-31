#include "pxs/core/directives.h"
#include "pxs/graphics/shader.h"

pxs::Shader::Shader(GLuint glProgram) {
    this->glProgram = glProgram;
}

pxs::ShaderVariable pxs::Shader::findAttribute(const GLchar *name) const {
    // We must ensure that we're using this shader,
    // in other way there's a chance that we'll try
    // to find attribute in other shader program.
    use();

    GLint location = glGetAttribLocation(glProgram, name);
    EXPECT(location != ShaderVariable::INVALID_LOCATION, "Cannot find attribute with the given name.");

    return pxs::ShaderVariable(location);
}

pxs::ShaderVariable pxs::Shader::findUniform(const GLchar *name) const {
    // We must ensure that we're using this shader,
    // in other way there's a chance that we'll try
    // to find uniform in other shader program.
    use();

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
