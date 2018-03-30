1. How long did you spend working on the problem? What did you find to be the most
difficult part?

5-6 hrs, mostly time was spent to think about making it scalable and flexible. Details below

2. How would you modify your data model or code to account for an eventual introduction
of new, asofyet unknown types of covenants, beyond just maximum default likelihood
and state restrictions?

To make solution more flexible, I have introduced a convenantField.json config file, which contains
- list of convenant fields
- mapping of these fields with the covenant fields in covenant.csv
If we want to add more covenant fields , we need to update the json file with new covenant fields and mapping,
and add extra columns in the covenant.csv file. Though the current logic is not fully implemented, but I have an 
idea as to how it can be scaled by just modifying json and csv files. We neeed to specify the types data to be compared. 
for eg, currently we are comparing string(state) and float(max_default_likelihood) . For any new covenant we can define a type,
so that we know how to comare against the convenant fields of loan


3. How would you architect your solution as a production service wherein new facilities can
be introduced at arbitrary points in time. Assume these facilities become available by the
finance team emailing your team and describing the addition with a new set of CSVs


All the faciity update emails can be sent to an alias. we can use a polling based mechanism, which reads the csv files from emails and parses all the information.
The new facility based system can be fed into a publisher/subcriber based model like kafka

.
4. Your solution most likely simulates the streaming process by directly calling a method in
your code to process the loans inside of a for loop. What would a REST API look like for
this same service? Stakeholders using the API will need, at a minimum, to be able to
request a loan be assigned to a facility, and read the funding status of a loan, as well as
query the capacities remaining in facilities.

[ Base URL: / ]

HTTP GET  /loan  Gets all loans
HTTP GET  /loan/l{oan_id}  Get a particular loan with loan id
HTTP  PUT /loan/{loan_id}  Assign a loan to fund from a facility.

    The schema of  request payload:
    {

            "id": "string",
            "amount": " string ",
            "interest_rate": " string ",
            "default_liklihood": " string ",
            "state": " string "
    }


    Response Payload:
    201 Created : {“facility_id” :””,”status”:””}

HTTP  GET /facility  Gets all facilities
HTTP  GET /facility /{facility _id} Gets a particular facility with facility id along with the amount remaining
    Response 200 OK
    {

        "facility_id": " string ",
        "initial_amount": " string ",
        "amount_remaining": " string ",
        "interest_rate": " string ",
        "bank_id": " string "
    }

HTTP  PUT /facility/{facility _id}  Update a facility

5. How might you improve your assignment algorithm if you were permitted to assign loans
in batch rather than streaming? We are not looking for code here, but pseudo code or
description of a revised algorithm appreciated.

If batch processing is permitted, the we have to match n loans to m facilities. 
we can sort the loans and facilities based on their amounts, and then try to come up with M pairs 
such that difference of amounts between each pair is minimal. This can be done by forming nXm pairs
and sorting the pairs based on |n-m| values and picking first M pairs. Each batch can process M pairs
till mxn pairs are exhausted


6. Because a number of facilities share the same interest rate, it’s possible that there are a
number of equally appealing options by the algorithm we recommended you use
(assigning to the cheapest facility). How might you tiebreak
facilities with equal interest rates, with the goal being to maximize the likelihood that future loans streaming in will be
assignable to some facility?

one way to break the tie is to select the facility whose updated amount is closet to a given loan amount. we can maintain data structures around the facility amounts
to figure out the nearest loan request. This will help to ensure fewer ties, instead of just picking first/random facility among all other equal-interest facilities


