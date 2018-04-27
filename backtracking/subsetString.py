#!/bin/python
import sys
#https://www.youtube.com/watch?v=NdF1QDTRkck&index=10&list=PLFE6E58F856038C69
# start from 12:18

'''
program to find all subset of a given string:

    All subsets(of a string of n chars) is the sum of number of ways of choosing
    0 to n chars.

    No of subsets = nC0 + nC1 + nC2 + ....+ nCn

In permutation/combination type of problems, always take two strings
1. originalString
2.ProcessedSoFar

Try to think recursively solving the problem by moving the chars from original
to processed string


idea is to  take an element and
1. include it in subset
2. exclude from the subset

nCr = no of ways when one elements is included in subset + no of ways when an
element is excluded from subset

ir nCr =  n-1Cr-1 ( element included : no of ways to choose the remaining r-1
from n-1) + n-1Cr (element excluded : no of ways to choose r-1 from n-1 )

'''

def subsetsOfString(origS, procSoFar, index) :

    originalString = list(origS) #declare a local stack variable, as list is passed by refernce in python
    processedSoFar = list(procSoFar)

    if(not originalString):
        print processedSoFar
        return

    else:

        '''
        select the first char of the originalString list  and include it in the
        processedSoFar list
        '''
        processedSoFar.append(originalString[index]) #append the first char of  originalString to processedSoFar list
        originalString.pop(index) #now pop the originalString
        #print originalString

        subsetsOfString(originalString, processedSoFar, index)


        '''
        select the first char of the originalString list  and exclude it from the
        processedSoFar list
        Note that both orginal and processed list are declared as stack
        variables and not passed as reference because , by default lists are
        passed as reference in python.
        '''
        processedSoFar.pop() #exculde it from processedSoFar list

        subsetsOfString(originalString, processedSoFar, index)





if __name__ == "__main__":

    print 'enter string'
    originalString = list(raw_input())
    processedSoFar = []
    subsetsOfString(originalString, processedSoFar, 0)

