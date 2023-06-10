//include
#include "util.h"
#include <sstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
