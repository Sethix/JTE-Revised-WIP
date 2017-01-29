#include <algorithm>
#include "JTLMath.h"

namespace JTL
{

#pragma region Clamps

	int intClamp(const int & v, const int & iMin, const int & iMax)
	{ return fminf(fmaxf(v, iMin), iMax); }

	float fltClamp(const float & v, const float & fMin, const float & fMax)
	{ return fminf(fmaxf(v, fMin), fMax); }

	double dblClamp(const double & v, const double & dMin, const double & dMax)
	{ return fmin(fmax(v, dMin), dMax); }

#pragma endregion

}