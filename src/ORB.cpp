#include "ORB.h"
// #include "util.h"

using namespace std;

bool ORB::find(string ifname, string name, string* s) {
		Client c;
		bool found = false;

		string msg = to_string(NSFIND) + "/" + name;
		int nsport = stoi(NSPORT);
		string resp = c.send(NSIP, nsport, msg);
		std::vector<string> vet = splitMsg(resp);
		if(vet.at(0) == "0")
			cout<<"Proxy not found"<<endl;
		else {
			found = true;
			s[0] = vet.at(0);
			s[1] = vet.at(1);
		}
		return found;
}

void ORB::deploy(Service* obj) {
	Client c;
	cout<<"deploing: "<<obj->getName()<<endl;

	bool dep = skelsrv->add(obj);
	if(dep) {
		string msg = to_string(NSREG) + "/" + SKPORT + "/" + obj->getName();
		int nsport = stoi(NSPORT);
		c.send(NSIP, nsport, msg);
	}
	return;	
}

void ORB::init() {
	skport = stoi(SKPORT);
	skelsrv = new SkelServer(skport);
	skelt = new thread(&SkelServer::start, skelsrv);
}

void ORB::shutdown() {
	// for(int i=0; i<(int)(skelts.size()); ++i)
	skelt->join();
}