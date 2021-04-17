import csv
import fuzzywuzzy
from fuzzywuzzy import fuzz
from fuzzywuzzy import process

print (fuzz.partial_ratio("St. Louis", "St Louis"))

countyToStateDict = {}
cityToCountyDict = {}


with open("us_cities_states_counties_comma_separated.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        if(row["City alias"]) not in cityToCountyDict:
            cityToCountyDict[ row["City alias"] ] = row["County"]
            if(row["County"]) not in countyToStateDict:
                countyToStateDict[row["County"]] = row["State short"]


with open("simple_uscities.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        if(row["city_ascii"]) not in cityToCountyDict:
            cityToCountyDict[row["city_ascii"]] = row["county_name"]
            if(row["county_name"]) not in countyToStateDict:
                countyToStateDict[row["county_name"]] = row["state_id"]

#print(countyToStateDict)
print(cityToCountyDict)

'''
# This is create a csv with city+state, county of many different city to county csv
with open('comboUSCities.csv', mode='w') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONE, escapechar='\n')
    writer.writerow(['City','County', 'State'])
    for key in cityToCountyDict:
        writer.writerow([key, cityToCountyDict[key], countyToStateDict[cityToCountyDict[key]]])
'''


potentialChangesDict = {}

# Clean Police_shooting csv
'''
with open("police_shootings_cleaned.csv", mode='w') as shooting_file:
    myFields =['Person.Name','Person.Age','Person.Gender','Person.Race','Incident.Date.Month','Incident.Date.Day','Incident.Date.Year','Incident.Date.Full','Incident.Location.City','Incident.Location.State','Factors.Armed','Factors.Mental-Illness','Factors.Threat-Level','Factors.Fleeing','Shooting.Manner','Shooting.Body-Camera']
    writer = csv.DictWriter(shooting_file, fieldnames=myFields)
    writer.writeheader()
    with open("police_shootings.csv", 'r') as file:
        shooting = csv.DictReader(file)
        for row in shooting:
            incidentCity = row["Incident.Location.City"]
            if (row["Incident.Location.City"].find("County") != -1):
                writer.writerow(row)
                continue
            else:
                if (row["Incident.Location.City"] ) in cityToCountyDict:
                    tmp = row["Incident.Location.City"]
                    row["Incident.Location.City"] = cityToCountyDict[row["Incident.Location.City"]] + " County"
                    print("{0} was placed in this county ->{1}, within this state {2}".format(tmp, cityToCountyDict[tmp], countyToStateDict[cityToCountyDict[tmp]]))
                
                else:
                    replacingCounty = ""
                    highestFuzzPartialRatio = 0.0
                    for key in cityToCountyDict:
                        if( countyToStateDict[cityToCountyDict[key]] == row["Incident.Location.State"]):
                            tmpPartialRatio = fuzz.partial_ratio(key, row["Incident.Location.City"])
                            if(tmpPartialRatio > highestFuzzPartialRatio) :
                                highestFuzzPartialRatio = tmpPartialRatio
                                replacingCounty = cityToCountyDict[key] + " County"
                    #print("{0} was replaced by {1}".format(row["Incident.Location.City"], replacingCounty))    
                    if(highestFuzzPartialRatio > 88):        
                        row["Incident.Location.City"] = replacingCounty
                writer.writerow(row)

'''

                
