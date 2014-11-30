#ifndef STUDENT_H
#define STUDENT_H

#include "NameServer.h"
#include "Printer.h"
#include "Watcard.h"
#include "WatcardOffice.h"

_Task Student {
    Printer &printer;
    NameServer &nameServer;
    WATCardOffice &cardOffice;
    unsigned int id;
    unsigned int maxPurchases;
    unsigned int numPurchase;
    unsigned int favFlavour;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif // STUDENT_H
