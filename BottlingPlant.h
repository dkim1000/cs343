#ifndef BOTTLING_PLANT_H
#define BOTTLING_PLANT_H

#include "NameServer.h"
#include "Printer.h"
#include "Truck.h"
#include "config.h"   // NUM_FLAVOURS

_Task BottlingPlant {
    Printer &printer;
    NameServer &nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    Truck *truck;
    bool isClosing, ready;
    unsigned int produced[ NUM_FLAVOURS ];
    
    void produce();
    void main();

  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
};


#endif // BOTTLING_PLANT_H
