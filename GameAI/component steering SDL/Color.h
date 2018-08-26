#pragma once
#include <Trackable.h>


class Color : public Trackable
{
public:
	Color(int r, int g, int b, int a = 255) :mR(r), mG(g), mB(b), mA(a){};
	~Color(){};

	inline int getR() const { return mR; }
	inline int getG() const { return mG; }
	inline int getB() const { return mB; }
	inline int getA() const { return mA; }

private:
	int mR;
	int mG;
	int mB;
	int mA;
};

const Color BLACK_COLOR = Color(0, 0, 0);
const Color RED_COLOR = Color(255, 0, 0);

