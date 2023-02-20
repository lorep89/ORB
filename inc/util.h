#ifndef UTIL_H
#define UTIL_H

#include <boost/asio.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>

using std::string;

string receive_(boost::asio::ip::tcp::socket & socket);

void send_(boost::asio::ip::tcp::socket & socket, const string& message);

std::vector<string> splitMsg(string msg);

#endif