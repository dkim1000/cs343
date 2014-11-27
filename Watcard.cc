#include "Watcard.h"

WATcard::WATCard() {
	balance = 0;
}

void WATcard::deposit( unsigned int amount ) {
	balance += amount;
}
void WATcard::withdraw( unsigned int amount ) {
	balance -= amount;
}

unsigned int WATcard::getBalance() {
	return balance;
}