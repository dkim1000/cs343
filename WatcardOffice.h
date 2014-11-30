#ifndef WATCARD_OFFICE_H
#define WATCARD_OFFICE_H

#include "Watcard.h"
#include "Printer.h"
#include "Bank.h"

_Monitor Printer;
_Monitor Bank;


_Task WATCardOffice {

  struct Args {
    unsigned int sid;
    Bank &bank;
    WATCard *card;
    unsigned int amount;

    Args(Bank &bank, unsigned int sid, WATCard *card, unsigned int amount) :
      sid(sid), bank(bank), card(card), amount(amount) {}
  };

  struct Job {                           // marshalled arguments and return future
    Args args;                         // call arguments (YOU DEFINE "Args")
    WATCard::FWATCard result;          // return future
    Job( Args args ) : args( args ) {}
  };

  _Task Courier {                    // communicates with bank
  private:
    unsigned int id;
    WATCardOffice *office;
    Printer &printer;

    void main();

  public:
    enum State {STARTING = 'S', START_XFER = 't', END_XFER = 'T', FINISHED = 'F'};

    Courier(unsigned int id, WATCardOffice *office, Printer &prt) : id(id), office(office), printer(prt) {}
  };

  Printer &printer;
  Bank &bank;
  unsigned int numCouriers;
  Courier **couriers;
  Job *job;
  bool isDone;

  void main();
public:
  ~WATCardOffice();
  _Event Lost {};                        // lost WATCard
  WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
  WATCard::FWATCard create( unsigned int sid, unsigned int amount );
  WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
  Job *requestWork();
};

#endif // WATCARD_OFFICE_H
