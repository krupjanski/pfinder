#include <classes/SimpCluster.h>

SimpCluster::SimpCluster(string coordFName, string pattFName, double epsilon, int rMode, int newdeb) : Cluster<int>(newdeb)
{
	aEpsilon = epsilon;
	aCluster = NULL;
	aPattern = NULL;
	stats = NULL;
	readMode = rMode;

	coordFileName = coordFName;
	pattFileName = pattFName;

	tCount = 1;
	if(debug>0) cout << "SimpCluster object created" << endl;
	Errappend("Unknown filter mode value");	//Code 4
}

SimpCluster::~SimpCluster() 
{
	if ( aPattern ) delete aPattern;
	if ( aCluster ) delete aCluster;
	if ( stats ) 
	{
		for ( int i=0 ; i<3 ; i++)
			if ( stats[i] ) delete [] stats[i];
		delete [] stats;
	}

	if(debug>0) cout << "SimpCluster object terminated" << endl;
}

bool SimpCluster::init() 
{
	aCluster = new AtomCluster(debug);		//Создаём кластер
	if(!aCluster->getDataFromFile(coordFileName, readMode)) return false;

	aPattern = new Pattern(debug);		//Создаём шаблон
	if(!aPattern->getDataFromFile(pattFileName, 0)) return false;
	dimension = aPattern->getECount();
	aPattern->init();			//Строим матрицу расстояний

	stats = new double *[3];
	for ( int i=0 ; i<3 ; i++ )
	{
		stats[i] = new double[dimension+1];
		for ( int j=0; j<=dimension ; j++ )
			stats[i][j] = 0.0;
	}

	if(debug>0) cout << "SimpCluster initialized" << endl;
	return true;
}

bool SimpCluster::alreadyHas(int *newdata, bool cycled)
{
	int ccount = dimension;
	if ( cycled ) ccount--;

	for ( int i=0 ; i<eCount ; i++ )
	{
		int equals = 0;
		for ( int k=0 ; k<ccount ; k++)
			for ( int l=0 ; l<ccount ; l++ )
				if ( elements[i].data[k] == newdata[l] ) equals++;
		if ( equals >=ccount ) return true;
	}

	return false;
}

bool SimpCluster::Find(int iteration, int *chain){

	if (iteration > 0)
	{
		for ( int i=0 ; i<aCluster->getECount() ; i++ )
		{
			if (fabs(
					aCluster->getDistance(i,chain[iteration-1])
					-aPattern->M(iteration, iteration-1)
				)<aEpsilon)
			{
				bool maybenew = true;
				for ( int j=0 ; j<iteration ; j++)
				{
					if(!aPattern->isCycled())
					{
						if(i==chain[j]) maybenew = false;
					} 
					else
					{
						if(iteration!=(aPattern->getECount()-1))
						{
							if(i==chain[j]) maybenew = false;
						}
						else
						{
							if(i!=chain[0]) maybenew = false;
						}
					}
				}
				if(maybenew)
				{
					bool correctone = true;
					if (aCluster->getType(i)==aPattern->getType(iteration)) 
					{
						if(aPattern->isHard())
							for ( int j=0 ; j<iteration ; j++ )
							{
								if(fabs(
									aCluster->getDistance(i, chain[j])
									-aPattern->M(iteration, j)
									)>aEpsilon) correctone = false;
							}
					}
					else correctone = false;
					if(correctone)
					{
						int * newchain = (int *)malloc((iteration+1)*sizeof(int));
						if ( NULL == newchain)
						{
							Errmsg("Search engine",1);
							return false;
						}
						for (int j=0 ; j<iteration ; j++) newchain[j] = chain[j];
						newchain[iteration] = i;

						if (iteration!=(aPattern->getECount()-1))
						{
							Find(iteration+1, newchain);
						}
						else if ( !this->alreadyHas(newchain, aPattern->isCycled()) )
						{
							this->appendElement(1,newchain);
						}
						free(newchain);
					}
				}
			}
		}
	}
	else
	{
		for ( int i=0 ; i<aCluster->getECount() ; i++ )
		{
			if (aCluster->getType(i) == aPattern->getType(iteration))
			{
				this->Find(1, &i);
			}
		}
	}
	return true;
}

bool SimpCluster::Filter()
{
	if(aPattern->getFilterMode()==1)
	{
		int * excluding = NULL;
		int exclCount = 0;

		for ( int i=0 ; i<this->eCount ; i++)
		{
			for ( int j=i+1 ; j<this->eCount ; j++ )
			{
				int tExclusion = -1;
				if ( elements[i].t != elements[j].t )
				{
					tExclusion = ( elements[i].t > elements[j].t ) ? i : j;
				}
				else
				{
					int coincidence = 0;
					for ( int k=0 ; k<dimension ; k++ )
					{
						for ( int l=0 ; l<dimension ; l++ )
						{
							int a = this->elements[i].data[k];
							int b = this->elements[j].data[l];
							if ( (a<0) || (b<0) ) continue;
	
							if ( a == b ) coincidence++;
						}
					}
					if ( coincidence > 3 )
					{
						tExclusion = chooseExclusion(i,j);
					}
					else if ( coincidence > 0 )
					{
						;
					}
				}
				if ( tExclusion >= 0)
				{
					exclCount++;
					excluding = (int*)realloc(excluding, exclCount*sizeof(int));
					excluding[exclCount-1] = tExclusion;
				}
			}
		}

		if ( exclCount > 0 )
		{
			deleteElements(excluding, exclCount);
		}

		if ( excluding ) free(excluding);


		return true;
	}
	else {
		Errmsg("Filter", 4);
		return false;
	}
}

int SimpCluster::chooseExclusion(int i, int j)
{
	double sumi = 0.0f;
	double sumj = 0.0f;

	for ( int k=0 ; k<dimension-1 ; k++ )
	{
	
		for ( int l=k+1 ; l<dimension ; l++ )
		{
			sumi += aCluster->getDistance(elements[i].data[k], elements[i].data[l])-aPattern->getDistance(k, l);
			sumj += aCluster->getDistance(elements[j].data[k], elements[j].data[l])-aPattern->getDistance(k, l);
		}
	}
	return (sumi>sumj) ? i : j;
}

bool SimpCluster::printStats()
{
	return true;
}

EDGE* SimpCluster::getLinks(int *linksCount)
{
	EDGE * links = NULL;
	int commonPoint[3];
	double avgAngle = 0.0;
	*linksCount = 0;
	for ( int i=0 ; i<eCount-1 ; i++ )
	{
		int q [3] = {0,0,0};
		for ( int j=i+1 ; j<eCount ; j++ )
		{
			int areNeighbours = 0;
			for ( int k=0 ; k<dimension ; k++ )
			{
				int ik = elements[i].data[k];
				if ( ik<0 ) continue;
				for ( int l=0 ; l<dimension ; l++ )
				{
					int jl = elements[j].data[l];
					if ( jl<0 ) continue;
					if ( ik == jl )
					{
						commonPoint[areNeighbours] = ik;
						areNeighbours++;
					}
				}
			}
			if ( areNeighbours>0 )
			{
				(*linksCount)++;
				links = (EDGE*)realloc(links, (*linksCount)*sizeof(EDGE));
				if ( NULL == links )
				{
					Errmsg("getLinks", 1);
					return NULL;
				}
				links[*linksCount-1].a = i;
				links[*linksCount-1].b = j;
				links[*linksCount-1].w = getAngle(i,j,commonPoint, areNeighbours);
				avgAngle += links[*linksCount-1].w;
				q[areNeighbours-1]++;
			}
		}
		for ( int j=0 ; j<3 ; j++ )
			stats[j][q[j]]++;
	}
	cout << "Average link angle " << avgAngle/(*linksCount)<<endl;
	return links;
}

double * SimpCluster::getAData(int eIndex, int aIndex)
{
	return aCluster->getElement(elements[eIndex].data[aIndex]).data;
}

double SimpCluster::getAngle(int iSimp, int jSimp, int *Points, int size)
{
	double *aPoint = new double [3];
	double *bPoint = new double [3];
	double *cPoint = new double [3];

	switch ( size )
	{
		case 1:
			for ( int i=0 ; i< 3 ; i++ ) 
				bPoint[i] = aCluster->getElement(Points[0]).data[i];
			break;
		case 2:
			aCluster->getMidPoint(Points[0], Points[1], bPoint);
			break;
		default:
			return 180.0;
	}

	if ( aPattern->getCenter() < 0 )
	{
		getCenter(iSimp, aPoint);
		getCenter(jSimp, cPoint);
	}
	else
	{
		for ( int i=0 ; i< 3 ; i++ )
		{ 
			aPoint[i] = getAData(iSimp,aPattern->getCenter())[i];
			cPoint[i] = getAData(jSimp,aPattern->getCenter())[i];
		}
	}

	double angle = Helpers::angle(aPoint, bPoint, cPoint);

	if ( aPoint ) delete [] aPoint;
	if ( bPoint ) delete [] bPoint;
	if ( cPoint ) delete [] cPoint;

	return angle;
}

void SimpCluster::getCenter(int iSimp, double *Point)
{
	for ( int i=0 ; i<3 ; i++ ) Point[i] = 0.0;
	for ( int i=0 ; i<dimension ; i++)
	{
		for ( int j=0 ; j<3 ; j++ )
		{
			Point[j] += getAData(iSimp, i)[j];
		}
	}
	for ( int i=0 ; i<3 ; i++ ) Point[i] /= dimension;
}

int* SimpCluster::getListOfTypes()
{
	int *tlist = (int*)malloc(eCount*sizeof(int));
	for ( int i=0 ; i<eCount ; i++ )
		tlist[i] = elements[i].t;
	return tlist;
}

bool SimpCluster::saveAsGraph()
{

	int lnkCnt;
	EDGE *links;
	Graph *aGraph = new Graph(debug);

	aGraph->setVerticles(getListOfTypes(), getECount());
	links=getLinks(&lnkCnt);
	aGraph->setEdges(links, lnkCnt);
	aGraph->normalizeAngles();
	aGraph->saveToFile("nodes","links");
	if(aGraph) delete aGraph;

	return true;
}

void SimpCluster::showStats()
{
	cout << "Stats:"<<endl;
	string str;
	str="QRS";
	
	for ( int j=0 ; j<=dimension ; j++ )
	{
		cout << str[0]<<j<<": "<<stats[0][j] << "\t\t"
			<<  str[1]<<j<<": "<<stats[1][j] << "\t\t"
			<<  str[2]<<j<<": "<<stats[2][j] << "\n";
	}
}
