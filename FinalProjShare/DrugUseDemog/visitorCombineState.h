#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"

#include "visitor.h"
#include "parse.h"
#include <memory>
#include <string>

class visitorCombineState : public Visitor {

    public:
        visitorCombineState() {
            read_csvStateToCode("StateNametoCode.csv");   
        }
        void visit(std::shared_ptr<hospitalData> hosp) override {

            std::string stateName = hosp->getState();

            if (allStateHospData.count(stateName) < 1) {
                allStateHospData[stateName] = new comboHospitalData("state", stateName, stateName);
            }

            allStateHospData[stateName]->addHospitaltoRegion(hosp);
        }

        virtual void visit(drugData &drugstuff) override {
            std::string stateName = drugstuff.getState();
            allStateDrugData[stateToCode[stateName]] = &drugstuff;
        }



        void visit(demogData &demog) override {
            string stateName = demog.getState();
			//if first state entry, create it
			if (allStateDemogData.count(stateName) < 1) {
					//cout << "Making a new state entry: " << stateName << endl;
					allStateDemogData[stateName] = new comboDemogData("state", stateName, stateName);
			}
			//either way now add this county info 
			//this keeps a running total
			allStateDemogData[stateName]->addDemogtoRegion(make_shared<demogData>(demog));
        }

        //getter functions
        std::map<string, comboDemogData*> stateDmap(){
            return allStateDemogData;
        }
        comboDemogData* stateDmapEntry(string stateN) {
            return allStateDemogData[stateN];
        }
        std::map<string, comboHospitalData*> stateHmap() const {
            return allStateHospData;
        }
        comboHospitalData* stateHmapEntry(string stateN) {
            return allStateHospData[stateN];
        }

        std::map<string, drugData*> stateDrugmap() const {
            return allStateDrugData;
        }
        drugData* stateDrugmapEntry(string stateN) {
            return allStateDrugData[stateN];
        }

        void read_csvStateToCode(std::string filename) {
                // Create an input filestream
            std::ifstream myFile(filename);

            // Make sure the file is open
            if(!myFile.is_open()) {
                    throw std::runtime_error("Could not open file");
            }

            if(myFile.good()) {
                    consumeColumnNames(myFile);

                    std::string line, state, junk;

                    // Now read data, line by line and enter into the map
                    while(std::getline(myFile, line)) {

                        std::stringstream ss(line);

                        string state = getField(ss);
                        string abr = getField(ss);
                        string code = getField(ss);

                        stateToCode[state] = code;

                    }

                    // Close file
                    myFile.close();
            }
        }

        private:
    	//state maps
        std::map<string, comboDemogData*> allStateDemogData;
        std::map<string, comboHospitalData*> allStateHospData;
        std::map<string, drugData*> allStateDrugData;
        std::map<string, string> stateToCode;

    
};

#endif
