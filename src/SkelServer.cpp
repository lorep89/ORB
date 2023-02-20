#include <iostream>
#include <map>
#include <typeinfo>
#include "SkelServer.h"

using std::string;
using std::cout;
using std::endl;

SkelServer::SkelServer (int port) {
	lport = port;
	cout<<"SkelServer created. Port: "<<port<<endl;
}

bool SkelServer::add(Service* obj) {
	auto it = skels.find(obj->getType());
	if (it != skels.end()) {
		skel = skels[obj->getType()];
		skel->add(obj);
	}
	else {
		skel = obj->makeSkel();
		skels.insert(Skelmap::value_type(obj->getType(), skel));
		skel->add(obj);
	}
	return true;
}

void SkelServer::start() {
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

void SkelServer::elab(boost::asio::ip::tcp::socket & socket, string msg) {
	string resp = "err";
	// nsobj.ip = socket.remote_endpoint().address().to_string();
	std::vector<string> vet = splitMsg(msg);
	auto it = skels.find(vet.at(0));
	if(it != skels.end()) {
		vet.erase(vet.begin());
		resp = it->second->dispatch(vet);
	}
//write operation
	send_(socket, resp);
}
