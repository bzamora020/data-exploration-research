#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "cityHospitalData.h"
#include "countyDemogData.h"
#include "demogData.h"
#include "hospitalData.h"
#include "parse.h"
#include "visitor.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <string>

class visitorCombineCounty : public Visitor
{

public:
  ~visitorCombineCounty()
  {
    for (auto entry : allCountySData)
    {
      delete entry.second;
    }
    for (auto entry : allCountyDData)
    {
      delete entry.second;
    }
    for (auto entry : allCountyHData)
    {
      delete entry.second;
    }
  }

  visitorCombineCounty(string fileName) // Creates helper map when instantiated
                                        // with the uscities file
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
      std::string line;

      // Now read data, line by line and enter into the map
      while (std::getline(myFile, line))
      {

        std::stringstream ss(line);
        // First csv
        string city = getFieldNQ(ss);
        string state = getFieldNQ(ss);
        string junk = getFieldNQ(ss);
        string county = getFieldNQ(ss);

        string cityKey = city + state;

        cityToCounty[cityKey] = county;
      }

      // Close file
      myFile.close();
    }
  }

  void visit(hospitalData *e)
  {

    if (e)
    {
      string city = ((cityHospitalData *)e)->getCity();
      // city names can be redundent
      string cityKey = city + e->getState();
      string county = "";
      string countyKey = "";
      // figure out the county
      if (cityToCounty.count(cityKey) >= 1)
      {
        county = cityToCounty[cityKey];
      }
      else
      {
        county = "unknown " + e->getState();
      }

      countyKey = county + e->getState();

      // if first county entry, create it
      if (allCountyHData.count(countyKey) < 1)
      {

        allCountyHData[countyKey] =
            new comboHospitalData(county + " County", e->getState());
      }
      // either way now add this city hospital to the right county
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

      // if first state entry, create it

      if (allCountyDData.count(countyKey) < 1)
      {
        // cout << "Making a new county entry: " << countyName << endl;
        allCountyDData[countyKey] =
            new comboDemogData(countyName, e->getState());
      }
      // either way now add this county info
      // this keeps a running total
      comboDemogData *ce = allCountyDData[countyKey];
      if (ce)
      {
        ce->addDemogtoRegion(e);
      }
    }
  }
  int unkCounter = 0;

  void visit(shootingData *e)
  {
    if (e)
    {
      string county = ((cityShootingData *)e)->getCity();

      string countyKey = "";
      string test = county;
      size_t found = test.find(" County");
      if (county.find(" County") != std::string::npos)
      {
        test.erase(found, 7);
        county = test;
      }
      else if(county.find(" Parish") != std::string::npos){
        // Do Nothing
      }
      else if(county.find(" Borough") != std::string::npos){
        // Do Nothing
      }
      else
      {
        unkCounter++;
        // cout << county << " " << e->getState() << endl;
        county = "Unknown";
      }

      countyKey = county + e->getState();

      // if first county entry, create it
      if (allCountySData.count(countyKey) < 1)
      {

        allCountySData[countyKey] =
            new comboShootingData(county + " County", e->getState());
      }

      // either way now add this city's shooting incident to the right county
      comboShootingData *cs = allCountySData[countyKey];
      if (cs)
      {
        cs->addShootingtoRegion(e);
      }
    }
  }

  std::map<string, comboDemogData *> countyDmap() { return allCountyDData; }

  comboDemogData *countyDmapEntry(string countyN)
  {
    if (allCountyDData.count(countyN) == 1)
    { // Check if the county exists in the map already before returning a value for it, could create new entries unwillingly
      return allCountyDData[countyN];
    }   
    else{
      return NULL;
    }
  }

  std::map<string, comboHospitalData *> countyHmap() { return allCountyHData; }
  comboHospitalData *countyHmapEntry(string countyN)
  {
    if (allCountyHData.count(countyN) == 1)
    {
      return allCountyHData[countyN];
    }
    else{
      return NULL;
    }
  }
  std::map<string, comboShootingData *> countySmap() { return allCountySData; }
  comboShootingData *countySmapEntry(string countyN)
  {
    if (allCountySData.count(countyN) == 1)
    {
      return allCountySData[countyN];
    }
    else{
      return NULL;
    }
  }
  void mostShootingsCounty()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          //if(entry.second->getState() == "CA"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          //}
        }
    /*
    CSVs to get:
        - DC, AK, HI, CA, TX, AZ
        Racial Demog and Shootings race identification
    */

    std::ofstream myFile;
    myFile.open ("countiesPerArmed.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("countiesPerBodyCam.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllness.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeing.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("countiesPerUnder18.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("countiesPerBelowPoverty.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();
    }

  void mostShootingsCountyCA()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          if(entry.second->getState() == "CA"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          }
        }
    std::ofstream myFile;
    myFile.open ("countiesPerArmedCA.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBodyCamCA.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllnessCA.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeingCA.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerUnder18CA.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBelowPovertyCA.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();
  }
  void mostShootingsCountyAK()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          if(entry.second->getState() == "AK"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          }
        }

    std::ofstream myFile;
    myFile.open ("countiesPerArmedAK.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(1){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBodyCamAK.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(1){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllnessAK.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(1){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeingAK.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(1){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerUnder18AK.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(1){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBelowPovertyAK.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(1){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();
    }

  void mostShootingsCountyDC()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          if(entry.second->getState() == "DC"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          }
        }
    std::ofstream myFile;
    myFile.open ("countiesPerArmedDC.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBodyCamDC.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllnessDC.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeingDC.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerUnder18DC.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBelowPovertyDC.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();
    }

  void mostShootingsCountyHI()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          if(entry.second->getState() == "HI"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          }
        }
    std::ofstream myFile;
    myFile.open ("countiesPerArmedHI.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBodyCamHI.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllnessHI.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeingHI.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerUnder18HI.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBelowPovertyHI.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();
    }
  void mostShootingsCountyAZ()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          if(entry.second == NULL){
            cout << "AHHH" << endl;
          }
          if(entry.second->getState() == "AZ"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          }
        }
    std::ofstream myFile;
    myFile.open ("countiesPerArmedAZ.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBodyCamAZ.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllnessAZ.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeingAZ.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerUnder18AZ.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBelowPovertyAZ.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();
    }
  void mostShootingsCountyTX()
  {
    std::vector<comboShootingData *> theCountiesShootingData;
    std::vector<comboDemogData*> theCountiesDemogData;
    // shooting county has a demog county
    for (auto entry : (allCountySData))
        {
          if(entry.second == NULL){
            cout << "AHHH" << endl;
          }
          if(entry.second->getState() == "TX"){
            // cout << entry.first << endl;
            comboDemogData *demogForCounty;
            if(countyDmapEntry(entry.first) != NULL){
                demogForCounty = countyDmapEntry(entry.first);
            }
            if(demogForCounty != NULL)
            {
                theCountiesShootingData.push_back(entry.second);
                theCountiesDemogData.push_back(demogForCounty);
            }
          }
        }
    std::ofstream myFile;
    myFile.open ("countiesPerArmedTX.csv"); 
    // Header Line
     myFile << "County,NumArmedShootings,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getArmedData().getArmedCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBodyCamTX.csv");

    myFile << "County,NumBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getBodyCamData().getBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerMentalIllnessTX.csv");

    myFile << "County,NumMentalIllness,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getMIData().getMentalI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerWasFleeingTX.csv");

    myFile << "County,NumWereFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getFleeingData().getTriedFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerUnder18TX.csv");

    myFile << "County,NumUnder18,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getpopUnder18Count() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();

    myFile.open("countiesPerBelowPovertyTX.csv");

    myFile << "County,NumBelowPoverty,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theCountiesShootingData.size(); i++){
        auto shootingObj = theCountiesShootingData[i];
        auto demogObj = theCountiesDemogData[i];
          if(shootingObj !=NULL && demogObj != NULL){
            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << demogObj->getBelowPovertyCount() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
          }
    }
    myFile.close();
    }


  void sortRacialDemogDemogCounties()
  {
    std::vector<comboDemogData *> theCountiesSortedOnBlackPerc;
    for (const auto entry : allCountyDData)
    {
      theCountiesSortedOnBlackPerc.push_back(entry.second);
    }
    std::sort(theCountiesSortedOnBlackPerc.begin(), theCountiesSortedOnBlackPerc.end(), compareBlackPerc);

    std::vector<comboDemogData *> theCountiesSortedOnHispanicPerc;
    for (const auto entry : allCountyDData)
    {
      theCountiesSortedOnHispanicPerc.push_back(entry.second);
    }
    std::sort(theCountiesSortedOnHispanicPerc.begin(), theCountiesSortedOnHispanicPerc.end(), compareHispanicPerc);

    std::vector<comboDemogData *> theCountiesSortedOnWhitePerc;
    for (const auto entry : allCountyDData)
    {
      theCountiesSortedOnWhitePerc.push_back(entry.second);
    }
    std::sort(theCountiesSortedOnWhitePerc.begin(), theCountiesSortedOnWhitePerc.end(), compareWhitePerc);

    std::vector<comboDemogData *> theCountiesSortedOnNativeAmerPerc;
    for (const auto entry : allCountyDData)
    {
      theCountiesSortedOnNativeAmerPerc.push_back(entry.second);
    }
    std::sort(theCountiesSortedOnNativeAmerPerc.begin(), theCountiesSortedOnNativeAmerPerc.end(), compareNativeAmerPerc);

    std::ofstream myFile;
    myFile.open ("countiesSortedOnBlackPerc.csv");
    myFile << "State,County,BlackPerc\n";
    for(auto obj: theCountiesSortedOnBlackPerc){
      myFile <<  obj->getName() << "," << obj->getRegionType() << "," << obj->getBlackPerc() << "\n";
    }
    myFile.close();

    myFile.open ("countiesSortedOnHispanicPerc.csv");
    myFile << "State,County,HispanicPerc\n";
    for(auto obj: theCountiesSortedOnHispanicPerc){
      myFile <<  obj->getName() << "," << obj->getRegionType() << "," << obj->getHispanicPerc() << "\n";
    }
    myFile.close();


    myFile.open ("countiesSortedOnWhitePerc.csv");
    myFile << "State,County,WhitePerc\n";
    for(auto obj: theCountiesSortedOnWhitePerc){
      myFile << obj->getName() << "," << obj->getRegionType() << "," << obj->getWhitePerc() << "\n";
    }
    myFile.close();


    myFile.open ("countiesSortedOnNativeAmerPerc.csv");
    myFile << "State,County,NativeAmerPerc\n";
    for(auto obj: theCountiesSortedOnNativeAmerPerc){
      myFile << obj->getName() << "," << obj->getRegionType() << "," << obj->getNativePerc() << "\n";
    }
    myFile.close();
    

  }

  void highestPovLevels()
  {
    std::vector<comboDemogData *> theCounties;
    for (const auto entry : allCountyDData)
    {
      theCounties.push_back(entry.second);
    }
    std::sort(theCounties.begin(), theCounties.end(), comparePovLevelsHighLow);

    cout << "Counties with highest poverty levels: \n";
    for (int i = 0; i < 10; i++)
    {
    cout << i << ".) " << theCounties[i]->getRegionType() << " in this state ->" << theCounties[i]->getState() << " had this \% below poverty level ->" << theCounties[i]->getBelowPoverty() << endl;
    }

  }

private:
  // Private data like maps and stuff
  // map for county hospital data
  std::map<string, comboHospitalData *> allCountyHData;
  // map for county name to demog data
  std::map<string, comboDemogData *> allCountyDData;
  // map for county name to shooting data
  std::map<string, comboShootingData *> allCountySData;

  // helper map to create aggregates from city -> county
  std::map<string, string> cityToCounty;

  static bool compareNumShootings(comboShootingData *a, comboShootingData *b)
  {
    return (a->getNumCases() > b->getNumCases());
  }

  static bool compareBlackPerc(comboDemogData *a, comboDemogData *b)
  {
    return (a->getBlackPerc() > b->getBlackPerc());
  }

  static bool compareWhitePerc(comboDemogData *a, comboDemogData *b)
  {
    return (a->getWhitePerc() > b->getWhitePerc());
  }
  static bool compareHispanicPerc(comboDemogData *a, comboDemogData *b)
  {
    return (a->getHispanicPerc() > b->getHispanicPerc());
  }
  static bool compareNativeAmerPerc(comboDemogData *a, comboDemogData *b)
  {
    return (a->getNativePerc() > b->getNativePerc());
  }
  static bool compareHSGraduatesLowHigh(comboDemogData *a, comboDemogData *b)
  {
    return (a->getHSup() < b->getHSup());
  }

  static bool comparePovLevelsHighLow(comboDemogData *a, comboDemogData *b)
  {
    return (a->getBelowPoverty() > b->getBelowPoverty());
  }

};

#endif
