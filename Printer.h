#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <sstream>

using namespace std;

_Monitor Printer {
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	void flush();
	void finish();
	string convert(int i);
	string convert(char c);

	string parent;
	string watcard;
	string nameServer;
	string truck;
	string plant;
	string * studentBuffer;
	string * vendingMachineBuffer;
	string * courierBuffer;
public:
	enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	~Printer();
	void print( Kind kind, char state );
	void print( Kind kind, char state, int value1 );
	void print( Kind kind, char state, int value1, int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, int value1 );
	void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif // PRINTER_H
