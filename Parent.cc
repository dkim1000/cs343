#include "Parent.h"
#include <iostream>
using namespace std;

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
		} _Else {
			unsigned int rId = mprng(numStudents-1);
			unsigned int rMoney = mprng(1,3);
			yield(parentalDelay);
			bank.deposit(rId, rMoney);
			printer.print(Printer::Parent, 'D', rId, rMoney);
		}
	}
	printer.print(Printer::Parent, 'F');
}
