#pragma once
#include "constant.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "SOIL.h"

#define LOCSTR(token) hash(#token)
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <random>
#include <glfw3.h>
#include <stb_image_aug.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

#include <cstdlib>
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
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

        static int getRandomInt(int min, int max) {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> uni(min, max);
            return uni(rng);
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

        static std::unordered_map<int, std::string> loadTranslation(std::string path) {
            std::unordered_map<int, std::string> localizedStrings;
            std::ifstream infile(path);
            std::string line;
            std::vector<std::vector<std::string>> content;
            std::vector<std::string> row;
            while (std::getline(infile, line))
            {
                row.clear();
                std::stringstream iss(line);
                std::string token;
                char delimiter = ',';
                std::string value;
                while (std::getline(iss, value, ','))
                    row.push_back(value);
                content.push_back(row);
            }

            for (std::vector<std::string> pair : content) {
                int key = Utils::hash(pair[0].c_str());
                std::string translation = pair[1];
                localizedStrings.insert(std::pair<int, std::string>(key, translation));
            }
            return localizedStrings;
        }
        static std::unordered_map<int, std::string> loadConverter() {
            std::unordered_map<int, std::string> localizedStrings;
            std::string path = "./Assets/Data/Converter/";
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                std::ifstream infile(entry.path());
                std::string line;
                std::vector<std::vector<std::string>> content;
                std::vector<std::string> row;
                while (std::getline(infile, line))
                {
                    row.clear();
                    std::stringstream iss(line);
                    std::string token;
                    char delimiter = ',';
                    std::string value;
                    while (std::getline(iss, value, ','))
                        row.push_back(value);
                    content.push_back(row);
                }

                for (std::vector<std::string> pair : content) {
                    int key = Utils::hash(pair[0].c_str());
                    std::string translation = pair[1];
                    localizedStrings.insert(std::pair<int, std::string>(key, translation));
                }
            }
            return localizedStrings;
        }
};

