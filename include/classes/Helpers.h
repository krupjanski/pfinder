#pragma once

#include <define.h>

using namespace std;

class Helpers {

	public:

		//Properties
		static const double Pi;

		//Methods
		static POINT3 makePoint(double *data);
		static POINT3 makePoint(double *startp, double *endp);
		static double scalProd(POINT3 a, POINT3 b);
		static double length(POINT3 a);
		static double angle(POINT3 a, POINT3 b);
		static double angle(double * aData, double *bData, double *cData);
		

	protected:

		//Properties


		//Methods

};
