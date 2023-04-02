#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <boost/asio.hpp>
#include <map>
#include <boost/tokenizer.hpp>
// #include "Server.h"
#include "util.h"
#include "def.h"

struct NSOBJ{
	string ip;
	int port;
	string type;
};

class NameServer {
private:
	int lport;
	boost::asio::io_service io_service;
	string message;
	std::multimap<string, NSOBJ> names;

	void elab(boost::asio::ip::tcp::socket & socket, string msg);
public:
	NameServer();

	NameServer (int port);

	void start();

};

#endif