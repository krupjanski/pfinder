#pragma once

#include <define.h>
#include <classes/Base.h>

using namespace std;

class Application : public Base{

	public:

		//Properties

		//Methods
		Application(int newdeb);
		virtual ~Application();

		static float getVersion();
		static string getName();
		static string getFullInfo();
		virtual bool Init(int argc, char** argv) = 0;
		virtual bool Start() = 0;
		void setDebugLevel(int newLevel);
		int getDebugLevel();

	protected:

		//Properties
		static const float version;
		static const string name;
		static const string author;
		static const int year;

		//Methods
						
};
