#include "ORB.h"
// #include "util.h"

using namespace std;

ORB::ORB(){
	skport = stoi(SKPORT);
}

ORB::~ORB(){
	cout<<"ORB destructor"<<endl<<endl;
	if (skelt) {
		skelt->join();
		delete(skelsrv);
	}
}

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

bool ORB::deploy(Service* obj) {
	Client c;
	bool deployed = true;
	cout<<"Deploing: "<<obj->getName()<<endl;

	//Check if another servant with the same name is already present in name server
	string msg = to_string(NSFIND) + "/" + obj->getName();
	int nsport = stoi(NSPORT);
	string resp = c.send(NSIP, nsport, msg);
	std::vector<string> vet = splitMsg(resp);
	if(vet.at(0) != "0") {
		deployed = false;
		cout<<obj->getName()<<" already present in Nameserver"<<endl;
	}
	else { // Servant is not present in name server, try to add it locally
		if(!skelsrv) {
			skelsrv = new SkelServer(skport);
			skelt = new thread(&SkelServer::start, skelsrv);
		}
		bool dep = skelsrv->add(obj);
		if(dep) {
			msg = to_string(NSREG) + "/" + SKPORT + "/" + obj->getName();
			resp = c.send(NSIP, nsport, msg);
			vet = splitMsg(resp);
		}
		else {
			deployed = false;
			cout<<obj->getName()<<" already present locally"<<endl;
		}
	}
	return deployed;
}
