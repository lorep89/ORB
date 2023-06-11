#ifndef SKELSERVER_H
#define SKELSERVER_H

#include <map>
#include <boost/asio.hpp>
#include <boost/tokenizer.hpp>
#include <boost/variant.hpp>
#include "def.h"
#include "Service.h"
#include "Skel.h"
#include "util.h"

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
	SkelServer(int port);

	bool add(Service* obj);

	void start();
};

#endif
