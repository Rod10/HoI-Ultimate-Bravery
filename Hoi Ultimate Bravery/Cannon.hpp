#pragma once
class Cannon
{
public:
	enum Size {
		Small,
		Medium,
		Heavy,
		BFG,
		Last
	};

	Cannon::Size size;
};

