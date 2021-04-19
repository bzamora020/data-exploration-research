import csv
import fuzzywuzzy
from fuzzywuzzy import fuzz
from fuzzywuzzy import process

print (fuzz.partial_ratio("St. Louis", "St Louis"))

countyToStateDict = {}
cityToCountyDict = {}

# Read through both of our csv's to add to our combined list for all cities to counties to state
# If we had more csvs we can add them here in this kind of format
with open("us_cities_states_counties_comma_separated.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        cityToCountyDict[ row["City alias"] ] = row["County"] # the keys are the headers to the csv entries
        countyToStateDict[row["County"]] = row["State short"]


with open("simple_uscities.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        cityToCountyDict[row["city_ascii"]] = row["county_name"]   
        countyToStateDict[row["county_name"]] = row["state_id"]

#print(countyToStateDict)
#print(cityToCountyDict)

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

with open("police_shootings_cleaned.csv", mode='w') as shooting_file:
    #Header fields from WP fatal police shootings csv
    myFields =['id', "name", "date", "manner_of_death","armed", "age", "gender", "race", "city", "state", "signs_of_mental_illness", "threat_level", "flee", "body_camera", "longitude", "latitude", "is_geocoding_exact"] 
    #Open a writer from the csv library, pass in header names, for new cleaned csv
    writer = csv.DictWriter(shooting_file, fieldnames=myFields)
    #Writes the top of the csv file
    writer.writeheader()
    #Open file to be cleaned
    with open("fatal-police-shootings-data.csv", 'r') as file:
        shooting = csv.DictReader(file)
        # read through every row in the dictionary created, every entry is a dictionary Ex. {"city":" Los Angeles"}
        for row in shooting:
            incidentCity = row["city"]
            #Check if entries have a problematic comma, this is a good for loop to do any checking for all the entries
            for i in range(len(myFields)):
                if(row[myFields[i]].find(",") == -1):
                    row[myField[i]] = row[myFields[i]].replace(",", "")
            #Some entries already have a county skip these rows
            if (row["city"].find("County") != -1):
                writer.writerow(row)
                continue
            else:
                #If its a city we know a mapping to, replace it with its respective county
                if (row["city"] ) in cityToCountyDict:
                    tmp = row["city"]
                    row["city"] = cityToCountyDict[row["city"]] + " County"
                    #print("{0} was placed in this county ->{1}, within this state {2}".format(tmp, cityToCountyDict[tmp], countyToStateDict[cityToCountyDict[tmp]]))
                #Else we have to do some fuzzy string matching
                else:
                    replacingCounty = ""
                    highestFuzzPartialRatio = 0.0
                    #Find the max partial ratio between any cities we know and the city from the entry that are in the same state as the entry
                    for key in cityToCountyDict:
                        if( countyToStateDict[cityToCountyDict[key]] == row["state"]): # check if in same state
                            tmpPartialRatio = fuzz.partial_ratio(key, row["city"]) # compute ratio
                            if(tmpPartialRatio > highestFuzzPartialRatio) : # algorithm for finding the max
                                highestFuzzPartialRatio = tmpPartialRatio
                                replacingCounty = cityToCountyDict[key] + " County" 
                    #print("{0} was replaced by {1}".format(row["Incident.Location.City"], replacingCounty))  
                    # Only replace if the max partial ratio was greater than 88 (used as an index bc that's the partial ratio between St. Louis and St Louis)  
                    if(highestFuzzPartialRatio > 88):        
                        row["city"] = replacingCounty
                writer.writerow(row)



                
