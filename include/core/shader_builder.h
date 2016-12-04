#pragma once

#include "core/shader.h"
#include "core/types.h"

namespace pxs {
    class ShaderBuilder {
    public:
        ShaderBuilder();

        /**
         * Attach source to the shader program
         * (use build method to make shader from attached sources).
         *
         * @param path GLSL file path to be compiled.
         * @param type GLSL file type.
         * @return
         */
        virtual ShaderBuilder &attach(const char *path, Shader::Type type);

        /**
         * Destroy all attached sources
         * and remove it from the building queue.
         *
         * @return
         */
        virtual ShaderBuilder &detachAll();

        /**
         * Get shader instance from attached sources
         * (also clean builder by detaching all sources).
         *
         * @return
         */
        virtual ptr<Shader> build();

        virtual ~ShaderBuilder();

    protected:
        GLuint glProgram;

        std::vector<GLuint> glShaders;

        /**
         * Compile shader source.
         *
         * @param source
         * @param type
         * @return OpenGL shader object identifier.
         */
        virtual GLuint compile(const GLchar *source, Shader::Type type);

        /**
         * Create program from linked sources.
         */
        virtual void link();

        /**
         * Destroy program and attached shaders.
         */
        virtual void dispose();
    };
}

