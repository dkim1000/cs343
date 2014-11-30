#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : 
printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
	numRegisteredMachines = 0;
	assignment = new int[numStudents];
	machines = new VendingMachine*[numVendingMachines];

	//Initial assignments for students
	for (unsigned int i = 0 ; i < numStudents ; i++) {
		assignment[i] = i % numVendingMachines;
	}
}

NameServer::~NameServer() {
	delete[] assignment;
	delete[] machines;
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
	int id = vendingmachine->getId();
	printer.print(Printer::NameServer, 'R', id);
	machines[numRegisteredMachines++] = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id ) {
	VendingMachine *ret = machines[assignment[id]];
	printer.print(Printer::NameServer, 'N', id, ret->getId());
	assignment[id] = (assignment[id] + 1) % numVendingMachines;

	return ret;
}

VendingMachine **NameServer::getMachineList() {
	return machines;
}


void NameServer::main() {
    printer.print( Printer::NameServer, 'S' );
    while ( 1 ) {
		_Accept( ~NameServer ) {
		    break;
		} or _When ( numRegisteredMachines < numVendingMachines ) _Accept( VMregister ) {
		} or _When ( numRegisteredMachines == numVendingMachines ) _Accept( getMachine, getMachineList ) {
		}
    }

    printer.print( Printer::NameServer, 'F' );

}
