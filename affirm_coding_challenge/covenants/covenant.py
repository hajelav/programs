#! /bin/python
import sys
import csv
import json
import traceback

def getCovenantList(fileName):
    covenantList = []
    try:
        schema = json.load(open(fileName))
        covenantList = schema['covenantList']
                    #pprint(facilitySchema)
    except Exception as e:
        print 'error parsing covenantFields.json:%s' %traceback.format_exc()

        pass
    return covenantList

def getCovenantsLoanMap(fileName):
    map = {}
    try:
        schema = json.load(open(fileName))
        map = schema['CovenantsLoanMap']
                    #pprint(facilitySchema)
    except:
        pass
    return map

def getCovenantListFromCsv(jsonConfig, csvFile):

    covenantCsvList = []
    try:
        with open(csvFile) as csvfile:
            dictReader = csv.DictReader(csvfile)
            #schema = loadFacilitySchema(jsonConfig)

            for row in dictReader:
                covenantCsvList.append(row)

    except Exception as e:
        #e = sys.exc_info()[0]
        print 'error parsing covenants.csv %s' %traceback.format_exc()

    return covenantCsvList


if __name__ == "__main__":


     #print getCovenantList('covenantFields.json')
     print\
     json.dumps(getCovenantListFromCsv('covenantFields.json','covenants.csv'),\
             indent=4)

