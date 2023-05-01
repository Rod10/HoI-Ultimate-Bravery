#pragma once
class TankType {
public:
	enum Type {
		Light,
		Medium,
		Heavy,
		SuperHeavy,
		Modern,
		Last
	};

	static TankType::Type intToTankType(int type) {
		switch (type) {
		default: break;
		case 0: return TankType::Type::Light;
		case 1: return TankType::Type::Medium;
		case 2: return TankType::Type::Heavy;
		case 3: return TankType::Type::SuperHeavy;
		case 4: return TankType::Type::Modern;
		}
	};
};