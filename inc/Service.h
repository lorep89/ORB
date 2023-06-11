#ifndef SERVICE_H
#define SERVICE_H

#include "../inc/Skel.h"

class Service {
private:
	string name;
	string type;

public:
	Service(string sname, string stype) {
		this->name = sname;
		this->type = stype;
	};

	virtual ~Service() {};
	
	string getName() {return this->name;};

	string getType() {return this->type;};

	virtual	Skel* makeSkel() = 0;

};

#endif