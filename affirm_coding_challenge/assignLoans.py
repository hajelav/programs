#! /bin/python
import sys
import csv
import json
from facilities import facility
from covenants import covenant


'''
creates a new csv file
'''
def writeToCsv(fileName, data, fieldList):
    with open(fileName, "wb") as out_file:
        writer = csv.DictWriter(out_file, delimiter=',',extrasaction='ignore', fieldnames=fieldList)
        writer.writeheader()
        for row in data:
            writer.writerow(row)
'''
gets the covenant data(max_default_likelihood, banned_state) from loan
'''
def getCovenantListFromLoan(row):

    d = {}
    result = {}

    covenantsLoanMapDict = {}
    covenantList =\
            covenant.getCovenantList('covenants/covenantFields.json')

    if(covenantList):

        '''
        the covenants fields from the loan.csv and covenants.csv are different,
        for eg state and banned_state so to be able to compare the fields, we
        need to refer to the config file covenantsFields.json to get the
        mapping. Ths idea behind introducing a json config file is make the
        solution more scalable. In future , if you need to add more covenants,
        you can just add it to the config file(along with data types[int, char,
        float] for comparision, though not implemented in this code) and add
        corresponding mapping of the fields used in  covenants.csv

        '''
        covenantsLoanMap = covenant.getCovenantsLoanMap('covenants/covenantFields.json')

        if(len(covenantsLoanMap) == len(covenantList)):

            for l in covenantList:
                d[covenantsLoanMap[l]] = row[l]
            result['amount'] = row['amount']
            result['covenantList'] = d
            #print json.dumps(d, indent = 4)

    else:
        print 'covenant schema not defined'
    return result


'''
check if any of the covenants are violated or not.
True - if not violated
False - if violated
'''
def searchCovenantCsv(d):

        covenantCsvList = []
        covenantsLoanMap = {}

        covenantCsvList = \
                covenant.getCovenantListFromCsv('covenants/covenantFields.json',\
                'covenants/covenants.csv')


        for row in covenantCsvList:
            if(d['bank_id'] == row['bank_id'] and d['facility_id'] ==\
                    row['facility_id']):

                if (d.has_key('covenantList') and d['covenantList']):

                    for key in d['covenantList']:

                        if(key == "banned_state"):
                            if(row[key] and row[key] == d['covenantList'][key]):
                                return False

                        if(key == "max_default_likelihood"):
                            if(row[key] and (float(d['covenantList'][key]) > float(row[key]))):
                                return False


        return True

'''
check if any amount in loan can be satisfied with any facility
'''
def searchFacilityCsv(covenantDataFromLoan, facilityList):
    row = None
    facility_id = ""
    if facilityList:
        for row in facilityList:

            #print float(row['amount']), float(d['amount'])
            if float(row['amount']) >= float(covenantDataFromLoan['amount']):

                #append the bank_id and facility id
                covenantDataFromLoan['bank_id'] = row['bank_id']
                covenantDataFromLoan['facility_id'] = row['id']

                #update the amount in facility list, if we able to find a loan
                #where none of convenants were violated
                if(searchCovenantCsv(covenantDataFromLoan)):
                    row['amount'] = (float(row['amount']) -\
                            float(covenantDataFromLoan['amount']))
                    return row
    return row


def calculate_yield(assignLoanList):
    yield_list =[]
    for row in assignLoanList:
        expected_yield = ((1.0- float(row['default_likelihood'])) *  \
            float(row['loan_interest_rate']) * float(row['amount'])) \
            - (float(row['default_likelihood']) * float(row['amount']) ) \
            - (float(row['facility_interest_rate']) * float(row['amount']))
        if(not facility_exists(row['facility_id'],yield_list,expected_yield)):
            ind ={}
            ind['facility_id'] =row['facility_id']
            ind['expected_yield'] = int(expected_yield)
            yield_list.append(ind)
    return yield_list

def facility_exists(facility_id, yield_list,expected_yield):
    for i in yield_list:
        if i['facility_id'] == facility_id:
            i['expected_yield'] = float(i['expected_yield']) + float(expected_yield)
            return True
        else:
            return False
'''
main wrapper function to assign the loans against the facilities.
program flow:
    1. First we the get the list of facilties from csv
    2. We get the list of loans from loans.csv
    3. we go through each loan ( in a for loop )
        3.1 for each loan , we get the a subset of fields which form the
        covenant data(covenantData)
        3.2 get the amount from loan, and compare it against the amount in
        facility list
        3.3 if we find an amount in facility which can satisfy loan, then we
            append convenant data with corresponding bank_id and facility_id
        3.4 With the appended covenant data formed in 3.3, we check this data
        against the covenants list(convenant.csv).
        3.5 if none of the covenant checks fails, we extract the loan_id from
        loan and facility_id from covenant data and append to assignment.csv
        3.6 go to step 3

'''
def assignLoans():

    assignLoanList = []
    facilityList =\
            facility.getFacilitiesFromCsv('facilities/facilitySchema.json',
                    'facilities/facilities.csv')

    with open("loans/loans.csv") as csvfile:
        dictReader = csv.DictReader(csvfile)

        for loan in dictReader:
            assignment = {}
            covenantData = getCovenantListFromLoan(loan)
            if covenantData:
                selected_facility = searchFacilityCsv(covenantData, facilityList)
                if(selected_facility is not None ):
                    assignment['loan_id'] = loan['id']
                    assignment['default_likelihood']=loan['default_likelihood']
                    assignment['loan_interest_rate']=loan['interest_rate']
                    assignment['facility_id'] = covenantData['facility_id']
                    assignment['facility_interest_rate'] =selected_facility['interest_rate']
                    assignment['amount'] = covenantData['amount']
                    assignLoanList.append(assignment)
        print json.dumps(assignLoanList, indent=4)

    #write the expected_yeild to yield.csv
    writeToCsv('yield.csv', calculate_yield(assignLoanList),['expected_yield','facility_id'])

    #write the assignment list to assignment.csv
    writeToCsv('assignment.csv', assignLoanList,['loan_id','facility_id'])

if __name__ == "__main__":
    assignLoans()

