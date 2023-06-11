#ifndef ORB_H
#define ORB_H

#include <thread>
#include <boost/variant.hpp>

#include "Client.h"
#include "def.h"
#include "NameServer.h"
#include "Service.h"
#include "Skel.h"
#include "SkelServer.h"

using namespace std;
using std::string;

class ORB {
private:
	int skport;
	SkelServer* skelsrv = NULL;
	thread* skelt = NULL;

public:
	ORB();

	~ORB();

	bool find(string ifname, string name, string* s);

	bool deploy(Service* obj);
};

#endif
