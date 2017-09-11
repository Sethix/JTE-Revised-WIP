#pragma once

#pragma region Defines

#define PI_F 3.14159265f
#define PI_D 3.1415926535897932
#define DEG2RAD(v) v * 0.0174533
#define RAD2DEG(v) v * 57.2958

#pragma endregion

namespace JTL
{

#pragma region Clamps

	int		intClamp(const int	  &v, const int	   &iMin, const int	   &iMax);
	float	fltClamp(const float  &v, const float  &fMin, const float  &fMax);
	double	dblClamp(const double &v, const double &dMin, const double &dMax);

#pragma endregion

}