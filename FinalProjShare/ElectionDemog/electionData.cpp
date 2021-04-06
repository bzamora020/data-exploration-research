#include "electionData.h"
#include "visitor.h"
#include <sstream>

vector<string> electionData::candidateNames;

std::ostream& operator<<(std::ostream& out, const electionData& E) {
	out << E.getName() << " " << E.state << ": ";
	string name = E.candidateNames.at(0);
	out << *(E.getCandidates()[name]);
	for (int i = 1; i < E.candidateNames.size(); i++) {
		name = E.candidateNames.at(i);
		out << ", " << *(E.getCandidates()[name]);
	}
	cout << "\n";
	for (auto ie: E.totalVotesPerParty){
		cout << "Party: " << ie.first << " Votes: " << (int)ie.second << endl;
	}
	return out;
}

void electionData::accept(class Visitor& v) { v.visit(this); }