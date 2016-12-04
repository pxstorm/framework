#pragma once

#include <GL/glew.h>

namespace pxs {
    class ShaderVariable {
    public:
        enum Type {
            Vector,
            Color,
            Matrix,
            Int,
            UInt
        };

        ShaderVariable(GLint glVariable);

        // TODO: setVector(...)
        // TODO: setColor(...)
        // TODO: setValue(...)
        // TODO: setVector(...)
        // TODO: setMatrix(...)

        virtual ~ShaderVariable();

    protected:
        GLint glVariable;
    };
}

