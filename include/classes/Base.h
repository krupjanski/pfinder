#pragma once

#include <define.h>

using namespace std;

class Base {

	public:

		//Properties

		//Methods
		Base(int newdeb);
		virtual ~Base();
		POINT3 makePoint(double *data);
		POINT3 makePoint(double *startp, double *endp);
		double scalProd(POINT3 a, POINT3 b);
		

	protected:

		//Properties
		int debug;
		int msgCount;
		string *msg;

		//Methods
		void Errmsg(string Place, int code);
		int Errappend(string newerror);
};
