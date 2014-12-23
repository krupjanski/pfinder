#include <classes/Application.h>

Application::Application(int newdeb) : Base(newdeb) {

	if(debug>0) cout << "Application created" << endl;
}

Application::~Application() {

	if(debug>0) cout << "Application terminated" << endl;
}

float Application::getVersion() {
	return version;
}

string Application::getName() {
	return name;
}

string Application::getFullInfo(){
	stringstream s;
	s << "Author:\t\t\t" << author << endl;
	s << "Application name:\t" << name << endl; 
	s << "Current version:\t" << version << endl;
	s << "Year:\t\t\t" << year << endl;
	return s.str();	
}

void Application::setDebugLevel(int newLevel) {
	debug = newLevel;
};

int Application::getDebugLevel() {
	return debug;
};

