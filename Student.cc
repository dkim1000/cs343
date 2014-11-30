#include "MPRNG.h"
#include "Student.h"
#include "VendingMachine.h"
#include "config.h"  // WATCARD_INITIAL_BALANCE, NUM_FLAVOURS

/* public */

// Constructor
Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases )
	: printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases) {
    numPurchase = mprng( 1, maxPurchases );
    favFlavour = mprng( NUM_FLAVOURS - 1 );
}



/* private */
void Student::main() {
    printer.print( Printer::Student, id, 'S', favFlavour, numPurchase );
    
    FWATCard watcard = cardOffice.create( id, WATCARD_INITIAL_BALANCE );
    
    VendingMachine *vm = nameserver.getMachine( id );
    printer.print( Printer::Student, id, 'V', vm->getId() );
    
    for ( unsigned int i = 0; i < numPurchase; i += 1 ) {
	yield ( mprng ( 1, 10 ) );
	

	// try buying a soda. Exits infinite loop only after a successful buy
	while ( 1 ) {
	    try {
		vm->buy( (VendingMachine::Flavours)favFlavour, *watcard );
		printer.print( Printer::Student, id, 'B', watcard() );
		break;
	    } catch ( _Event e ) {
		switch (e) {
		case VendingMachine::Stock: // out of stock; try another vending machine
		    vm = nameServer.getMachine(id);
		    printer.print( Printer::Student, id, 'V', vm->getId() );
		    continue;
		case VendingMachine::Funds: // out of funds; transfer money
		    watcard = cardOffice.transfer( id, WATCARD_INITIAL_BALANCE + vm->cost(), watcard() );
		    continue;
		case WATCardOffice::Lost:   // lost card; create new one
		    printer.print( 
		    break;
		}
	    }

	}

    }

    delete watcard();
    printer.print( Printer::Student, id, 'F' );
}

