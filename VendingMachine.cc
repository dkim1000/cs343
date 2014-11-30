#include "VendingMachine.h"


/* public */

// Constructor
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour )
    : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour) {
    
    for ( unsigned int i = 0; i < NUM_FLAVOURS; i += 1 ) {
	stocks[i] = 0;
    }
    isRestocking = false;
    nameServer.VMregister(this);
} // VendingMachine::VendingMachine


void VendingMachine::buy( Flavours flavour, WATCard &card ) {
    // TODO: need a flag variable to correctly throw these exceptions..?

    if ( stocks[flavour] <= 0 ) {        // No stock remaining for the flavour
        throwStock = true;
	uRendezvousAcceptor();
	return;
    }  

    if ( card.getBalance() < sodaCost ) {// Not enough fund on the watcadr
	throwFunds = true;
	uRendezvousAcceptor();
	return;
    }

    card.withdraw( sodaCost );           // deduct the cost from watcard balance
    stocks[flavour] -= 1;                // decrement number of stocks

    printer.print( Printer::Vending, id, 'B', flavour, stocks[flavour] );
}

// start restocking
unsigned int *VendingMachine::inventory() {
    isRestocking = true;
    return stocks;
}

// finished restocking
void VendingMachine::restocked() {
    isRestocking = false;
}

// getter for sodaCost
_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

// getter for id
_Nomutex unsigned int VendingMachine::getId() {
    return id;
}


/* private */

void VendingMachine::main() {
    printer.print( Printer::Vending, id, 'S', sodaCost );

    while ( 1 ) {
	_Accept( ~VendingMachine ) {
	    break;
	} or _When ( !isRestocking ) _Accept ( buy, inventory ) {
	    if ( throwStock ) {
		throw Stock();
	    } else if ( throwFunds ) {
		throw Funds();
	    }
	    printer.print( Printer::Vending, id, 'r' );
	} or _When ( isRestocking ) _Accept ( restocked ) {
	    printer.print( Printer::Vending, id, 'R' );
	}
    }

    printer.print( Printer::Vending, id, 'F' );
}





