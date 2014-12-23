#include <classes/Base.h>

Base::Base(int newdeb)
{
	debug = newdeb;
	msgCount = 4;
	msg = new string [msgCount];
	msg[0] = "File not found";
	msg[1] = "Memory allocation error";
	msg[2] = "File access error";
	msg[3] = "Wrong data format";


	if(debug>0) cout << "Base object created" << endl;	
}

Base::~Base()
{
	if(msg) delete [] msg;
	if(debug>0) cout << "Base object terminated" << endl;	
}

void Base::Errmsg(string Place, int code)
{
	cout << "::::Error: " << Place <<" - "<<msg[code]<<endl;
}

int Base::Errappend(string newerror)
{
	string *tmparr = new string [msgCount+1];
	memcpy(tmparr, msg, msgCount);
	tmparr[msgCount] = newerror;
	delete [] msg;
	msg = tmparr;
	msgCount++;
	return msgCount;
}
