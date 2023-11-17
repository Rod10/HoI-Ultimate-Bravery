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
		WinterLogisticsSupportCompany,
		SLast
	};

	static std::string typeToString(Type type) {

	}

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
		case UnitSubType::WinterLogisticsSupportCompany: return "winterLogisticsCompany";
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
		if (type == "amtracBatattlion") return AmtracBattalion;
		if (type == "armoredCar") return ArmoredCar;
		if (type == "antiTank") return AntiTank;
		if (type == "antiAir") return AntiAir;
		if (type == "artillery") return Artillery;
		if (type == "rocketArtillery") return RocketArtillery;
		if (type == "motorizedAntiTank") return MotorizedAntiTank;
		if (type == "motorizedAntiAir") return MotorizedAntiAir;
		if (type == "motorizedAritllery") return MotorizedArtillery;
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
};