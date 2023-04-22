#include <iostream>
#include <map>
#include <typeinfo>
#include "NameServer.h"
// #include "util.h"

using std::string;
using std::cout;
using std::endl;

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
            cout << message << endl;
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
		cout<<"New Servant registering..."<<endl;
		nsobj.port = stoi(vet.at(1));
		nsobj.name = vet.at(2);
		names.insert(std::pair{nsobj.name, nsobj});
		cout<<"IP: "<< nsobj.ip << endl <<"Port: " << nsobj.port << endl << "name: " << nsobj.name << endl;
		for(auto& p: names)
			cout<< p.first << endl;
		resp = nsobj.name + " registered to ORB";
		break;

	case NSFIND:
		cout<<"New request for servant:  "<<vet.at(1)<<endl;
		resp = "0/not found in Name Server";
		auto it = names.find(vet.at(1));
		if(it != names.end())
			resp = it->second.ip + "/" + std::to_string(it->second.port) + "/" + it->second.name;
		break;
	}

//write operation
	send_(socket, resp);
}
