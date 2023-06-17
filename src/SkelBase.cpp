//include

#include <sstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using std::string;
using std::endl;
using namespace std;

//constructor

//skeldispatch
	// DEVO CHIAMARE accel o brake IN BASE AL MESSAGGIO RICEVUTO
	string resp = "No function find";
	std::istringstream iss;
	auto it = ser.find(vet.at(0));
	if(it != ser.end()) {
		if(vet.size() > 2) {
			iss.str(vet.at(2));
		}
		switch(fns[vet.at(1)]) {
//interface
		}
	}
	return resp;
}
