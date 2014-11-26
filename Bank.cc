#include "Bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
	balance = new int[numStudents];
	for (unsigned int i = 0 ; i < numStudents ; i++) {
		balance[i] = 0;
	}
	aCond = new uCondition[numStudents];
}
Bank::~Bank() {
	delete[] balance;
	delete[] aCond;
}
void Bank::deposit( unsigned int id, unsigned int amount ) {
	balance[id] += amount;
	aCond[id].signal();
}
void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (balance[id] < amount)
		aCond[id].wait();
	balance[id] -= amount;
}