Shaders
=======

This chapter assumes that you are familiar with [OpenGL Shaders](https://www.khronos.org/opengl/wiki/Shader).

To create and use shaders you have to include `shader_builder.h` header:

```cpp
#include "pxs/graphics/shader_builder.h"
```

Building Shader
---------------

`ShaderBuilder` class provide easy way for building [GLSL Objects](https://www.khronos.org/opengl/wiki/GLSL_Object). Using `attach` method we can compile and attach shader source to the program.

```cpp
pxs::ShaderBuilder sb;
sb.attach("resources/shaders/basic.vs", pxs::Shader::Vertex);
sb.attach("resources/shaders/basic.fs", pxs::Shader::Fragment);
```

Then you can use `build` method which link previously attached shaders.

```cpp
pxs::Shader::ptr basic = sb.build();
```

This method also detach all previously attached shaders. If you would like to build another shader with the same vertex shader source then you have to attach it again:

```cp
pxs::ShaderBuilder sb;
sb.attach("resources/shaders/basic.vs", pxs::Shader::Vertex);
sb.attach("resources/shaders/basic.fs", pxs::Shader::Fragment);
pxs::Shader::ptr basic = sb.build();

sb.attach("resources/shaders/basic.vs", pxs::Shader::Vertex);
sb.attach("resources/shaders/other.fs", pxs::Shader::Fragment);
pxs::Shader::ptr other = sb.build();
```

Using Shader
------------

`pxs::Shader::ptr` provide 3 useful methods:

- `use` - use shader in rendering
- `findUniform` - get uniform variable by name
- `findAttribute` - get attribute variable by name

It's recommended to call `findUniform` and `findAttribute` methods fixed number of times and store retrieved instances.

Uniforms and Attributes
-----------------------

Not implemented yet.