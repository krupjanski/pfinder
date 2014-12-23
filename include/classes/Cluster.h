#pragma once

#include <define.h>
#include <classes/Base.h>

using namespace std;

template <class data_t> class Cluster : public Base{

	public:

		//Properties

		//Methods
		OBJECT<data_t> getElement(int index);
		bool appendElement(int newT, data_t *newdata);
		bool deleteLast();
		bool setECount(int newECount);
		bool getDataFromFile(string fileName, int rmode);
		int getDim();
		int getECount();
		int getType(int index);
		int getTCount();
		string dataPreview(int size);
		string showElementData(int index);
		void setTCount(int newTCount);
		bool saveToFile(string fileName);
		bool deleteElements(int * list, int lsize);

		virtual void setData(int index, int newT, data_t *newdata);
		virtual bool readAdditional(string header, ifstream *file){return true;}

		Cluster(int newdeb);
		virtual ~Cluster();

	protected:

		//Properties
		OBJECT<data_t>* elements;
		int dimension;
		int eCount;
		int tCount;
		bool dimOverridden;

		//Methods

};
