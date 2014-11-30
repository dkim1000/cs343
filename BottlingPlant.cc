#include "BottlingPlant.h"
#include "MPRNG.h"

/* Public */

// Constructor
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
			      unsigned int timeBetweenShipments ) 
    : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
      maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
      timeBetweenShipments(timeBetweenShipments) {
    
    // create truck
    truck = new Truck( printer, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    // initialize produced array to 0
    for ( unsigned int i = 0; i < NUM_FLAVOURS; i += 1 ) {
	produced[i] = 0;
    }
}

// destructor; destroy truck
BottlingPlant::~BottlingPlant() {
    delete truck;
}

// put shipment to truck
// returns true if plant closed, false otherwise
void BottlingPlant::getShipment( unsigned int cargo[] ) {
    if ( isClosing ) {
        return;
    }

    for ( unsigned int i = 0; i < NUM_FLAVOURS; i += 1 ) {
	cargo[i] = produced[i];
	produced[i] = 0;
    }
    
    printer.print( Printer::BottlingPlant, 'P' );
} // getShipment


/* Private */

// produces soda and stores them in produced array
void BottlingPlant::produce() {
    unsigned int total = 0;                           // keep track of # sodas produced
    for ( unsigned int i = 0; i < NUM_FLAVOURS; i += 1 ) {
	produced[i] = mprng( maxShippedPerFlavour );  // produce random amount
	total += produced[i];
    }

    printer.print( Printer::BottlingPlant, 'G', total );
} // produce


void BottlingPlant::main() {
    printer.print( Printer::BottlingPlant, 'S' );

    produce();

    while ( 1 ) {
	_Accept( ~BottlingPlant ) {
	    /*	    isClosing = true;
		    break; */
	    uRendezvousAcceptor();
	    throw Shutdown();
	} or _Accept( getShipment ) {
	    yield( timeBetweenShipments );
	    produce();
	}
    }

    printer.print( Printer::BottlingPlant, 'F' );
} // main
