#pragma once

#include <define.h>
#include <classes/Base.h>


using namespace std;

class Graph : public Base {
	public:
		//Properties

		//Methods
		Graph(int newdeb);
		virtual ~Graph();

		void appendEdge(int i, int j, double weight);
		void setVerticles(int *aTypes, int size);
		bool setEdges(EDGE *earray, int esize);

		bool setVCount(int newVCount);
		int getVCount();
		int getECount();
		int *getVerticles();
		void normalizeWeights();
		void normalizeAngles();
		void saveToFile(string nodefilename, string linksfilename);

	private:
		//Properties
		int vCount;
		int *verticles; 
		int eCount;
		EDGE *edges;
		double maxWeight;

		//Methods
};
