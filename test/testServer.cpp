#include "ORB.h"
#include "Carservice.h"
#include "Planeservice.h"

using namespace std;

int main() {
	ORB myORB;
//	myORB.init();

	Carservice* c1;
	// Carservice* c2;
	Planeservice* p1;

	c1 = new Carservice("Car1");
	myORB.deploy(c1);
	cout<<c1->getName()<<" deployed"<<endl;

	// c2 = new Carservice("Car2");
	// myORB.deploy<Carservice>(c2);
	// cout<<c2->getName()<<" deployed"<<endl;

	p1 = new Planeservice("Plane1");
	myORB.deploy(p1);
	cout<<p1->getName()<<" deployed"<<endl;

//	delete(myORB);
//	myORB.shutdown();
	return 0;
}
