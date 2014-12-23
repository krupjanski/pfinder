#pragma once

#include <define.h>
#include <classes/Cluster.h>


using namespace std;

class AtomCluster : public Cluster<double>{

	public:

		//Properties

		//Methods
//		int getACount();
//		int getAtomType(int index);
		bool getDataFromFile(string fileName, int rmode);
		double getDistance(int iAtom, int jAtom);
		void getMidPoint(int iAtom, int jAtom, double *mPoint);
		virtual void setAtomData(int index, int newT, double newX, double newY, double newZ);

		AtomCluster(int newdeb);
		virtual ~AtomCluster();

	protected:

		//Properties
		static const int X;
		static const int Y;
		static const int Z;
		POINT3 Center;

		//Methods

};
