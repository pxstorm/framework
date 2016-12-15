#pragma once

#include <memory>
#include "shader_variable.h"

namespace pxs {
    class Shader {
    public:
        typedef std::shared_ptr<Shader> ptr;

        enum Type {
            Vertex = GL_VERTEX_SHADER,
            TessControl = GL_TESS_CONTROL_SHADER,
            TessEvaluation = GL_TESS_EVALUATION_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
            Compute = GL_COMPUTE_SHADER
        };

        Shader(GLuint glProgram);

        /**
         * Get shader attribute variable
         * (it's recommended to retrieve variable fixed number of times).
         *
         * @param name GLSL attribute name.
         * @return
         */
        virtual ShaderVariable findAttribute(const GLchar *name) const;

        /**
         * Get shader uniform variable
         * (it's recommended to retrieve variable fixed number of times).
         *
         * @param name GLSL uniform name.
         * @return
         */
        virtual ShaderVariable findUniform(const GLchar *name) const;

        /**
         * Make shader program active.
         */
        virtual void use() const;

        /**
         * Destroy shader.
         */
        virtual ~Shader();

    protected:
        GLuint glProgram;
    };
}
