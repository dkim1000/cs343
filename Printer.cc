#include "Printer.h"
#include <iostream>

using namespace std;

enum Kind { Parent,
			WATCardOffice,
			NameServer,
			Truck,
			BottlingPlant,
			Student,
			Vending,
			Courier };
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ): numStudents(numStudents),
																								numVendingMachines(numVendingMachines),
																								numCouriers(numCouriers)
{

};

Printer::~Printer() {
  flush();
  cout << "***********************" << endl;
  delete [] buffer;
}

void Printer::flush() {
	cout << parent <<"\t";
	cout << watcard << "\t";
	cout << nameServer << "\t";
	cout << truck << "\t";
	cout << plant << "\t";
  for (int i = 0 ; i < numStudents ; i++) {
    cout << studentBuffer[i]<<"\t";
  }
  for (int i = 0 ; i < numVendingMachines ; i++) {
  	cout << vendingMachineBuffer[i]<<"\t";
  }
  for (int i = 0 ; i < numCouriers ; i++) {
  	cout << courierBuffer[i]<<"\t";
  }
cout << endl;
  for (int i = 0 ; i < voters ; i++) {
    buffer[i] = "";
  }
}	

void Printer::print( Kind kind, char state ) {
	switch (Kind) {
		case Parent:
			if (parent != "") {
				flush();
			}
			if (state == 'F')
				finish();
			parent = convert(state);
			break;
		case WATCardOffice:
			if (watcard != "") {
				flush();
			}
			if (state == 'F')
				finish();
			watcard = convert(state);
			break;
		case NameServer:
			if (nameServer != "") {
				flush();
			}
			if (state == 'F')
				finish();
			nameServer = convert(state);
			break;
		case Truck:
			if (truck != "") {
				flush();
			}
			if (state == 'F')
				finish();
			truck = convert(state);
			break;
		case BottlingPlant:
			if (plant != "") {
				flush();
			}
			if (state == 'F')
				finish();
			plant = convert(state);
			break;
	}

}
void Printer::print( Kind kind, char state, int value1 ){
	switch (Kind) {
		case Parent:
			if (parent != "") {
				flush();
			}
			parent = convert(state);
			parent += convert(value1);
			break;
		case WATCardOffice:
			if (watcard != "") {
				flush();
			}
			watcard = convert(state);
			watcard += convert(value1);
			break;
		case NameServer:
			if (nameServer != "") {
				flush();
			}
			nameServer = convert(state);
			nameServer += convert(value1);
			break;
		case Truck:
			if (truck != "") {
				flush();
			}
			truck = convert(state);
			truck += convert(value1);
			break;
		case BottlingPlant:
			if (plant != "") {
				flush();
			}
			plant = convert(state);
			plant += convert(value1);
			break;
	}
}
void Printer::print( Kind kind, char state, int value1, int value2 ) {
	switch (Kind) {
		case Parent:
			if (parent != "") {
				flush();
			}
			parent = convert(state);
			parent += convert(value1);
			parent += ",";
			parent += convert(value2);
			break;
		case WATCardOffice:
			if (watcard != "") {
				flush();
			}
			watcard = convert(state);
			watcard += convert(value1);
			parent += ",";
			parent += convert(value2);
			break;
		case NameServer:
			if (nameServer != "") {
				flush();
			}
			nameServer = convert(state);
			nameServer += convert(value1);
			nameServer += ",";
			nameServer += convert(value2);
			break;
		case Truck: 
			if (truck != "") {
				flush();
			}
			truck = convert(state);
			truck += convert(value1);
			truck += ",";
			truck += convert(value2);
			break;
		case BottlingPlant:
			if (plant != "") {
				flush();
			}
			plant = convert(state);
			plant += convert(value1);
			plant += ",";
			plant += convert(value2);
			break;
	}
}
void Printer::print( Kind kind, unsigned int lid, char state ) {
	switch (Kind) {
		case Student:
			if (studentBuffer[lid] != "")
				flush();
			if (state == 'F')
				finish();
			studentBuffer[lid] = convert(state);
			break;
		case Vending:
			if (vendingMachineBuffer[lid] != "")
				flush();
			if (state == 'F')
				finish();
			vendingMachineBuffer[lid] = convert(state);
			break;
		case Courier:
			if (courierBuffer[lid] != "")
				flush();
			if (state == 'F')
				finish();
			courierBuffer[lid] = convert(state);
			break;
		default:
	}
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	switch (Kind) {
		case Student:
			if (studentBuffer[lid] != "")
				flush();
			studentBuffer[lid] = convert(state);
			studentBuffer[lid] += convert(value1);
			break;
		case Vending:
			if (vendingMachineBuffer[lid] != "")
				flush();
			vendingMachineBuffer[lid] = convert(state);
			vendingMachineBuffer[lid] += convert(value1);
			break;
		case Courier:
			if (courierBuffer[lid] != "")
				flush();
			courierBuffer[lid] = convert(state);
			courierBuffer[lid] += convert(value1);
			break;
		default:
	}
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	switch (Kind) {
		case Student:
			if (studentBuffer[lid] != "")
				flush();
			studentBuffer[lid] = convert(state);
			studentBuffer[lid] += convert(value1);
			studentBuffer[lid] += ",";
			studentBuffer[lid] += convert(value2);
			break;
		case Vending:
			if (vendingMachineBuffer[lid] != "")
				flush();
			vendingMachineBuffer[lid] = convert(state);
			vendingMachineBuffer[lid] += convert(value1);
			vendingMachineBuffer[lid] += ",";
			vendingMachineBuffer[lid] += convert(value2);
			break;
		case Courier:
			if (courierBuffer[lid] != "")
				flush();
			courierBuffer[lid] = convert(state);
			courierBuffer[lid] += convert(value1);
			courierBuffer[lid] += ",";
			courierBuffer[lid] += convert(value2);
			break;
		default:
	}
}

string Printer::convert(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

string Printer::convert(char c) {
  stringstream ss;
  ss << c;
  return ss.str();
}

void Printer::finish() {
	parent = "...";
	watcard = "...";
	nameServer = "...";
	truck = "...";
	plant = "...";
	for (int i = 0 ; i < numStudents ; i++) {
		studentBuffer[i] = "...";
	}
	for (int i = 0 ; i < numVendingMachines ; i++) {
		vendingMachineBuffer[i] = "...";
	}
	for (int i = 0 ; i < numCouriers ; i++) {
		courierBuffer[i] = "...";
	}
}



