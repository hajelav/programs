#! /bin/python
import sys
import csv
import json
from pprint import pprint
import traceback


'''
This function compares two dictionaries,
returns True/False
'''
def compareDict(dictOne,dictTwo):

    if((not dictOne) or (not dictTwo)):
        return False

    if(len(dictOne) != len(dictTwo)):
            return False
    for key in dictOne:
        if key not in dictTwo:
            return False
    return True


'''
parse the facility schema json and convert it into dictionary
'''
def loadFacilitySchema(fileName):
    facilitySchema = {}
    try:
        facilitySchema = json.load(open(fileName))
        #pprint(facilitySchema)
    except:
        raise
    return facilitySchema

'''
parses the Facilities.csv and stores it into csv.
Other than storing the csv into list, we check if the schema of csv
matches with the json config. This is done because, in future we may want to
enhance the facilities, we need to update the jsonfile( where is schema is
defined)
'''
def getFacilitiesFromCsv(jsonConfig, csvFile):

    facilityList = []
    try:
        with open(csvFile) as csvfile:
            dictReader = csv.DictReader(csvfile)
            schema = loadFacilitySchema(jsonConfig)

            for row in dictReader:
                if(compareDict(schema, row)):
                        facilityList.append(row)
                else:
                    print 'csv file doesnt match the schema %s' %traceback.format_exc()
                    return facilityList

    except Exception as e:
        print 'error parsing facilities.csv %s' %traceback.format_exc()

    #sort the facility list , as we want to always pick the the cheapest loan
    if(facilityList):
        facilityList = sorted(facilityList, key=lambda k: float(k['interest_rate']))

    return facilityList

if __name__ == "__main__":

    print json.dumps(getFacilities("facilitySchema.json","facilities.csv"), indent=4)

