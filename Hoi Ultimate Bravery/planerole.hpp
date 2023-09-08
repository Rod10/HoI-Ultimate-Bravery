#pragma once
#include <string>
class PlaneRole
{
public:
	enum Role {
		Fighter,
		CAS,
		NavalBombing,
		TacticalBombing,
		StrategicBombing,
		Last
	};

	static std::string roleToString(Role role) {
		switch (role)
		{
		case PlaneRole::Fighter: return "fighter";
		case PlaneRole::CAS: return "cas";
		case PlaneRole::NavalBombing: return "navalBombing";
		case PlaneRole::TacticalBombing: return "tacticalBombing";
		case PlaneRole::StrategicBombing: return "strategicBombing";
		default:
			break;
		}
	}
};

