#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <boost/asio.hpp>

#include "util.h"

using namespace std;
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

class Client {
private:
    boost::asio::io_service io_service;
    // ip::tcp::resolver resolver(io_service);
public:
    string send(string destip, int destport, string message);
};

#endif