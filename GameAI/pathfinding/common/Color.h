#pragma once
#include <Trackable.h>


class Color : public Trackable
{
public:
	Color(int r, int g, int b, int a = 255);
	~Color(){};

	inline int getR() const { return mR; }
	inline int getG() const { return mG; }
	inline int getB() const { return mB; }
	inline int getA() const { return mA; }

	bool operator<(const Color& rhs) const;

private:
	int mR;
	int mG;
	int mB;
	int mA;
	size_t mHash;
};

const Color BLACK_COLOR = Color(0, 0, 0);
const Color RED_COLOR = Color(255, 0, 0);
const Color YELLOW_COLOR = Color(255, 255, 0);
const Color GREEN_COLOR = Color(0, 255, 0);
const Color BLUE_COLOR = Color(0, 0, 255);

