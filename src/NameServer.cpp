#include <map>
#include <typeinfo>
#include <boost/tokenizer.hpp>
#include "NameServer.h"

//using std::string;
//using std::cout;
//using std::endl;
using namespace std;
// cout << "Peer IP: " << socket_.remote_endpoint().address().to_string() << std::endl;

NameServer::NameServer (int port) {
	lport = port;
	cout<<"NameServer created. Port: "<<port<<endl;
}

void NameServer::start() {
//listen for new connection
      boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), lport ));
//socket creation
      while(true) {
//waiting for connection
            boost::asio::ip::tcp::socket socket_(io_service);
            acceptor_.accept(socket_);
//read operation
            message = receive_(socket_);
//            cout << "Received message: "<< message << endl;
//elaboration of message
            elab(socket_, message);
      }
      return;
}

void NameServer::elab(boost::asio::ip::tcp::socket & socket, string msg) {
	NSOBJ nsobj;
	nsobj.ip = socket.remote_endpoint().address().to_string();
	std::vector<string> vet = splitMsg(msg);
	string resp = "err";
	switch (std::stoi(vet.at(0))) {
	case NSREG:
	{
		cout<<"New Servant registering..."<<endl;
		resp="0/Servant already present";
		nsobj.port = stoi(vet.at(1));
		nsobj.name = vet.at(2);
		auto reg = names.find(nsobj.name);
		if(reg != names.end()) {
			cout<<"Servant already present:"<<endl;
			for(auto& p: names)
				cout<< p.first << endl;
		}
		else {
			names.insert(std::pair{nsobj.name, nsobj});
			cout<<"Servant registered"<<endl;
			cout<<"IP: "<< nsobj.ip << endl <<"Port: " << nsobj.port << endl << "name: " << nsobj.name << endl;
			resp = "1/" + nsobj.name + " registered to ORB";
		}
		break;
	}
	case NSFIND:
	{
		cout<<"New request for servant:  "<<vet.at(1)<<endl;
		resp = "0/Not found in Name Server";
		auto found = names.find(vet.at(1));
		if(found != names.end())
			resp = found->second.ip + "/" + std::to_string(found->second.port) + "/" + found->second.name;
		break;
	}
	}

//write operation
	send_(socket, resp);
}
