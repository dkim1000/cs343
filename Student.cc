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
    
    WATCard::FWATCard watcard = cardOffice.create( id, WATCARD_INITIAL_BALANCE );
    
    VendingMachine *vm = nameServer.getMachine( id );
    printer.print( Printer::Student, id, 'V', vm->getId() );
    
    for ( unsigned int i = 0; i < numPurchase; i += 1 ) {
	yield ( mprng ( 1, 10 ) );
	

	// try buying a soda. Exits infinite loop only after a successful buy
	while ( 1 ) {
	    try {
		vm->buy( (VendingMachine::Flavours)favFlavour, *watcard() );
		printer.print( Printer::Student, id, 'B', watcard()->getBalance() );
		break;
	    } catch ( VendingMachine::Stock ) {
		vm = nameServer.getMachine(id);
		printer.print( Printer::Student, id, 'V', vm->getId() );
		continue;
	    } catch ( VendingMachine::Funds ) {
		watcard = cardOffice.transfer( id, WATCARD_INITIAL_BALANCE + vm->cost(), watcard() );
		continue;

	    } catch ( WATCardOffice::Lost ) {
		printer.print( Printer::Student, id, 'L');
		watcard = cardOffice.create( id, WATCARD_INITIAL_BALANCE );
		continue;

	    }

	}

    }

    delete watcard();
    printer.print( Printer::Student, id, 'F' );
}

