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
#include <string>

class visitorCombineCounty : public Visitor
{

public:
    visitorCombineCounty(string fileName) // Creates helper map when instantiated with the uscities file
    {
        // Create an input filestream
        std::ifstream myFile(fileName);

        // Make sure the file is open
        if (!myFile.is_open())
        {
            throw std::runtime_error("Could not open file");
        }

        if (myFile.good())
        {
            consumeColumnNames(myFile);

            // Helper vars
            std::string line, state, junk, city, county, cityAlias;

            // Now read data, line by line and enter into the map
            while (std::getline(myFile, line))
            {

                std::stringstream ss(line);

                city = getFieldNQ(ss);
                state = getFieldNQ(ss);
                junk = getFieldNQ(ss);
                county = getFieldNQ(ss);
                cityAlias = getFieldNQ(ss);

                cout << "line: " << line << endl;
                cout << "city: " << city << " state: " << state<< " junk: " << junk << " county: " << county << " cityAlias: " << cityAlias << endl;

                string cityAliasKey = cityAlias + state;

                cout << cityAliasKey << endl;

                cityToCounty[cityAliasKey] = county;

                //cout << "line: " << line << endl;
                //cout << "pair (city, county): " << cityAlias << ", " << county << " state " << junk << endl;
            }

            // Close file
            myFile.close();
        }
    }

    void visit(hospitalData *e)
    {
        //std::shared_ptr<cityHospitalData > e = std::static_pointer_cast<cityHospitalData >(e);
        if (e)
        {
            string city = ((cityHospitalData *)e)->getCity();
            //city names can be redundent
            string cityKey = city + e->getState();
            string county = "";
            string countyKey = "";
            //figure out the county
            if (cityToCounty.count(cityKey) >= 1)
            {
                county = cityToCounty[cityKey];
            }

            else
            {
                county = "unknown " + e->getState();
            }

            countyKey = county + e->getState();

            //if first county entry, create it
            if (allCountyHData.count(countyKey) < 1)
            {
                //cout << "Making a new county entry (hospital): " << countyKey << endl;
                //make the new data
                allCountyHData[countyKey] = new comboHospitalData(county + " County", e->getState());
            }
            //either way now add this city hospital to the right county
            comboHospitalData *ce = allCountyHData[countyKey];
            if (ce)
            {
                ce->addHospitaltoRegion(e);
            }
        }
    }

    void visit(demogData *e)
    {
        if (e)
        {
            string countyName = ((countyDemogData *)e)->getCounty();
            
            string test = countyName;

            size_t found = test.find(" County");

            if (test.find(" County") != string::npos)
            {
                test.erase(found, 7);
            }

            string countyKey = test + e->getState();

            //if first state entry, create it

            if (allCountyDData.count(countyKey) < 1)
            {
                //cout << "Making a new county entry: " << countyName << endl;
                allCountyDData[countyKey] = new comboDemogData(countyName, e->getState());
            }
            //either way now add this county info
            //this keeps a running total
            comboDemogData *ce = allCountyDData[countyKey];
            if (ce)
            {
                ce->addDemogtoRegion(e);
            }
        }
    }

    void visit(shootingData *e){
        if(e)
        {
            string city = ((cityShootingData *)e)->getCity();

            string cityKey = city + e->getState();

            // cout << cityKey << endl;

            string county = "";

            string countyKey = "";

            //figure out the county
            if (cityToCounty.count(cityKey) >= 1)
            {
                county = cityToCounty[cityKey];
            }

            else
            {
                county = "unknown " + e->getState();
                cout << city << " " << e->getState() << endl;
                // cout << "Uh oh we are in here" << endl;
                // City was not found in the csv (i think)
            }

            countyKey = county + e->getState();

            // cout << countyKey << endl;

            //if first county entry, create it
            if (allCountySData.count(countyKey) < 1)
            {
                
                allCountySData[countyKey] = new comboShootingData(county + " County", e->getState());
            }

            //either way now add this city's shooting incident to the right county
            comboShootingData *cs = allCountySData[countyKey];
            if (cs)
            {
                cs->addShootingtoRegion(e);
            }
        }
    }

    std::map<string, comboDemogData *> countyDmap()
    {
        return allCountyDData;
    }

    comboDemogData *countyDmapEntry(string countyN)
    {
        return allCountyDData[countyN];
    };

    std::map<string, comboHospitalData *> countyHmap()
    {
        return allCountyHData;
    }
    comboHospitalData *countyHmapEntry(string countyN)
    {
        return allCountyHData[countyN];
    }
    std::map<string, comboShootingData *> countySmap()
    {
        return allCountySData;
    }
    comboShootingData *countySmapEntry(string countyN)
    {
        return allCountySData[countyN];
    }

private:
    // Private data like maps and stuff
    //map for county hospital data
    std::map<string, comboHospitalData *> allCountyHData;
    //map for county name to demog data
    std::map<string, comboDemogData *> allCountyDData;
    //map for county name to shooting data
    std::map<string, comboShootingData*> allCountySData;

    //helper map to create aggregates from city -> county
    std::map<string, string> cityToCounty;
};

#endif
