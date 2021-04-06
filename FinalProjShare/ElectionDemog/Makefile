#CXX=clang++
CXX=g++

CXXFLAGS= -g -std=c++14 

BINARIES=main

all: ${BINARIES}

tests: ${BINARIES}
	./main

main: statTool.o placeData.o rating.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o comboElectionData.o electionData.o candidate.o parse.o  main.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o 
