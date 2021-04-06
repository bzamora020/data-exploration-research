#ifndef ELECDATA_H
#define ELECDATA_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "placeData.h"
#include "candidate.h"

using namespace std;

class electionData : public placeData {
public:
	electionData(string c, string s) : placeData(c), state(s), totalVotes(0) {}
	electionData() : placeData("default"), state("default"), totalVotes(0) {}
	electionData(electionData &e) : placeData(e.getName()), state(e.state), totalVotes(e.totalVotes) {
		for (string name : candidateNames) {
			addCandidate(make_shared<candidate>(*(e.getCandidates()[name])));
		}
	}
	static vector<string> candidateNames;
	void addCandidate(shared_ptr<candidate> c) {
		if (candidates.count(c->getName()) == 0) {
			candidates[c->getName()] = make_shared<candidate>(*(c));
		}
		else {
			candidates[c->getName()]->setVotes(candidates[c->getName()]->getVotes() + c->getVotes());
		}
		totalVotes += c->getVotes();
		string keyParty = c->getParty();
		if (totalVotesPerParty.count(keyParty) == 0) {
			totalVotesPerParty[keyParty] = 0;
		}
		totalVotesPerParty[keyParty] += c->getVotes();
	}
	map<string, shared_ptr<candidate>> getCandidates() const {
		return candidates;
	}
	string getState() {return state;}

	double getRepublicanVotes()  const { return 100*totalVotesPerParty.find("Republican")->second / totalVotes; }
	double getDemocratVotes()  const { return 100*totalVotesPerParty.find("Democrat")->second / totalVotes; }
	double getNAVotes()  const { return 100*totalVotesPerParty.find("NA")->second / totalVotes; }

	double getBernieVotes() const { return 100*candidates.find("Bernie Sanders")->second->getVotes() / totalVotesPerParty.find("Democrat")->second ; }
	double getHillaryVotes() const { return 100*candidates.find("Hillary Clinton")->second->getVotes() / totalVotesPerParty.find("Democrat")->second ; }

	double getCruzVotes() const { return 100*candidates.find("Ted Cruz")->second->getVotes() / totalVotesPerParty.find("Republican")->second ; }
	double getTrumpVotes() const { return 100*candidates.find("Donald Trump")->second->getVotes() / totalVotesPerParty.find("Republican")->second ; }

	void accept(class Visitor& v);
	friend std::ostream& operator<<(std::ostream& out, const electionData& E);
private:
	string state;
	int totalVotes;
protected:
	map<string, shared_ptr<candidate>> candidates;
	map<string, double> totalVotesPerParty; //party name to total party votes
};
#endif