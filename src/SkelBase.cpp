//include

using std::string;
using std::endl;
using namespace std;

//constructor

//skeldispatch
	// DEVO CHIAMARE accel o brake IN BASE AL MESSAGGIO RICEVUTO
	string resp = "No function find";
	// std::vector<string> vet = splitMsg(msg);
	auto it = ser.find(vet.at(0));
	if(it != ser.end()) {
		switch(fns[vet.at(1)]) {
//interface
		}
	}
	return resp;
}
