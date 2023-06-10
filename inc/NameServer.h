#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <boost/asio.hpp>
#include <iostream>
#include <map>

#include "../inc/def.h"
#include "../inc/util.h"

struct NSOBJ{
	string ip;
	int port;
	string name;
};

class NameServer {
private:
	int lport;
	boost::asio::io_service io_service;
	string message;
	std::map<string, NSOBJ> names;

	void elab(boost::asio::ip::tcp::socket & socket, string msg);
public:
	NameServer (int port);

	void start();

};

#endif
