#include "Parent.h"

extern MPRNG generator;

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay)
  : printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {

  }

 Parent::~Parent() {
 	
 }

void Parent::main() {
	printer.print(Printer::Parent, 'S');
	while (1) {
		_Accept(~Parent) {
			break;
		} else {
			unsigned int rId = generator(numStudents-1);
			unsigned int rMoney = generator(1,3);
			yield(parentalDelay);
			bank.deposit(id, rMoney);
			printer.print(Printer::Parent, 'D', id, rMoney);
		}
	}
	printer.print(Printer::Parent, 'F');
}