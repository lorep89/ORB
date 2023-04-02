#ifndef ORB_H
#define ORB_H

#include <thread>
#include <boost/variant.hpp>
#include "SkelServer.h"
#include "Skel.h"
#include "Service.h"
#include "NameServer.h"
#include "Client.h"
#include "def.h"

using namespace std;
using std::string;

class ORB {
private:
	int skport;
	SkelServer* skelsrv;
	thread* skelt;

public:
	bool find(string ifname, string name, string* s);

	void deploy(Service* obj);

	void init();

	void shutdown();
};

#endif