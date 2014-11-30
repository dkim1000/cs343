#ifndef NAME_SERVER_H
#define NAME_SERVER_H

#include "Printer.h"

_Task VendingMachine;

_Task NameServer {
	Printer &printer;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	unsigned int numRegisteredMachines;

	int * assignment;
	VendingMachine ** machines;

    void main();
  public:
    ~NameServer();
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};


#endif // NAME_SERVER_H
