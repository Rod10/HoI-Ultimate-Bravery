#pragma once
//#include "gun.hpp"
#include "gunsize.hpp"
#include "stats.hpp"
#include "tanktype.hpp"
#include "turrettype.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Turret
{
public :
		Turret(TurretType::Type type, int crew, std::vector<GunSize::Size> allowedGun, Stats stats) :
		type(type),
		crew(crew),
		allowedGun(allowedGun),
		stats(stats) {}

    static Turret generatingRandomTurret(int tankType);

	TurretType::Type type;
	int crew;
	std::vector<GunSize::Size> allowedGun;
	Stats stats;
};

