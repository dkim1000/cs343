#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "NameServer.h"
#include "Printer.h"
#include "Watcard.h"
#include "config.h"     // NUM_FLAVOURS


_Task VendingMachine {
    Printer &printer;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int stocks[ NUM_FLAVOURS ];  
    bool isRestocking;

    void main();

  public:
    enum Flavours { APPLE, BANANA, COCACOLA }; // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif // VENDING_MACHINE_H
