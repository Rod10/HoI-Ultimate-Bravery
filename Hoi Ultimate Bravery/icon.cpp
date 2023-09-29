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
		std::map<std::string, std::map<std::string, Texture>> shipIconTextures;
		std::map<std::string, std::map<std::string, Texture>> planeIconTextures;
		std::map<std::string, std::map<std::string, Texture>> tankModulesTextures;
		std::map<std::string, std::map<std::string, Texture>> shipModulesTextures;
		std::map<std::string, std::map<std::string, Texture>> planeModulesTextures;

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

		tankModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("background", textureCategory));
		textureCategory.clear();

		fileName = std::format("./Assets/Images/Background/equipment_icon_bg.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		textureCategory.insert(std::pair<std::string, Texture>("equipment_icon_bg", texture));

		fileName = std::format("./Assets/Images/Background/equipment_icon_bg.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		texture.my_image_width = 375;
		texture.my_image_height = 60;
		textureCategory.insert(std::pair<std::string, Texture>("ship_icon_bg", texture));

		fileName = std::format("./Assets/Images/Background/tank_name_bg.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		texture.my_image_width = 200;
		texture.my_image_height = 30;
		textureCategory.insert(std::pair<std::string, Texture>("ship_name_bg", texture));

		fileName = std::format("./Assets/Images/Ship/ship_view_bg.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		textureCategory.insert(std::pair<std::string, Texture>("ship_view_bg", texture));

		shipModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("background", textureCategory));
		textureCategory.clear();

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

		fileName = std::format("./Assets/Images/Plane/generic_plane_blueprint_background.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		textureCategory.insert(std::pair<std::string, Texture>("plane_view_bg", texture));

		fileName = std::format("./Assets/Images/Background/equipment_icon_bg.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		texture.my_image_width = 154;
		texture.my_image_height = 56;
		textureCategory.insert(std::pair<std::string, Texture>("tank_icon_bg", texture));

		fileName = std::format("./Assets/Images/Background/equipment_icon_bg.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		textureCategory.insert(std::pair<std::string, Texture>("equipment_icon_bg", texture));

		planeModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("background", textureCategory));
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

		tankModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("blueprint", textureCategory));
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

		tankModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("modules", textureCategory));
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

		path = "./Assets/Images/Ship/Ship/destroyer";
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

		shipIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("destroyer", textureCategory));
		textureCategory.clear();

		path = "./Assets/Images/Ship/Ship/cruiser";
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

		shipIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("cruiser", textureCategory));
		textureCategory.clear();

		path = "./Assets/Images/Ship/Ship/carrier";
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

		shipIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("carrier", textureCategory));
		textureCategory.clear();

		path = "./Assets/Images/Ship/Ship/heavyShip";
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

		shipIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("heavyShip", textureCategory));
		textureCategory.clear();

		path = "./Assets/Images/Ship/Ship/submarine";
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

		shipIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("submarine", textureCategory));
		textureCategory.clear();

		path = "./Assets/Images/Ship/Modules/";
		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			if (p.is_directory()) {
				for (const auto& entry : std::filesystem::directory_iterator(p)) {
					const std::string imagePath = entry.path().string();
					ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
					IM_ASSERT(ret);
					texture = Texture(my_image_width, my_image_height, my_image_texture);

					std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
					std::string::size_type const p(base_filename.find_last_of('.'));
					std::string file_without_extension = base_filename.substr(0, p);

					textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
				}
			}
		}

		fileName = std::format("./Assets/Images/Ship/none.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		textureCategory.insert(std::pair<std::string, Texture>("none", texture));

		shipModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("modules", textureCategory));
		textureCategory.clear();

		path = "./Assets/Images/Plane/Plane/";		
		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			if (p.is_directory()) {
				for (const auto& entry : std::filesystem::directory_iterator(p)) {
					const std::string imagePath = entry.path().string();
					ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
					IM_ASSERT(ret);
					texture = Texture(my_image_width, my_image_height, my_image_texture);

					std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
					std::string::size_type const p(base_filename.find_last_of('.'));
					std::string file_without_extension = base_filename.substr(0, p);

					textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
				}
				std::string base_folder = p.path().string().substr(p.path().string().find_last_of("/\\") + 1);
				planeIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>(base_folder, textureCategory));
				textureCategory.clear();
			}
		}


		path = "./Assets/Images/Plane/Modules/";
		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			if (p.is_directory()) {
				for (const auto& entry : std::filesystem::directory_iterator(p)) {
					const std::string imagePath = entry.path().string();
					ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
					IM_ASSERT(ret);
					texture = Texture(my_image_width, my_image_height, my_image_texture);

					std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
					std::string::size_type const p(base_filename.find_last_of('.'));
					std::string file_without_extension = base_filename.substr(0, p);

					textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
				}
			}
		}

		fileName = std::format("./Assets/Images/Ship/none.png");
		ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);
		texture = Texture(my_image_width, my_image_height, my_image_texture);
		textureCategory.insert(std::pair<std::string, Texture>("none", texture));

		planeModulesTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("modules", textureCategory));

		icon_ = new Icon(tankIconTextures, tankModulesTextures, shipIconTextures, shipModulesTextures, planeModulesTextures, planeIconTextures);
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

Texture Icon::getShipModulesTextures(std::string type, std::string name)
{
	return shipModulesTextures_.find(type)->second.find(name)->second;
}

std::map<std::string, Texture> Icon::getShipIcon(std::string hull) {
	return shipIconTexture_.find(hull)->second;
}

std::map<std::string, Texture> Icon::getPlaneIcon(std::string hull) {
	return planeIconTextures_.find(hull)->second;
}

std::string Icon::getRandomIcon(TankType::Type type)
{	std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(type));
	auto it = icon.cbegin();
	int random = rand() % icon.size();
	std::advance(it, random);
	return it->first;
}

std::string Icon::getShipIcon(Hull::Type type, Country *country)
{
	std::map<std::string, Texture> icons = Icon::GetInstance()->getShipIcon(Hull::typeToString(type));
	std::string version = ShipVersion::versionToFileString(country->shipList.find(type)->second.version);
	std::string shipType = ShipType::shipTypeToIconString(country->shipList.find(type)->second.type);
	std::string string = std::format("{0}_{1}", version, shipType);
	return icons.find(string)->first;
}

std::string Icon::getPlaneIcon(PlaneType::Type type, PlaneRole::Role role, Country* country)
{
	std::map<std::string, Texture> icons = Icon::GetInstance()->getPlaneIcon(PlaneType::typeToString(type));
	std::string version = PlaneVersion::versionToFileString(country->planeList.find(role)->second.version);
	std::string shipType = PlaneType::typeToIconString(type);
	std::string string = std::format("{0}_plane_{1}", shipType, version);
	return icons.find(string)->first;
}

Texture Icon::getShipIconTextures(std::string type, std::string name) {
	return shipIconTexture_.find(type)->second.find(name)->second;
}

Texture Icon::getPlaneModulesTextures(std::string type, std::string name)
{
	return planeModulesTextures_.find(type)->second.find(name)->second;
}

Texture Icon::getPlaneIconTextures(std::string type, std::string name) {
	return planeIconTextures_.find(type)->second.find(name)->second;
}
