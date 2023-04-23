//guard

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/tokenizer.hpp>
#include <boost/variant.hpp>
#include <boost/thread.hpp>

#include "../../inc/Service.h"
#include "../../inc/Skel.h"
#include "../../inc/util.h"

using std::string;

//class
	std::map<string, int> fns;
	
//makeskel

public:
//constructor

	string dispatch(std::vector<string> vet) override;

	void add(Service* obj) override;
};

#endif
