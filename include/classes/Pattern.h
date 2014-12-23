#pragma once

#include <define.h>
#include <classes/AtomCluster.h>

using namespace std;

class Pattern : public AtomCluster {

	public:

		//Properties

		//Methods
		bool init();
		bool isCycled();
		bool isHard();
		bool readAdditional(string header, ifstream *file);
		double M(int i, int j);
		int getFilterMode();
		void checkDuplicates(int index);
		void setAtomData(int index, int newT, double newX, double newY, double newZ);
		int getCenter();

		Pattern(int newdeb);
		~Pattern();


	private:

		//Properties
		double *Matrix;
		bool Cycles;
		bool Hard;
		int Filter;
		int Center;

		//Methods
};
