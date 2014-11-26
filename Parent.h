#include "Printer.h"
#include "Bank.h"
#include "MPRNG.h"

_Monitor Printer;
_Monitor Bank;

_Task Parent {
	Printer &printer;
	Bank &bank;
	unsigned int numStudents;
	unsigned int parentalDelay;
	void main();
		public:
			~Parent();
			Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
