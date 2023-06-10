#include <iostream>
#include <sstream>

#include "ORB.h"
#include "Car.h"
//#include "Plane.h"

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
//using namespace std;

class gps_position
{
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & degrees;
        ar & minutes;
        ar & seconds;
    }
    int degrees;
    int minutes;
    float seconds;
public:
    gps_position(int d=0, int m=0, float s=0) :
        degrees(d), minutes(m), seconds(s)
    {}
    void print() {
    	std::cout<<degrees<<std::endl;
    }
};

int main(int argc, char *argv[]) {
//    // create and open a character archive for output
//	std::ostringstream oss;
//
//    // create class instance
//    const gps_position g(39, 59, 24.567f);
//    // save data to archive
//    {
//        boost::archive::text_oarchive oa(oss);
//        // write class instance to archive
//        oa <<  g;
//        std::cout<<oss.str()<<std::endl;
//    	// archive and stream closed when destructors are called
//    }
//
//    // ... some time later restore the class instance to its orginal state
//    gps_position newg;
//    {
//        // create and open an archive for input
//    	std::istringstream iss(oss.str());
//        boost::archive::text_iarchive ia(iss);
//        // read class state from archive
//        ia >> newg;
//        newg.print();
//        // archive and stream closed when destructors are called
//    }
//    return 0;

	Car* c1 = new Car("Car1");
	c1->accel(5.5, 5);
	c1->brake(10);
//	 Car* c2 = new Car("Car2");
//	 c2->accel(10, 3);
//	 c1->brake(4);
//	Plane* p1 = new Plane("Plane1");
//	p1->take_off(25);
	
	return 0;
}
