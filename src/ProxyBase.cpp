//include
#include "util.h"

using std::string;
using std::cout;
using std::endl;

//constructor
	ORB myORB;
	string s[2];
	bool found = myORB.find(type, cname, &s[0]);
	if (found) {
		name = cname;
		destIP = s[0];
		destPort = stoi(s[1]);
	}
	else
		cout<<"Object not found in NameServer"<<endl;
}


// DEFINITE DA INTERFACCIA
//interface
