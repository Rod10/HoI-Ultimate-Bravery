#pragma once
#include <string>
class UnitSubType
{
public:
	enum Type {
		Infantry,
		Bicycle,
		PenalBattalion,
		Moutain,
		Marines,
		Paratrooper,
		Cavalry,
		Camelry,
		MotorizedInfantry,
		MechanizedInfantry,
		AmtracBattalion,
		ArmoredCar,
		AntiTank,
		AntiAir,
		Artillery,
		RocketArtillery,
		MotorizedAntiTank,
		MotorizedAntiAir,
		MotorizedArtillery,
		TruckDrawnRocketArtillery,
		MotorizedRocketArtillery,
		LightTank,
		MediumTank,
		HeavyTank,
		SuperHeavyTank,
		ModernTank,
		LightTankDestroyer,
		MediumTankDestroyer,
		HeavyTankDestroyer,
		SuperHeavyTankDestroyer,
		ModernTankDestroyer,
		LightSPArtillery,
		MediumSPArtillery,
		HeavySPArtillery,
		SuperHeavySPArtillery,
		ModernSPArtillery,
		LightSPAntiAir,
		MediumSPAntiAir,
		HeavySPAntiAir,
		SuperHeavySPAntiAir,
		ModernSPAntiAir,
		Last
	};
	enum Support {
		SupportAntiTank,
		SupportAntiAir,
		SupportArtillery,
		SupportRocketArtillery,
		CavalryReconCompany,
		MotorizedReconCompany,
		ArmoredCarReconCompany,
		EngineerCompany,
		FieldHospital,
		LogisticsCompany,
		MaintenanceCompany,
		MilitaryPolice,
		SignalCompany,
		SLast
	};

	static std::string supportTypeToString(Support support) {
		switch (support)
		{
		case UnitSubType::SupportAntiTank: return "antiTank";
		case UnitSubType::SupportAntiAir: return "antiAir";
		case UnitSubType::SupportArtillery: return "artillery";
		case UnitSubType::SupportRocketArtillery: return "rocketArtillery";	
		case UnitSubType::CavalryReconCompany: return "cavalryReconCompany";
		case UnitSubType::MotorizedReconCompany: return "motorizedReconCompany";
		case UnitSubType::ArmoredCarReconCompany: return "armoredCarReconCompany";
		case UnitSubType::EngineerCompany: return "engineerCompany";
		case UnitSubType::FieldHospital: return "fieldHospital";
		case UnitSubType::LogisticsCompany:return "logisticsCompany";
		case UnitSubType::MaintenanceCompany: return "maintenanceCompany";
		case UnitSubType::MilitaryPolice: return "militaryPolice";
		case UnitSubType::SignalCompany: return "signalCompany";
		case UnitSubType::SLast:
			break;
		default:
			break;
		}
	}

	static std::string supportTypeToImageString(Support support) {
		switch (support)
		{
		case UnitSubType::SupportAntiTank: return "Support_anti-tank";
		case UnitSubType::SupportAntiAir: return "Support_anti-air";
		case UnitSubType::SupportArtillery: return "Support_artillery";
		case UnitSubType::SupportRocketArtillery: return "Support_rocket_artillery";	
		case UnitSubType::CavalryReconCompany: return "Recon";
		case UnitSubType::MotorizedReconCompany: return "Motorized_Recon";
		case UnitSubType::ArmoredCarReconCompany: return "Armored_Car_Recon";
		case UnitSubType::EngineerCompany: return "Engineer";
		case UnitSubType::FieldHospital: return "Field_hospital";
		case UnitSubType::LogisticsCompany:return "Logistics_company";
		case UnitSubType::MaintenanceCompany: return "Maintenance_company";
		case UnitSubType::MilitaryPolice: return "Military_Police";
		case UnitSubType::SignalCompany: return "Signal_company";
		case UnitSubType::SLast:
			break;
		default:
			break;
		}
	}
	
	static std::string supportTypeToExportString(Support support) {
		switch (support)
		{
		case UnitSubType::SupportAntiTank: return "anti_tank";
		case UnitSubType::SupportAntiAir: return "anti_air";
		case UnitSubType::SupportArtillery: return "artillery";
		case UnitSubType::SupportRocketArtillery: return "rocket_artillery";
		case UnitSubType::CavalryReconCompany: return "recon";
		case UnitSubType::MotorizedReconCompany: return "mot_recon";
		case UnitSubType::ArmoredCarReconCompany: return "armored_car_recon";
		case UnitSubType::EngineerCompany: return "engineer_company";
		case UnitSubType::FieldHospital: return "field_hospital";
		case UnitSubType::LogisticsCompany:return "logistics_company";
		case UnitSubType::MaintenanceCompany: return "maintenance_company";
		case UnitSubType::MilitaryPolice: return "military_police";
		case UnitSubType::SignalCompany: return "signal_company";
		case UnitSubType::SLast:
			break;
		default:
			break;
		}
	}

	static UnitSubType::Type stringToType(std::string type) {
		if (type == "infantry") return Infantry;
		if (type == "bicycle") return Bicycle;
		if (type == "penalBattalion") return PenalBattalion;
		if (type == "mountain") return Moutain;
		if (type == "marines") return Marines;
		if (type == "paratrooper") return Paratrooper;
		if (type == "cavalry") return Cavalry;
		if (type == "camelry") return Camelry;
		if (type == "motorizedInfantry") return MotorizedInfantry;
		if (type == "mechanizedInfantry") return MechanizedInfantry;
		if (type == "amtracBattalion") return AmtracBattalion;
		if (type == "armoredCar") return ArmoredCar;
		if (type == "antiTank") return AntiTank;
		if (type == "antiAir") return AntiAir;
		if (type == "artillery") return Artillery;
		if (type == "rocketArtillery") return RocketArtillery;
		if (type == "motorizedAntiTank") return MotorizedAntiTank;
		if (type == "motorizedAntiAir") return MotorizedAntiAir;
		if (type == "motorizedArtillery") return MotorizedArtillery;
		if (type == "truckDrawnRocketArtillery") return TruckDrawnRocketArtillery;
		if (type == "motorizedRocketArtillery") return MotorizedRocketArtillery;
		if (type == "lightTank") return LightTank;
		if (type == "mediumTank") return MediumTank;
		if (type == "heavyTank") return HeavyTank;
		if (type == "superHeavyTank") return SuperHeavyTank;
		if (type == "modernTank") return ModernTank;
		if (type == "lightSPAntiAir") return LightSPAntiAir;
		if (type == "mediumSPAntiAir") return MediumSPAntiAir;
		if (type == "heavySPAntiAir") return HeavySPAntiAir;
		if (type == "superHeavySPAntiAir") return SuperHeavySPAntiAir;
		if (type == "modernSPAntiAir") return ModernSPAntiAir;
		if (type == "lightTankDestroyer") return LightTankDestroyer;
		if (type == "mediumTankDestroyer") return MediumTankDestroyer;
		if (type == "heavyTankDestroyer") return HeavyTankDestroyer;
		if (type == "superHeavyTankDestroyer") return SuperHeavyTankDestroyer;
		if (type == "modernTankDestroyer") return ModernTankDestroyer;
		if (type == "lightSPArtillery") return LightSPArtillery;
		if (type == "mediumSPArtillery") return MediumSPArtillery;
		if (type == "heavySPArtillery") return HeavySPArtillery;
		if (type == "superHeavySPArtillery") return SuperHeavySPArtillery;
		if (type == "modernSPArtillery") return ModernSPArtillery;
	}

	static std::string typeToImageString(Type type) {
		switch (type)
		{
		case UnitSubType::Infantry: return "Infantry";
		case UnitSubType::Cavalry: return "Cavalry";
		case UnitSubType::Camelry: return "Camelry";
		case UnitSubType::PenalBattalion: return "Penal_Battalion";
		case UnitSubType::MotorizedInfantry: return "Motorized";
		case UnitSubType::LightTank: return "Light_tank";
		case UnitSubType::MediumTank: return "Medium_tank";
		case UnitSubType::HeavyTank: return "Heavy_tank";
		case UnitSubType::SuperHeavyTank: return "Super_heavy_tank";
		case UnitSubType::ModernTank: return "Modern_tank";
		case UnitSubType::Marines: return "Marine";
		case UnitSubType::Paratrooper: return "Paratrooper";
		case UnitSubType::AntiTank: return "Anti-tank";
		case UnitSubType::AntiAir: return "Anti-air";
		case UnitSubType::ArmoredCar: return "Armored_Car";
		case UnitSubType::Artillery: return "Artillery";
		case UnitSubType::MotorizedArtillery: return "Motorized_artillery";
		case UnitSubType::MotorizedAntiTank: return "Motorized_anti-tank";
		case UnitSubType::MotorizedAntiAir: return "Motorized_anti-air";
		case UnitSubType::RocketArtillery: return "Rocket_artillery";
		case UnitSubType::MotorizedRocketArtillery:return "Motorized_rocket_artillery";
		case UnitSubType::TruckDrawnRocketArtillery:return "Truck_drawn_rocket_artillery";
		case UnitSubType::Bicycle: return "Bicycle_Battalion";
		case UnitSubType::Moutain: return "Mountaineers";
		case UnitSubType::MechanizedInfantry: return "Mechanized";
		case UnitSubType::LightSPAntiAir: return "Light_tank_anti-air";
		case UnitSubType::MediumSPAntiAir: return "Medium_tank_anti-air";
		case UnitSubType::HeavySPAntiAir: return "Heavy_tank_anti-air";
		case UnitSubType::SuperHeavySPAntiAir: return "Super_heavy_tank_anti-air";
		case UnitSubType::ModernSPAntiAir: return "Modern_tank_anti-air";
		case UnitSubType::LightSPArtillery: return "Light_tank_artillery";
		case UnitSubType::MediumSPArtillery: return "Medium_tank_artillery";
		case UnitSubType::HeavySPArtillery: return "Heavy_tank_artillery";
		case UnitSubType::SuperHeavySPArtillery: return "Super_heavy_tank_artillery";
		case UnitSubType::ModernSPArtillery: return "Modern_tank_artillery";
		case UnitSubType::LightTankDestroyer: return "Light_tank_anti-tank";
		case UnitSubType::MediumTankDestroyer: return "Medium_tank_anti-tank";
		case UnitSubType::HeavyTankDestroyer: return "Heavy_tank_anti-tank";
		case UnitSubType::SuperHeavyTankDestroyer: return "Super_heavy_tank_anti-tank";
		case UnitSubType::ModernTankDestroyer: return "Modern_tank_anti-tank";
		case UnitSubType::AmtracBattalion: return "Amtrac";
		default:
			break;
		}
	}

	static std::string typeToExortString(Type type) {
		switch (type)
		{
		case UnitSubType::Infantry: return "infantry";
		case UnitSubType::Cavalry: return "cavalry";
		case UnitSubType::Camelry: return "camelry";
		case UnitSubType::PenalBattalion: return "penalBattalion";
		case UnitSubType::MotorizedInfantry: return "motorized";
		case UnitSubType::LightTank: return "light_armor";
		case UnitSubType::MediumTank: return "medium_armor";
		case UnitSubType::HeavyTank: return "heavy_armor";
		case UnitSubType::SuperHeavyTank: return "super_heavy_armor";
		case UnitSubType::ModernTank: return "modern_armor";
		case UnitSubType::Marines: return "marine";
		case UnitSubType::Paratrooper: return "paratrooper";
		case UnitSubType::AntiTank: return "anti_tank_brigade";
		case UnitSubType::AntiAir: return "anti_air_brigade";
		case UnitSubType::ArmoredCar: return "armored_car";
		case UnitSubType::Artillery: return "artillery_brigade";
		case UnitSubType::MotorizedArtillery: return "mot_artillery_brigade";
		case UnitSubType::MotorizedAntiTank: return "mot_anti_tank_brigade";
		case UnitSubType::MotorizedAntiAir: return "mot_anti_air_brigade";
		case UnitSubType::RocketArtillery: return "rocket_artillery_brigade";
		case UnitSubType::MotorizedRocketArtillery:return "mot_rocket_artillery_brigade";
		case UnitSubType::TruckDrawnRocketArtillery:return "motorized_rocket_brigade";
		case UnitSubType::Bicycle: return "bicycle_battalion";
		case UnitSubType::Moutain: return "mountaineers";
		case UnitSubType::MechanizedInfantry: return "mechanized";
		case UnitSubType::LightSPAntiAir: return "light_sp_anti_air_brigade";
		case UnitSubType::MediumSPAntiAir: return "medium_sp_anti_air_brigade";
		case UnitSubType::HeavySPAntiAir: return "heavy_sp_anti_air_brigade";
		case UnitSubType::SuperHeavySPAntiAir: return "super_heavy_sp_anti_air_brigade";
		case UnitSubType::ModernSPAntiAir: return "modern_sp_anti_air_brigade";
		case UnitSubType::LightSPArtillery: return "light_sp_artillery_brigade";
		case UnitSubType::MediumSPArtillery: return "medium_sp_artillery_brigade";
		case UnitSubType::HeavySPArtillery: return "heavy_sp_artillery_brigade";
		case UnitSubType::SuperHeavySPArtillery: return "super_heavy_sp_artillery_brigade";
		case UnitSubType::ModernSPArtillery: return "modern_sp_artillery_brigade";
		case UnitSubType::LightTankDestroyer: return "light_tank_destroyer_brigade";
		case UnitSubType::MediumTankDestroyer: return "medium_tank_destroyer_brigade";
		case UnitSubType::HeavyTankDestroyer: return "heavy_tank_destroyer_brigade";
		case UnitSubType::SuperHeavyTankDestroyer: return "super_heavy_tank_destroyer_brigade";
		case UnitSubType::ModernTankDestroyer: return "modern_tank_destroyer_brigade";
		case UnitSubType::AmtracBattalion: return "amtrac_battalion";
		default:
			break;
		}
	}
};