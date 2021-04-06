
#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "visitor.h"
#include "parse.h"
#include <memory>
#include <fstream>
#define DEBUG false

class visitorCombineCounty : public Visitor {
    public: 

        visitorCombineCounty(string filename){
                    // Create an input filestream
            std::ifstream myFile(filename);

            // Make sure the file is open
            if(!myFile.is_open()) {
                throw std::runtime_error("Could not open file");
            }

            if(myFile.good()) {
                consumeColumnNames(myFile);

                // Helper vars
                std::string line, state, junk;

                // Now read data, line by line and enter into the map
                while(std::getline(myFile, line)) {

                std::stringstream ss(line);

                string city = getFieldNQ(ss);
                state = getFieldNQ(ss);
                junk = getFieldNQ(ss);
                string county = getFieldNQ(ss);

                string cityKey = city+state;

                cityToCounty[cityKey] = county;

                //cout << "line: " << line << endl;
                //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
                }

                // Close file
                myFile.close();
        }
        };

        virtual void visit(demogData *d) override {
            countyDemogData* c = dynamic_cast<countyDemogData* >(d);
            string countyName = c->getCounty();
            string countyKey = "";

            if (countyName.find(" County") != string::npos) {
                countyName.erase(countyName.find(" County"));                
            }
            
            countyKey = countyName + c->getState();

            if(allCountyDemogData.count(countyKey) < 1){
                allCountyDemogData[countyKey] = new comboDemogData("county", c->getState());
            }
            allCountyDemogData[countyKey]->addDemogtoRegion(d);
        }

        virtual void visit(hospitalData *h) override {
                        //some error logging for dev
            int cityError = 0;
            int loggedCity = 0;
            int numCountyH = 0;
            /* make county hospital data */
                    //cityHospitalData *hInfo = dynamic_cast<cityHospitalData*>(h);
                    cityHospitalData *hInfo = dynamic_cast<cityHospitalData *>(h);
                    if(hInfo) { 
                        string city = hInfo->getCity();
                        //city names can be redundent
                        string cityKey = city+hInfo->getState();
                        string county = "";
                        string countyKey= "";
                        //county = cityToCounty[cityKey] + hInfo->getState();
                        //figure out the county
                        if (cityToCounty.count(cityKey) >= 1) {
                            county = cityToCounty[cityKey];
                        } else {
                            county = "unknown " + hInfo->getState();
                            if (DEBUG ) {
                                cout << "hospital with unknown city: ";// << city << ", " << hInfo->getState() << endl;
                                cout << "citykey: " << cityKey <<endl;
                            }
                            cityError++;
                        }
                        countyKey = county+hInfo->getState();
                        //if first county entry, create it
                        if (allCountyHospData.count(countyKey) < 1) {
                            //cout << "Making a new county entry (hospital): " << countyKey << endl;
                            //make the new data
                            allCountyHospData[countyKey] = new comboHospitalData(county +" County", hInfo->getState());
                            numCountyH++;
                        } 
                        //either way now add this city hospital to the right county
                        comboHospitalData* chInfo = allCountyHospData[countyKey];
                        if(chInfo) { 
                            chInfo->addHospitaltoRegion(hInfo);
                            loggedCity++;
                        } else {
                            cout << "Error should not happen - allCounty data map fail" << endl;
                        }
                    } else {
                        cout << "Error should not happen - hospital dynamic cast fail" << endl;
                    }    
        }
        void getHMsizes() override {
            cout << allCountyHospData.size() << " " << allCountyDemogData.size() << endl;
        }
        std::map<string, comboDemogData*> countyDmap() const { return allCountyDemogData; }
        comboDemogData* countyDmapEntry(string stateN) { return allCountyDemogData[stateN]; }
        std::map<string, comboHospitalData*> countyHmap() const { return allCountyHospData; }
        comboHospitalData* countyHmapEntry(string stateN) { return allCountyHospData[stateN]; }

        std::map<string, string> cityCountyHmap() const { return cityToCounty; }
        private:
            std::map<string, comboDemogData*> allCountyDemogData;
            std::map<string, comboHospitalData*> allCountyHospData;
            std::map<string, string> cityToCounty;
};

#endif
