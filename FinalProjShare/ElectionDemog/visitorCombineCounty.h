#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "visitor.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <map>

using namespace std;

class visitorCombineCounty : public Visitor {

    public:
        visitorCombineCounty(string filename) {
            // Create an input filestream
            ifstream myFile(filename);
            // Make sure the file is open
            if (!myFile.is_open()) {
                throw std::runtime_error("Could not open file");
            }

            if (myFile.good()) {
                consumeColumnNames(myFile);

                // Helper vars
                string line, state, junk;

                // Now read data, line by line and enter into the map
                while (getline(myFile, line)) {

                    stringstream ss(line);

                    string city = getFieldNQ(ss);
                    state = getFieldNQ(ss);
                    junk = getFieldNQ(ss);
                    string county = getFieldNQ(ss);

                    string cityKey = city + state;

                    cityToCounty[cityKey] = county;

                    //cout << "line: " << line << endl;
                    //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
                }

                // Close file
                myFile.close();
            }
        }

        void visit(demogData* dem) {
            comboDemogData* p = new comboDemogData(*dem);
            string county = p->getName() + p->getState();

            /*
            // check for pop of 0
            if (p->getPop() == 0){
                return;
            }
            */
            // fixing bug of counties from different state have same name - we could differentiate by adding state name
            //cout << p->getPop() << endl;
            if (allCountyDData.count(county) == 0) {
                allCountyDData.insert(make_pair(county, p));
            }
            else {
                shared_ptr<demogData> ptr(&(*dem));
                allCountyDData.at(county)->addDemogtoRegion(ptr);
            }
        }

        void visit(hospitalData* hosp) {
            string cityKey = "";
            string county = "";
            string state = "";
            state = hosp->getState();
            cityKey = hosp->getCity() + state;
            county = cityToCounty[cityKey];
            county += " County" + state; //added cause the tester tests for the exytra "County"
            if (allCountyHData.count(county) == 0) {
                comboHospitalData* p = new comboHospitalData(county, state);
                allCountyHData.insert(make_pair(county, p));
            }
            shared_ptr<hospitalData> ptr(&(*hosp));
            allCountyHData.at(county)->addHospitaltoRegion(ptr);
        }

        void visit(electionData* elec) {
            comboElectionData* p = new comboElectionData(*elec);
            string county = p->getName() + p->getState();
            if (allCountyEData.count(county) == 0) {
                allCountyEData.insert(make_pair(county, p));
            }
            else {
                //shared_ptr<electionData> ptr(&(*elec));
                allCountyEData.at(county)->addElectoRegion(elec);
            }
        }

        // getters
        map<string, comboDemogData*> countyDmap() { return allCountyDData; }
        comboDemogData* countyDmapEntry(string countyN) { return allCountyDData[countyN]; }
        map<string, comboHospitalData*> countyHmap()  { return allCountyHData;}
        comboHospitalData* countyHmapEntry(string countyN) { return allCountyHData[countyN]; }
        map<string, comboElectionData*> countyEmap() { return allCountyEData; }
        comboElectionData* countyEmapEntry(string countyN) { return allCountyEData[countyN]; }


    private:
        //map for county name to demog data
        map<string, comboDemogData*> allCountyDData;

        //map for county hospital data
        map<string, comboHospitalData*> allCountyHData;

        //map for county election data
        map<string, comboElectionData*> allCountyEData;

        //helper map to create aggregates from city -> county
        map<string, string> cityToCounty;

};

#endif