#include "Bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
	balance = new unsigned int [numStudents];
	for (int i = 0 ; i < numStudents ; i++) {
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
}
void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (balance[id] < amount)
		aCond[id].wait();
	balance[id] -= amount;
}