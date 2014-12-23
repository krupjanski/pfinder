#include <classes/Graph.h>

Graph::Graph(int newdeb) : Base(newdeb) {
	vCount = 0;
	verticles = NULL;
	eCount = 0;
	edges = NULL;
	maxWeight = 0.0f;
	if(debug>0) cout << "Graph object created " << endl;
}

Graph::~Graph(){

	if(verticles) free(verticles);
	if(edges) free(edges);
	if(debug>0) cout << "Graph object terminated!" << endl;
}

void Graph::appendEdge(int i, int j, double weight){
	eCount++;
	edges=(EDGE*)realloc(edges,eCount*sizeof(EDGE));
	edges[eCount-1].a=i;
	edges[eCount-1].b=j;
	edges[eCount-1].w=weight;
	if(weight>maxWeight)maxWeight=weight;
	if(debug>0) cout << i <<"-"<<j<<": "<<weight<<endl;
}

void Graph::setVerticles(int *aTypes, int size){
	vCount = size;

	verticles = aTypes;
	for(int i=0; i<size; i++) 
	{
		//verticles[i]=aTypes[i];
//		cout << i << " - " << verticles[i]<<endl;
	}
}

int Graph::getVCount(){
	return vCount;
}

int Graph::getECount(){
	return eCount;
}

void Graph::normalizeWeights(){
	for(int i=0; i<eCount; i++){
		edges[i].w/=maxWeight;
		if(debug>0) cout << edges[i].a<<"-"<<edges[i].b<<": "<<edges[i].w<<endl;
	}
}

void Graph::saveToFile(string nodefilename, string linkfilename)
{
	ofstream resfile;
	resfile.open(nodefilename.c_str());
	if (resfile.is_open()){
		resfile <<"Id;Label;Type"<< endl;
		for(int i=0;i<vCount;i++){
			resfile << (i+1)<<";"<<(i+1)<<";"<<verticles[i] << endl;
		}
		resfile.close();
	}
	resfile.open(linkfilename.c_str());
	if (resfile.is_open()){
		resfile <<"Source;Target;Type;Id;Label;Weight"<< endl;
		for(int i=0;i<eCount;i++){
			resfile << fixed << (edges[i].a+1)<<";"<<(edges[i].b+1)<<";Undirected;"<<(i+1)<<";;"<< edges[i].w <<endl;
		}
		resfile.close();
	}
}

bool Graph::setVCount(int newVCount)
{
	vCount = newVCount;
	verticles = (int*)realloc(verticles, vCount*sizeof(int));
	if ( NULL == verticles )
	{
		Errmsg("setVcount", 1);
		return false;
	}
	return true;
}

int *Graph::getVerticles()
{
	return verticles;
}

bool Graph::setEdges(EDGE *earray, int esize)
{
	
	eCount = esize;

	edges = earray;
	for(int i=0; i<esize; i++) 
	{
//		cout << i << " - (" << edges[i].a<<", "<<edges[i].b<<", "<<edges[i].w<<")"<<endl;
//verticles[i]=aTypes[i];
	}
	return true;
}

void Graph::normalizeAngles()
{
	for(int i=0; i<eCount; i++){
		edges[i].w/=180.0;
		if(debug>0) cout << edges[i].a<<"-"<<edges[i].b<<": "<<edges[i].w<<endl;
	}
}
