#ifndef SKEL_H
#define SKEL_H

#include <boost/asio.hpp>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/variant.hpp>
#include <iostream>

using std::string;

class Service;

class Skel{
private:

public:
	Skel(){};

	virtual ~Skel(){};

	virtual string dispatch(std::vector<string> vet) = 0;

	virtual void add(Service* obj) = 0; 
};

#endif
