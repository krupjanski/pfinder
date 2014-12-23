#pragma once

#include <define.h>
#include <classes/Application.h>
#include <classes/AtomCluster.h>
#include <classes/SimpCluster.h>
#include <classes/Pattern.h>
#include <classes/Graph.h>

using namespace std;

class MyApplication : public Application{

	public:

		//Properties

		//Methods
		MyApplication(int newdeb);
		~MyApplication();

		bool Init(int argc, char** argv);
		bool Start();

	private:

		//Properties
		SimpCluster * Result;

		Graph *aGraph;

		//Methods

};
