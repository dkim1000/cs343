OPT:=-O2 -multi

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD ${OPT}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = main.o Printer.o Bank.o Parent.o Watcard.o NameServer.o VendingMachine.o BottlingPlant.o Student.o
EXEC1 = soda

OBJECTS = ${OBJECTS1}
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}


.PHONY : all clean

all : ${EXECS}					# build all executables

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS}
