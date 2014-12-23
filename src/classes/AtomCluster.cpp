#include <classes/AtomCluster.h>

const int AtomCluster::X=0;
const int AtomCluster::Y=1;
const int AtomCluster::Z=2;

AtomCluster::AtomCluster(int newdeb) : Cluster<double>(newdeb) {

	if(debug>0) cout << "AtomCluster object created" << endl;

}

AtomCluster::~AtomCluster() 
{
	if(debug>0) cout << "AtomCluster object terminated" << endl;
}

double AtomCluster::getDistance(int iAtom, int jAtom){
	double r;
	double* x1 = elements[iAtom].data;
	double* x2 = elements[jAtom].data;
	r =  ( x1[X] - x2[X] ) * ( x1[X] - x2[X] );
	r += ( x1[Y] - x2[Y] ) * ( x1[Y] - x2[Y] );
	r += ( x1[Z] - x2[Z] ) * ( x1[Z] - x2[Z] );
	r = sqrt(r);
	return r;
}

bool AtomCluster::getDataFromFile(string fileName, int rmode)
{
	if(dimOverridden)
	{
		Errmsg("AtomCluster", 3);
		return false;
	}
	return Cluster<double>::getDataFromFile(fileName, rmode);
}

void AtomCluster::setAtomData(int index, int newT, double newX, double newY, double newZ)
{
	double newdata[3];
	newdata[0]=newX;
	newdata[1]=newY;
	newdata[2]=newZ;
	Cluster<double>::setData(index, newT, newdata);
}

void AtomCluster::getMidPoint(int iAtom, int jAtom, double *mPoint)
{
	for ( int i=0 ; i<3 ; i++ )
	{
		mPoint[i] = 0.5 * ( elements[iAtom].data[i] + elements[jAtom].data[i]);
	}
}
