#include "icon.hpp"
Icon* Icon::icon_ = nullptr;;

Icon* Icon::GetInstance()
{
	if (icon_ == nullptr) {
        int my_image_width = 0;
        int my_image_height = 0;
        GLuint my_image_texture = 0;
        std::map<std::string, Texture> textureCategory;
        std::map<std::string, std::map<std::string, Texture>> tankIconTextures;
        std::map<std::string, std::map<std::string, Texture>> textures;

        std::string fileName = std::format("./Assets/Images/Background/tank_designer_bg.png");
        bool ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        Texture texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_designer_bg", texture));

        fileName = std::format("./Assets/Images/Background/tank_name_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_name_bg", texture));

        fileName = std::format("./Assets/Images/Background/tank_role_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_role_bg", texture));

        fileName = std::format("./Assets/Images/Background/equipment_icon_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        texture.my_image_width = 154;
        texture.my_image_height = 56;
        textureCategory.insert(std::pair<std::string, Texture>("tank_icon_bg", texture));

        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("equipment_icon_bg", texture));

        fileName = std::format("./Assets/Images/Background/tank_blueprint_background.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_blueprint_background", texture));

        textures.insert(std::pair<std::string, std::map<std::string, Texture>>("background", textureCategory));
        textureCategory.clear();

        std::string path = "./Assets/Images/Blueprint/";
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

        textures.insert(std::pair<std::string, std::map<std::string, Texture>>("blueprint", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Modules/Cannon";
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

        path = "./Assets/Images/Modules/Turret";
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

        path = "./Assets/Images/Modules/Special";
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

        path = "./Assets/Images/Modules/Suspension";
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

        path = "./Assets/Images/Modules/Armor";
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

        path = "./Assets/Images/Modules/Engine";
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

        textures.insert(std::pair<std::string, std::map<std::string, Texture>>("modules", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Light";
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
        textureCategory.clear();
        icon_ = new Icon(tankIconTextures, textures);
	}
	return icon_;
}

std::map<std::string, Texture> Icon::getTankIcon(std::string type)
{
    return tankIconTextures_.find(type)->second;
}

Texture Icon::getTankIconTextures(std::string type, std::string name)
{
    return tankIconTextures_.find(type)->second.find(name)->second;
}

Texture Icon::getTankModulesTextures(std::string type, std::string name)
{
    return tankModulesTextures_.find(type)->second.find(name)->second;
}
