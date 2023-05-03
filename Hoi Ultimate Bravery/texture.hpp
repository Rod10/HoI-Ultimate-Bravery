#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "SOIL.h"

#include <cstdlib>
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

class Texture
{
public:
    Texture(int my_image_width, int my_image_height, GLuint my_image_texture) : 
        my_image_width(my_image_width),
        my_image_height(my_image_height),
        my_image_texture(my_image_texture) {}

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
};

