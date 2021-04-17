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
                countyToStateDict[row["County"]] = row["State"]


with open("simple_uscities.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        if(row["city_ascii"]) not in cityToCountyDict:
            cityToCountyDict[row["city_ascii"] = row["county_name"]
            if(row["county_name"]) not in countyToStateDict:
                countyToStateDict[row["county_name"]] = row["state_id"]


# This is create a csv with city+state, county of many different city to county csv
with open('comboUSCities.csv', mode='w') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONE, escapechar='\n')
    writer.writerow(['City','County', 'State'])
    for key in cityToCountyDict:
        writer.writerow([key, cityToCountyDict[key], countyToStateDict[cityToCountyDict[key]])


'''
potentialChangesDict = {}

# Clean Police_shooting csv

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
                for key in comboCitiesDict:
                    if((96 > fuzz.partial_ratio(incidentCity, (comboCitiesDict[key][0])) > 88) and (row["Incident.Location.State"] == comboCitiesDict[key][1]) ) :
                        temp = row["Incident.Location.City"]
                        row["Incident.Location.City"] = comboCitiesDict[key][0]
                        print("{0} was replaced by {1}".format(temp, comboCitiesDict[key][0]))
                        writer.writerow(row)
                
                writer.writerow(row)
'''


                
