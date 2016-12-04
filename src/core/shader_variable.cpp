#include "core/shader_variable.h"

pxs::ShaderVariable::ShaderVariable(GLint glVariable) {
    this->glVariable = glVariable;
}

pxs::ShaderVariable::~ShaderVariable() {
    //
}
