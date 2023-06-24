#include <iostream>
#include <sstream>

#include "ORB.h"
#include "Car.h"
#include "Plane.h"

//using namespace std;

int main(int argc, char *argv[]) {

	Car* c1 = new Car("Car1");
	string sret = c1->accel("pippo", 5);
	cout<<"Car1_accel return: "<<sret<<endl<<endl;
	int iret = c1->brake(10);
	cout<<"Car1_brake return: "<<iret<<endl<<endl;

	Car* c2 = new Car("Car2");
	sret = c2->accel("Pluto", 3);
	cout<<"accel return: "<<sret<<endl<<endl;

	Plane* p1 = new Plane("Plane1");
	iret = p1->take_off();
	cout<<"take_off return: "<<iret<<endl<<endl;
	
	return 0;
}
