//guard
#include <boost/asio.hpp>

#include "Client.h"
#include "ORB.h"
//include

//class
private:
	Client c;
	string destIP;
	int destPort;
	string name;
	string type;

public:
//constructor

	string getIP () {return destIP;};

	int getPort() {return destPort;};

//interface
};

#endif
