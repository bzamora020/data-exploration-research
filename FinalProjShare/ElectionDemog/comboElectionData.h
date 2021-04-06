#ifndef CELECDATA_H
#define CELECDATA_H

#include <string>
#include "electionData.h"
using namespace std;
class comboElectionData : public electionData {
public:
	comboElectionData(string r, string s) : electionData(r, s) {}
	/*
	* Careful: It directly uses the name of electionData as its own.
	*/
	comboElectionData(electionData e) : electionData(e) {
		//shared_ptr<electionData> p(&e);
		electionData* p = &e;
		addElectoRegion(p);
	}
	void addElectoRegion(electionData* CD);
	string getRegion() {
		return this->getName();
	}
	vector<shared_ptr<electionData>> getCounties() { return counties; }
private:
	vector<shared_ptr<electionData>> counties;
};
#endif