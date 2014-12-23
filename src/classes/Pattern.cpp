#include <classes/Pattern.h>

Pattern::Pattern(int newdeb) : AtomCluster(newdeb)
{
	Matrix = NULL;
	Cycles = false;
	Hard = true;
	Filter = 0;
	Center = -1;

	if(debug>0) cout << "Pattern created" << endl;
}

Pattern::~Pattern()
{
	if(NULL!=Matrix) free(Matrix);
	if(debug>0) cout << "Pattern terminated" << endl;
}

double Pattern::M(int i, int j){
	return Matrix[i*eCount+j];
}

bool Pattern::isCycled(){
	return Cycles;
}

bool Pattern::init()
{
	Matrix = (double*)malloc(eCount*eCount*sizeof(double));
	if(NULL==Matrix) 
	{
		Errmsg("buildMatrix",1);
		return false;
	}

	for ( int i=0 ; i<eCount ; i++ )
		for ( int j=0 ; j<eCount ; j++ )
			if (i!=j) {
				double r = getDistance(i, j);
				Matrix[i*eCount+j] = r;
				Matrix[j*eCount+i] = r;
			}
			else Matrix[i*eCount+j] = 0.0f;
	if(debug>0) {
		cout << endl << "Matrix: " << endl;
		for ( int i=0 ; i<eCount ; i++ ) {
			for ( int j=0 ; j<eCount ; j++ ) {
				cout << Matrix[i*eCount+j] << "\t";
			}
			cout << endl;
		}
	}
	return true;	
}

void Pattern::checkDuplicates(int index)
{
	if(index>0)
	{
		for ( int i = 0 ; i < index ; i++ )
		{
			if ( (elements[i].data[X] == elements[index].data[X])&&
					(elements[i].data[Y] == elements[index].data[Y])&&
					(elements[i].data[Z] == elements[index].data[Z]))
			{
				if(debug>0) cout << "Pattern contains cycles" << endl;
				Cycles = true;
			}
		}
	}
}

void Pattern::setAtomData(int index, int newT, double newX, double newY, double newZ)
{
	AtomCluster::setAtomData(index, newT, newX, newY, newZ);
	checkDuplicates(index);
}

bool Pattern::readAdditional(string header, ifstream *file)
{
	string tmp;
	size_t found;
	int inttmp;

	found = header.find("Hard"); 
	if(found!=string::npos) 
	{
		getline (*file,tmp);
		if(sscanf(tmp.c_str(),"%d",&inttmp)<=0) 
		{
			Errmsg("readAdditional",3);
			return false;
		}
		Hard = (inttmp==1)?true:false;
	}

	found = header.find("Filter"); 
	if(found!=string::npos) 
	{
		getline (*file,tmp);
		if(sscanf(tmp.c_str(),"%d",&Filter)<=0) 
		{
			Errmsg("readAdditional",3);
			return false;
		}
	}

	found = header.find("Center"); 
	if(found!=string::npos) 
	{
		getline (*file,tmp);
		if(sscanf(tmp.c_str(),"%d",&Center)<=0) 
		{
			Errmsg("readAdditional",3);
			return false;
		}
	}

	return true;
}

bool Pattern::isHard()
{
	return Hard;
}

int Pattern::getFilterMode()
{
	return Filter;
}

int Pattern::getCenter()
{
	return Center;
}
