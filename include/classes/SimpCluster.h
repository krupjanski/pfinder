#pragma once

#include <define.h>
#include <classes/Cluster.h>
#include <classes/AtomCluster.h>
#include <classes/Pattern.h>
#include <classes/Graph.h>
#include <classes/Helpers.h>


using namespace std;

class SimpCluster : public Cluster<int>{

	public:

		//Properties

		//Methods
		bool alreadyHas(int *newdata, bool cycled);
		bool Find(int iteration, int *chain);
		bool Filter();
		bool printStats();
		EDGE* getLinks(int *linksCount);
		bool init();
		int *getListOfTypes();
		bool saveAsGraph();
		void showStats();

		SimpCluster(string coordFName, string pattFName, double epsilon, int rMode, int newdeb);
		virtual ~SimpCluster();

	protected:

		//Properties
		AtomCluster *aCluster;
		Pattern *aPattern;
		double aEpsilon;
		string coordFileName;
		string pattFileName;
		int readMode;
		double **stats;

		//Methods
		int chooseExclusion(int i, int j);
		double *getAData(int eIndex, int aIndex);
		double getAngle(int iSimp, int jSimp, int *Points, int size);
		void getCenter(int iSimp, double *Point);
};
