#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "MPRNG.h"
#include "config.h"
#include "Printer.h"
#include "Bank.h"
#include "Parent.h"
#include "Watcard.h"
#include "WatcardOffice.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"

using namespace std;
MPRNG mprng;

// prints error statement
void printError ( char *argv ) {
    cerr << "Usage: " << argv << " [ config-file [ random-seed (> 0) ] ]" << endl;
    exit(EXIT_FAILURE);	
}

// convert C string to integer
bool convert( int &val, string buffer ) {	
    std::stringstream ss( buffer );		// connect stream and buffer
    ss >> dec >> val;				// convert integer from buffer
    return ! ss.fail() &&			// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void uMain::main() {
    string fileName = "soda.config";
    int seed = getpid();			// random seed
    
    if ( argc > 3 ) {
    Error: printError( argv[0] );
    }

    if ( argc >= 2 ) {				
	fileName = argv[1];
    }
    if ( argc >= 3 ) {
	if ( !convert( seed, argv[2] ) || seed <= 0 ) goto Error;
    }

    mprng.seed(seed);				// randomize with seed
    
    ConfigParms parms;
    processConfigFile( fileName.c_str() , parms );
    Printer prt( parms.numStudents, parms.numVendingMachines, parms.numCouriers );
    Bank bank( parms.numStudents );
    Parent parent( prt, bank, parms.numStudents, parms.parentalDelay );
    WATCardOffice cardOffice ( prt, bank, parms.numCouriers );
    NameServer nameServer ( prt, parms.numVendingMachines, parms.numStudents );

    VendingMachine* vendingMachines[ parms.numVendingMachines ];
    for ( unsigned int i = 0; i < parms.numVendingMachines; i += 1 ) {
	vendingMachines[i] = new VendingMachine( prt, nameServer, i, parms.sodaCost, parms.maxStockPerFlavour );
    }

    BottlingPlant* bottlingPlant = new BottlingPlant( prt, nameServer, parms.numVendingMachines, parms.maxShippedPerFlavour, 
						      parms.maxStockPerFlavour, parms.timeBetweenShipments );

    Student* students[ parms.numStudents ];
    for ( unsigned int i = 0; i < parms.numStudents; i += 1 ) {
	students[i] = new Student( prt, nameServer, cardOffice, i, parms.maxPurchases );
    }
       

    for ( unsigned int i = 0; i < parms.numStudents; i += 1 ) {
	delete students[i];
    }

    delete bottlingPlant;

    for ( unsigned int i = 0; i < parms.numVendingMachines; i += 1 ) {
	delete vendingMachines[i];
    }

			 
} // uMain::main()
