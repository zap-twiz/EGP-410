#include "Color.h"
#include <sstream>
#include <functional>
#include <string>

using namespace std;

Color::Color(int r, int g, int b, int a /*= 255*/)
	:mR(r)
	,mG(g)
	,mB(b)
	,mA(a)
{
	mHash = (r << 24) + (g << 16) + (b << 8) + a;
	//stringstream ss;
	//ss << "red=" << mR << "green=" << mG << "blue=" << mB << "alpha=" << mA;
	//hash<string> strHash;
	//mHash = strHash(ss.str());
}

bool Color::operator<(const Color& rhs) const
{
	if (mHash < rhs.mHash)
		return true;

	return false;
}
