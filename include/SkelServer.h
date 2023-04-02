#ifndef SKELSERVER_H
#define SKELSERVER_H


#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/tokenizer.hpp>
#include <boost/variant.hpp>
#include <boost/thread.hpp>
#include "Skel.h"
#include "Service.h"
#include "util.h"
#include "def.h"

class Skel;
class Service;

typedef std::map<string, Skel*> Skelmap;

using std::string;

class SkelServer {
private:
	int lport;
	Skelmap skels;
	Skel* skel;
	boost::asio::io_service io_service;
	string message;
	
	void elab(boost::asio::ip::tcp::socket & socket, string msg);

public:
	SkelServer() {};

	SkelServer(int port);

	bool add(Service* obj);

	void start();
};

#endif
