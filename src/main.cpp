#include <classes/MyApplication.h>

using namespace std;

int main( int argc, char** argv ){


	MyApplication *MyApp;
	MyApp = new MyApplication(0);

//	cout << MyApp->getFullInfo();

	if(!MyApp->Init(argc, argv)) {
		cout << "Application initialization failed" << endl;
		delete MyApp;
		exit(1);
	}

	if(!MyApp->Start()){
		cout << "Application failed" << endl;
		delete MyApp;
		exit(1);
	}

	if(MyApp) delete MyApp;
	return 0;
}
