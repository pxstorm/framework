#pragma once

#include <vector>
#include "shader.h"

namespace pxs {
    class ShaderBuilder {
    public:
        static const GLuint GL_NULL = 0;

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
         * Get shader instance from attached sources
         * (also clean builder by detaching all sources).
         *
         * @return
         */
        virtual Shader::ptr build();

        virtual ~ShaderBuilder();

    protected:
        /**
         * Initialized with first `attach` method call.
         */
        GLuint glProgram;

        std::vector<GLuint> glShaders;

        struct ShaderSource {
            GLchar* content;
            GLint length;
        };

        /**
         * Get file length and content.
         *
         * @param path
         * @return
         */
        virtual ShaderSource readFile(const char *path);

        /**
         * Compile shader source.
         *
         * @param source
         * @param type
         * @return OpenGL shader object identifier.
         */
        virtual GLuint compile(const ShaderSource source, Shader::Type type);

        /**
         * Create program from linked sources.
         */
        virtual void link();

        /**
         * Destroy all attached sources
         * and remove it from the building queue.
         *
         * @return
         */
        virtual ShaderBuilder &detachAll();

        /**
         * Destroy program and attached shaders.
         */
        virtual void dispose();
    };
}
