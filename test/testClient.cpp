#include <iostream>
// #include "ORB.h"
#include "Car.h"
#include "Plane.h"

using namespace std;

int main(int argc, char *argv[]) {
	// ORB myORB;
	// bool found; 
	Car* c1 = new Car("Car1");
	c1->accel(5, 5);
	c1->brake(10);
	// Car* c2 = new Car("Car2");
	// c2->accel(10, 3);
	// c1->brake(4);
	// Car* c1 = myORB.find<Car>("Car1", found);
	// cout<<found<<endl;
	// cout<<c1->getPort()<<endl;
	// c1->accel(10, 5);

	Plane* p1 = new Plane("Plane1");
	p1->take_off(25);
	
	return 0;
}
