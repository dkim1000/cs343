#ifndef TRUCK_H
#define TRUCK_H

// created by bottling plant
_Task Truck {
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};


#endif // TRUCK_H
