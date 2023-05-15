#include "icon.hpp"
Icon* Icon::icon_ = nullptr;;

Icon* Icon::GetInstance()
{
	if (icon_ == nullptr) {
        int my_image_width = 0;
        int my_image_height = 0;
        GLuint my_image_texture = 0;
        std::string fileName;
        bool ret;
        Texture texture = Texture(0,0,0);
        std::map<std::string, Texture> textureCategory;
        std::map<std::string, std::map<std::string, Texture>> tankIconTextures;
        std::string path = "./Assets/Images/Icon/Light";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            bool ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("light", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Medium";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("medium", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Heavy";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("heavy", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/SuperHeavy";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("superHeavy", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Modern";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("modern", textureCategory));
        icon_ = new Icon(tankIconTextures);
	}
	return icon_;
}

Texture Icon::getTankIconTextures(std::string type, std::string name)
{
    return tankIconTextures_.find(type)->second.find(name)->second;
}
