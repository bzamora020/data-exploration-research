#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

using namespace std;

class candidate {
public:
	candidate(string a, int b, string c) : name(a), votes(b), party(c) {}
	candidate(string n, string p) : name(n), votes(0), party(p) {}
	candidate(candidate& c) : name(c.name), votes(c.votes), party(c.party) {}
	string getName() const {
		return name;
	}
	int getVotes() const {
		return votes;
	}
	void setVotes(int n) {
		votes = n;
	}
	string getParty() const {
		return party;
	}
	candidate& operator+=(const candidate& c1) { votes += c1.votes; return *this; }
	friend std::ostream& operator<<(std::ostream& out, const candidate& D);
private:
	string name;
	int votes;
	string party;
};
#endif
