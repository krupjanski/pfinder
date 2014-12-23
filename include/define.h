#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>

#ifndef STRUCT_OBJECT
#define STRUCT_OBJECT
template <typename T> 
struct OBJECT { 
	int t; 
	T *data; 
};
#endif

#ifndef STRUCT_ATOM
#define STRUCT_ATOM
typedef struct{
		int t;
		double x;
		double y;
		double z;
	} ATOM;
#endif

#ifndef STRUCT_POINT
#define STRUCT_POINT
typedef struct{
		double x;
		double y;
		double z;
	} POINT3;
#endif

#ifndef STRUCT_FUZZELEMENT
#define STRUCT_FUZZELEMENT
typedef struct{
		int i;
		double mu;
	} FUZZELEMENT;
#endif

#ifndef STRUCT_FUZZSET
#define STRUCT_FUZZSET
typedef struct{
		int n;
		FUZZELEMENT * set;
	} FUZZSET;
#endif

#ifndef STRUCT_EDGE
#define STRUCT_EDGE
typedef struct{
		int a;
		int b;
		double w;
	}EDGE;
#endif

#ifndef STRUCT_INTPAIR
#define STRUCT_INTPAIR
typedef struct{
		int a;
		int b;
	}INTPAIR;
#endif
