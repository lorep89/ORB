#ifndef ORB_H
#define ORB_H

#include <thread>
#include <boost/variant.hpp>

#include "../inc/Client.h"
#include "../inc/def.h"
#include "../inc/NameServer.h"
#include "../inc/Service.h"
#include "../inc/Skel.h"
#include "../inc/SkelServer.h"

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

	void deploy(Service* obj);

	void init();

	void shutdown();
};

#endif
