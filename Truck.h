#ifndef TRUCK_H
#define TRUCK_H

#include "NameServer.h"
#include "Printer.h"
#include "config.h"    // NUM_FLAVOURS

_Task Truck {
    Printer &printer;
    NameServer &nameServer;
    BottlingPlant &plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    VendingMachine **vm;
    unsigned int cargo[ NUM_FLAVOURS ];
    
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif // TRUCK_H

