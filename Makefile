OPT:=-O2 -multi

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD ${OPT}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = config.o Printer.o Bank.o Parent.o Watcard.o WatcardOffice.o NameServer.o VendingMachine.o Truck.o BottlingPlant.o Student.o main.o 
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"


.PHONY : all clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}
