import csv

comboCitiesDict = {}

with open("us_cities_states_counties_comma_separated.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        if(row["City alias"]) not in comboCitiesDict:
            comboCitiesDict[row["City alias"] + row["State short"]] = row["County"]


with open("simple_uscities.csv", 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        if(row["city_ascii"]) not in comboCitiesDict:
            comboCitiesDict[row["city_ascii"] + row["state_id"]] = row["county_name"]


# This is create a csv with city+state, county of many different city to county csv
with open('comboUSCities.csv', mode='w') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONE, escapechar='\n')
    writer.writerow(['City+State','County'])
    for key in comboCitiesDict:
        writer.writerow([key, comboCitiesDict[key]])

with open("police_shooting.csv", 'r') as shooting_file:
    
    