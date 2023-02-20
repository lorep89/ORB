#include <iostream>
#include <thread>
#include "NameServer.h"
#include "util.h"
#include "def.h"

using namespace std;

int main() {
	NameServer* ns;
	int nsport = stoi(NSPORT);
	ns = new NameServer(nsport);
	thread nst(&NameServer::start, ns);
	nst.join();
}
