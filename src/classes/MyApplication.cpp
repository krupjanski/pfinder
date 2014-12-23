#include <classes/MyApplication.h>

const float Application::version=1.0f;
const string Application::name="Pattern finder";
const string Application::author="Krupyanskiy Dmitriy";
const int Application::year=2014;

MyApplication::MyApplication(int newdeb) : Application(newdeb) {

	Result = NULL;
	aGraph = NULL;

	if(newdeb>0) cout << "MyApplication created" << endl;
}

MyApplication::~MyApplication() {

	if(Result) delete Result;
	if(aGraph) delete aGraph;

	if(debug>0) cout << "MyApplication terminated" << endl;
}

bool MyApplication::Init(int argc, char** argv) {

	if(argc!=6)
	{
		cout << getFullInfo() << endl
			<< "Wrong parameters count" << endl
			<< "Usage: patt_search {coord_file} {pattern_file} {read_mode} {output_level} {epsilon}" 
			<< endl;
		return false;
	}

	string coordFileName = argv[1];
	string pattFileName = argv[2];
	int readMode = atoi(argv[3]);
	debug = atoi(argv[4]);
	double epsilon = atof(argv[5]);

	if(debug>0)
	{
		cout << (argc-1) << " parameters were given:" << endl
			<< "\tCoordinates filename:\t" << coordFileName << endl
			<< "\tPattern filename:\t" << pattFileName << endl
			<< "\tRead mode is set to:\t" << readMode << endl
			<< "\tDebug mode is set to:\t" << debug << endl
			<< "\tEpsilon is set to:\t" << epsilon << endl;
	}

	Result = new SimpCluster(coordFileName, pattFileName, epsilon, readMode, debug);
	Result -> init();

//	aGraph = new Graph(debug);

	if(debug>0) cout << "MyApplication initialized" << endl;
	return true;
}

bool MyApplication::Start() 
{
	if ( Result->Find(0, NULL) )
	{
		cout << "\tFound: " << Result->getECount()<<endl;

		if ( !Result->Filter() ) cout << "Filtering failed" << endl;

		Result->saveToFile("results");
		cout << "\tSaved: " << Result->getECount()<<endl;
		Result->saveAsGraph();
		Result->showStats();
////////////////////////
/*
		EDGE * edges = NULL;
		int * nods = NULL;

		int lnkCnt;
		edges = Result->getLinks(&lnkCnt);
		nods = Result->getListOfTypes();
//		aGraph->setVerticles(nods, Result->getECount());
		
		aGraph->setVerticles(nods, Result->getECount());

		for ( int i=0 ; i<lnkCnt ; i++){
			aGraph->appendEdge(edges[i].a,edges[i].b,edges[i].w);
		}

		cout << "Found " << Result->getECount() << " elements connected with " 
			<< aGraph->getECount() << " links!   ...done" << endl;

//		aGraph->normalizeWeights();
//		aGraph->saveToFile("nodes", "links");

		if ( nods ) free(nods);
		if ( edges ) free(edges);
*/
		return true;
	}
	else return false;
}
