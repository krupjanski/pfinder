#include <classes/Base.h>
#include <classes/Helpers.h>

const double Helpers::Pi=3.14159265;

POINT3 Helpers::makePoint(double *data)
{
	POINT3 newpoint;
	newpoint.x = data[0];
	newpoint.y = data[1];
	newpoint.z = data[2];

	return newpoint;
}

POINT3 Helpers::makePoint(double *startp, double *endp)
{
	POINT3 newpoint;
	newpoint.x = endp[0]-startp[0];
	newpoint.y = endp[1]-startp[1];
	newpoint.z = endp[2]-startp[2];

	return newpoint;
}

double Helpers::length(POINT3 a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

double Helpers::scalProd(POINT3 a, POINT3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

double Helpers::angle(POINT3 a, POINT3 b)
{
	return acos(scalProd(a, b)/(length(a)*length(b)))*180.0/Pi;
}

double Helpers::angle(double * aData, double *bData, double *cData)
{
	POINT3 a = makePoint(aData, bData);
	POINT3 b = makePoint(cData, bData);
	return acos(scalProd(a, b)/(length(a)*length(b)))*180.0/Pi;
}
