#include <iostream>
#include "pxs/graphics/shader_builder.h"

int main() {
    pxs::ShaderBuilder x;
    x.attach("resources/shaders/basic.vs", pxs::Shader::Vertex);

    std::cout << "abc" << std::endl;
    return 0;
}