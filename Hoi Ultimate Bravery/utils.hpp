#pragma once
#define LOCSTR(token) hash(#token)
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <random>
#include <glfw3.h>
#include <stb_image_aug.h>

class Utils
{
    public :
        template<typename Iter, typename RandomGenerator>
        static Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
            std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
            std::advance(start, dis(g));
            return start;
        }

        template<typename Iter>
        static Iter select_randomly(Iter start, Iter end) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return select_randomly(start, end, gen);
        }

        static constexpr int hash(const char* string) {
            unsigned long hash = 5381;
            int c;

            while (c = *string++)
                hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

            return hash;
        }
        // Simple helper function to load an image into a OpenGL texture with common settings
        static bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
        {
            // Load from file
            int image_width = 0;
            int image_height = 0;
            unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
            if (image_data == NULL)
                return false;

            // Create a OpenGL texture identifier
            GLuint image_texture;
            glGenTextures(1, &image_texture);
            glBindTexture(GL_TEXTURE_2D, image_texture);

            // Setup filtering parameters for display
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F); // This is required on WebGL for non power-of-two textures
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F); // Same

            // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
            glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
            stbi_image_free(image_data);

            *out_texture = image_texture;
            *out_width = image_width;
            *out_height = image_height;

            return true;
        }
};

