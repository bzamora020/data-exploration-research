#include "comboElectionData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


void comboElectionData::addElectoRegion(electionData* CD) {
	vector<string> names = electionData::candidateNames;
	for (int i = 0; i < names.size(); i++) {
		addCandidate(CD->getCandidates()[names.at(i)]);
	}
}