#include <classes/Cluster.h>

template <class data_t> 
Cluster<data_t>::Cluster(int newdeb) : Base(newdeb) {

	dimension = 3;
	elements = NULL;
	dimOverridden = false;
	eCount = 0;
	tCount = 0;

	if(debug>0) cout << "Cluster object created" << endl;

}

template <class data_t> 
Cluster<data_t>::~Cluster() 
{

	for ( int i=0 ; i<eCount ; i++)
	{
		if (NULL!=elements[i].data) free(elements[i].data);
	}
	if(NULL!=elements) free(elements);

	if(debug>0) cout << "Cluster object terminated" << endl;
}

template <class data_t> 
int Cluster<data_t>::getType(int index){
	return elements[index].t;
}

template <class data_t> 
void Cluster<data_t>::setTCount(int newTCount){
	tCount = newTCount;
}

template <class data_t> 
int Cluster<data_t>::getECount(){
	return eCount;
}

template <class data_t> 
int Cluster<data_t>::getTCount(){
	return tCount;
}


template <class data_t> 
bool Cluster<data_t>::appendElement(int newT, data_t *newdata){
	eCount++;
	elements=(OBJECT<data_t>*)realloc(elements, eCount*sizeof(OBJECT<data_t>));
	if(NULL==elements) 
	{
		Errmsg("Cluster",1);
		return false;
	}

	elements[eCount-1].data=(data_t*)malloc(dimension*sizeof(data_t));
	if(NULL==elements[eCount-1].data) 
	{
		Errmsg("Cluster",1);
		return false;
	}
	
	setData(eCount-1, newT, newdata);

	return true;
}

template <class data_t> 
bool Cluster<data_t>::setECount(int newECount){
	eCount = newECount;
	elements=(OBJECT<data_t>*)realloc(elements, eCount*sizeof(OBJECT<data_t>));
	if(NULL==elements) {
		Errmsg("Cluster",1);
		return false;
	}
	for ( int i=0 ; i< eCount ; i++ )
	{
		elements[i].data = (data_t*)malloc(dimension*sizeof(data_t));
	}
	return true;
}

template <class data_t> 
void Cluster<data_t>::setData(int index, int newT, data_t *newdata){

	elements[index].t=newT;
	memcpy(
		elements[index].data, 
		newdata, 
		dimension*sizeof(data_t));

}

template <class data_t> 
OBJECT<data_t> Cluster<data_t>::getElement(int index){
	return elements[index];
}

template <class data_t> 
string Cluster<data_t>::showElementData(int index){
	stringstream s;
	s << elements[index].t << "\t";	
	for( int i=0 ; i<dimension ; i++)
		s<< elements[index].data[i]<<"\t";
	return s.str();
}

template <class data_t> 
string Cluster<data_t>::dataPreview(int size){
	stringstream s;
	s << "\tData:" << endl;
	for (int i=0; i<size; i++) 
		s << "\t" << showElementData(i) << endl;
	s << "\t"<< "..." << endl;
	for (int i=eCount-size; i<eCount; i++) 
		s << "\t" << showElementData(i) << endl;
	return s.str();
}

template <class data_t> 
bool Cluster<data_t>::getDataFromFile(string fileName, int rmode){
	string line;
	string tmp;
	size_t found, found2;
	int npart;
	ifstream cfile;

	struct stat buffer;
	if(!(stat (fileName.c_str(), &buffer) == 0))
	{
		if(debug>0) Errmsg(fileName,0);
		return false;
	}

	if(debug>0) cout << "Reading file " << fileName << "..." << endl;

	cfile.open(fileName.c_str());
	if(cfile.is_open())
	{
		while(cfile.good()){
			getline(cfile, line);
			if((line.compare(0,1,"#")==0)&&(debug>0)) cout << line << endl;
			else{
				found = line.find("npart");
				if(found!=string::npos){
					getline (cfile,tmp);
					sscanf(tmp.c_str(),"%d%d",&npart,&tCount);
					if(debug>0) {
						cout << "Found " << npart << " elements of "
							<< tCount << " different kinds in Cluster!" << endl;
					}
					if(!setECount(npart)) return false;
				}
				found = line.find("Dimension");
				if(found!=string::npos){
					int tmpdim;
					getline (cfile,tmp);
					sscanf(tmp.c_str(),"%d",&tmpdim);
					if ( tmpdim != dimension ) dimOverridden = true;
					dimension = tmpdim;
					if(debug>0) {
						cout << "Cluster element dimension: " << dimension << endl;
					}
				}
				if(!readAdditional(line, &cfile)) return false;
				found = line.find("Coordinates");
				found2 = line.find("Data");
				if((found!=string::npos)||(found2!=string::npos)){
					for(int i=0; i<eCount;i++){
						getline (cfile,tmp);
						std::istringstream iss( tmp );
						if(rmode==1)
						{
							int junk;
							iss >> junk;
							iss >> junk;
						}

						int newtype;
						data_t *newdata = (data_t*)malloc(dimension*sizeof(data_t));
						if(NULL)
						{
							Errmsg("Cluster", 1);
							return false;
						}

						iss >> newtype;
						for ( int j=0 ; j<dimension ; j++ )
						{
							iss >> newdata[j];
						}
						setData(i, newtype, newdata);
						free(newdata);

					}
				}
			}
		}
		cfile.close();
		if(debug>0) {
			cout << "File "<<fileName << " read ok!" << endl;
			cout << dataPreview(3);
		}
		return true;
	}
	else
	{
		if(debug>0) Errmsg(fileName,2);
		return false;
	}	
}

template <class data_t> 
bool Cluster<data_t>::saveToFile(string fileName)
{
	ofstream resfile;
	resfile.open(fileName.c_str());

	if (resfile.is_open())
	{
		resfile << "npart" << endl
				<< eCount << "\t" <<tCount <<endl
				<< "Dimension" << endl 
				<< dimension << endl 
				<< "Data" << endl;
		for (int i=0 ; i<eCount ; i++) 
		{
				resfile << showElementData(i) << endl;
		}	
		resfile.close();
	}
	else return false;
	return true;
}

template <class data_t> 
int Cluster<data_t>::getDim()
{
	return dimension;
}

template <class data_t>
bool Cluster<data_t>::deleteLast()
{
	eCount--;
	elements = (OBJECT<data_t>*)realloc(elements, eCount*sizeof(OBJECT<data_t>));
	if(NULL==elements) {
		Errmsg("Cluster",1);
		return false;
	}
	return true;
}

template <class data_t>
bool Cluster<data_t>::deleteElements(int * list, int lsize)
{
	if ( debug>0 ) cout << lsize << " elements are marked for deletion" << endl;
	OBJECT<data_t>* newelements = NULL;//(OBJECT<data_t>*)malloc(eCount*sizeof(OBJECT<data_t>));
	int newecount = 0;
	for ( int i=0 ; i<eCount ; i++ )
	{
		bool include = true;
		for ( int j=0 ; j<lsize ; j++ )
		{
			if ( i == list[j]) {
				include = false;
			}
		}
		if ( include )
		{
			newecount++;
			newelements = (OBJECT<data_t>*)realloc(newelements, newecount*sizeof(OBJECT<data_t>));
			if ( NULL == newelements ) 
			{
				Errmsg("Cluster", 1);
				return false;
			}
			newelements[newecount-1]=elements[i];
		}
		else if ( elements[i].data ) free(elements[i].data);
	}
	if ( debug>0 ) cout << newecount << " elements are saved" << endl;
	free(elements);
	elements = newelements;
	eCount = newecount;

	return true;
}
template class Cluster<double>;
template class Cluster<int>;
