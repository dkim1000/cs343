#include "BottlingPlant.h"
#include "MPRNG.h"
#include "Truck.h"
#include "VendingMachine.h"


/* public */

// Constructor
Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
	      unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) 
    : printer(prt), nameServer(nameServer), plant(plant),
      numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {}



/* private */

// main
void Truck::main() {
    printer.print( Printer::Truck, 'S' );
    vm = nameServer.getMachineList();

    while ( 1 ) {
	yield( mprng ( 1, 10 ) );        // COFFEE TIME
	
	// get shipment and check if the plant's closed (true)
        if ( plant.getShipment( cargo ) ) break;

	unsigned int numTotalSoda = 0;   // number of all sodas on cargo
	for ( unsigned int i = 0; i < NUM_FLAVOURS; i += 1 ) {
	    numTotalSoda += cargo[i];
	}
	printer.print( Printer::Truck, 'P', total );
	
        // Choose a vending machine and restock it
	for ( unsigned int i = 0; i < numVendingMachines && numTotalSoda > 0; i += 1 ) {
	    unsigned int id = vm[i]->getId();
	    printer.print( Printer::Truck, 'd', id, numTotalSoda );    // begin delivery
	    unsigned int *vmStock = vm[i]->inventory();        // get this machine's stock

	    // restock for each soda flavour
	    unsigned int notFilled = 0;                        // keeps track of number of sodas not filled
	    for ( unsigned int j = 0; j < NUM_FLAVOURS; j += 1 ) {
		unsigned int restockAmount = maxStockPerFlavour - vmStock[j]; // number of sodas to restock
		if ( restockAmount > cargo[j] ) {              // more soda to fill than what's in cargo
		    restockAmount = cargo[j];                  // restock with the cargo remainder
		    notFilled += ( restockAmount - cargo[j] ); // add to number of sodas not filled
		}
		vmStock[j] += restockAmount;                   // fill machine's stock
		numTotalSoda -= restockAmount;                 // decrement from total number of sodas
		cargo[j] -= restockAmount;                     // decrement from cargo
	    } // for

	    if ( notFilled != 0 ) {
		printer.print( Printer::Truck, 'U', id, notFilled );   // notify that the vm was unfilled
	    }

	    // TODO: confirm during testing whether the following two lines are ordered correctly or not
	    printer.print( Printer::Truck, 'D', id, numTotalSoda );
	    vm[i]->restocked();
	    
	} // for
    } // while (1)
    
    printer.print( Printer::Truck, 'F' );
} // main
