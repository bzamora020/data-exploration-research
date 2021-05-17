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
        cityToCountyDict[ row["City alias"] + row["State short"] ] = [row["County"], row["State short"]] # the keys are the headers to the csv entries
        #countyToStateDict[row["County"] + row["State short"]] = row["State short"]


with open("simple_uscities.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        cityToCountyDict[row["city_ascii"] + row["state_id"]] = [row["county_name"], row["state_id"] ]  
        #countyToStateDict[row["county_name"] + row["state_id"]] = row["state_id"]

#print(countyToStateDict)
#print(cityToCountyDict)


# This is create a csv with city+state, county of many different city to county csv
with open('comboUSCities.csv', mode='w') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONE, escapechar='\n')
    writer.writerow(['City','County', 'State'])
    for key in cityToCountyDict:
        writer.writerow([key.replace(cityToCountyDict[key][1], ""), cityToCountyDict[key][0], cityToCountyDict[key][1]])


potentialChangesDict = {}
# Clean Demog Data

with open("county_demographics_cleaned.csv", mode = 'w') as demog_file:
    myFields = ["County","State","Age.Percent 65 and Older","Age.Percent Under 18 Years","Age.Percent Under 5 Years","Education.Bachelor's Degree or Higher","Education.High School or Higher","Employment.Nonemployer Establishments","Employment.Private Non-farm Employment","Employment.Private Non-farm Employment Percent Change","Employment.Private Non-farm Establishments","Ethnicities.American Indian and Alaska Native Alone","Ethnicities.Asian Alone","Ethnicities.Black Alone","Ethnicities.Hispanic or Latino","Ethnicities.Native Hawaiian and Other Pacific Islander Alone","Ethnicities.Two or More Races","Ethnicities.White Alone","Ethnicities.White Alone, not Hispanic or Latino","Housing.Homeownership Rate","Housing.Households","Housing.Housing Units","Housing.Median Value of Owner-Occupied Units","Housing.Persons per Household","Housing.Units in Multi-Unit Structures","Income.Median Houseold Income","Income.Per Capita Income","Income.Persons Below Poverty Level","Miscellaneous.Building Permits","Miscellaneous.Foreign Born","Miscellaneous.Land Area","Miscellaneous.Language Other than English at Home","Miscellaneous.Living in Same House +1 Years","Miscellaneous.Manufacturers Shipments","Miscellaneous.Mean Travel Time to Work","Miscellaneous.Percent Female","Miscellaneous.Veterans","Population.2010 Population","Population.2014 Population","Population.Population Percent Change","Population.Population per Square Mile","Sales.Accommodation and Food Services Sales","Sales.Merchant Wholesaler Sales","Sales.Retail Sales","Sales.Retail Sales per Capita","Employment.Firms.American Indian-Owned","Employment.Firms.Asian-Owned","Employment.Firms.Black-Owned","Employment.Firms.Hispanic-Owned","Employment.Firms.Native Hawaiian and Other Pacific Islander-Owned","Employment.Firms.Total","Employment.Firms.Women-Owned"]
    writer = csv.DictWriter(demog_file, fieldnames = myFields, delimiter=',', quotechar='"', quoting=csv.QUOTE_ALL, escapechar='\n')
    writer.writeheader()
    with open("county_demographics.csv", 'r', encoding="utf8", errors='ignore') as file1:
        demog = csv.DictReader(file1)
        for row in demog:
            if(row["County"].find("County") != -1):
                if(row["County"].find("St.") != -1):
                    row["County"] = row["County"].replace("St.", "Saint")
            elif(row["County"].find("city") != -1):
                row["County"] = row["County"].replace(" city", "")
            """ elif(row["County"].find("Parish") != -1):
                row["County"] = row["County"].replace(" Parish", "")
                if(row["County"].find("St.") != -1):
                    row["County"] = row["County"].replace("St.", "Saint") """
            writer.writerow(row)
 


# Clean Police_shooting csv,

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
            #Check if entries have a problematic comma, this is a good for loop to do any checking for all the entries
            for i in range(len(myFields)):
                if(row[myFields[i]].find(",") != -1):
                    row[myFields[i]] = row[myFields[i]].replace(",", "")
                if(myFields[i] == "city"):
                    if(row["city"].find("St.") != -1):
                        row["city"] = row["city"].replace("St.", "Saint")
            incidentCity = row["city"] + row["state"]
            #Some entries already have a county skip these rows
            if (row["city"].find("County") != -1):
                writer.writerow(row)
                #print("We already had a county entry")
                continue
            else:
                #If its a city we know a mapping to, replace it with its respective county
                if (incidentCity ) in cityToCountyDict:
                    #print("We know this city")
                    if(incidentCity.find("LA") != -1):
                        row["city"] = cityToCountyDict[incidentCity][0] + " Parish"
                    elif(incidentCity.find("AK") != -1):
                        row["city"] = cityToCountyDict[incidentCity][0] + " Borough"
                    else:
                        row["city"] = cityToCountyDict[incidentCity][0] + " County"
                    #print("{0} was placed in this county ->{1}, within this state {2}".format(tmp, cityToCountyDict[tmp], countyToStateDict[cityToCountyDict[tmp]]))
                #Else we have to do some fuzzy string matching
                else:
                    replacingCounty = ""
                    highestFuzzPartialRatio = 0.0
                    #Find the max partial ratio between any cities we know and the city from the entry that are in the same state as the entry
                    for key in cityToCountyDict:
                        if( cityToCountyDict[key][1] == row["state"]): # check if in same state
                            tmpPartialRatio = fuzz.partial_ratio(key.replace(row["state"], ""), row["city"]) # compute ratio
                            if(tmpPartialRatio > highestFuzzPartialRatio) : # algorithm for finding the max
                                highestFuzzPartialRatio = tmpPartialRatio
                                replacingCounty = cityToCountyDict[key][0] + " County" 
                    #print("{0} was replaced by {1}".format(row["Incident.Location.City"], replacingCounty))  
                    # Only replace if the max partial ratio was greater than 88 (used as an index bc that's the partial ratio between St. Louis and St Louis)  
                    if(highestFuzzPartialRatio > 88):
                        pass        
                        #row["city"] = replacingCounty
                
                writer.writerow(row)
