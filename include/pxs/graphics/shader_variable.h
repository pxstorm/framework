#pragma once

#include <GL/glew.h>

namespace pxs {
    class ShaderVariable {
    public:
        static const GLint INVALID_LOCATION = -1;

        ShaderVariable(GLint glVariable);

        // TODO: setValue(...) int, uint, ...?
        // TODO: setColor(...) vec3, vec4, ...?
        // TODO: setVector(...) vec2, vec3, vec4
        // TODO: setMatrix(...) mat4?

        virtual ~ShaderVariable();

    protected:
        GLint glVariable;
    };
}

