#include "WatcardOffice.h"
#include "MPRNG.h"
#include <iostream>

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), bank(bank), numCouriers(numCouriers) {
	couriers = new Courier*[numCouriers];
	for (unsigned int i = 0 ; i < numCouriers ; i++) {
		couriers[i] = new Courier(i, this, printer);
	}
}

WATCardOffice::~WATCardOffice() {
	delete[] job;
	for (unsigned int i = 0 ; i < numCouriers ; i++) {
		delete couriers[i];
	}
	delete[]couriers;
}

void WATCardOffice::main() {
	printer.print(Printer::WATCardOffice, 'S');

	while (1) {
		_Accept(~WATCardOffice) {
			isDone = true;
			for (unsigned int i = 0 ; i < numCouriers ; i++) {
				_Accept(requestWork);
			}
			break;
		}
		or _When (job == NULL) _Accept(create, transfer);
		or _When (job != NULL) _Accept(requestWork);
	}

	printer.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
  job = new Job(Args(bank, sid, NULL, amount));

  printer.print(Printer::WATCardOffice, 'C', sid, amount);

  return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  job = new Job(Args(bank, sid, card, amount));

  printer.print(Printer::WATCardOffice, 'T', sid, amount);

  return job->result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
  if (isDone) 
  	return NULL;
  Job* temp = job;
  job = NULL;
  return temp;
}

void WATCardOffice::Courier::main() {
	printer.print(Printer::Courier, id, 'S');
	std::cout << "hi";

	while (1) {
		Job *job = office->requestWork();

		if (job == NULL) break;

		Args args = job->args;

		//possiblility to drop the card
		bool loseCard = (mprng(5) == 0);
		if (loseCard) {
			job->result.exception(new Lost);
			if (args.card != NULL) delete args.card;
		} else {
			printer.print (Printer::Courier, id, 't', args.sid, args.amount);

			//withdraw from bank then add funds to card
			args.bank.withdraw(args.sid, args.amount);
			if (args.card == NULL) args.card = new WATCard();
			args.card->deposit(args.amount);
			printer.print(Printer::Courier, id, 'T', args.sid, args.amount);

			job->result.delivery(args.card);
		}

		printer.print( Printer::Courier, 'W' );
		delete job;
	}
	printer.print(Printer::Courier, id, 'F');
}







