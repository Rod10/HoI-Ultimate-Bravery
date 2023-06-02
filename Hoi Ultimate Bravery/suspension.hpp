#pragma once
#include "stats.hpp"
#include "tanktype.hpp"

#include <fstream>

class Suspension{
public:
	enum Type {
		Bogie,
		Christie,
		Interleaved,
		Torsion,
		HalfTrack,
		Wheeled,
		Last
	};

	Suspension();
	Suspension(
		Type type,
		Stats stats
	) :
		type(type),
		stats(stats){}

	static std::string typeToString(Type& type) {
		switch (type) {
		default: return "INVALID TYPE";
		case Bogie: return "bogie";
		case Christie: return "christie";
		case Interleaved: return "interleaved";
		case Torsion: return "torsion";
		case HalfTrack: return "halfTrack";
		case Wheeled: return "wheeled";
		}
	}

	static Suspension generateRandomSuspension(TankType::Type type);

	Type type;
	Stats stats;
};