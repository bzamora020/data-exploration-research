CXX=clang++
# CXX=g++

CXXFLAGS= -g -std=c++14

BINARIES=dataProj

all: ${BINARIES}



dataProj: statTool.o placeData.o rating.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  main.o comboShootingData.o shootingData.o race.o gender.o armed.o
	${CXX} $^ -o $@


clean:
	/bin/rm -f ${BINARIES} *.o 
