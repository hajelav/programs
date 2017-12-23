#!/bin/python
import sys
#https://www.youtube.com/watch?v=uFJhEPrbycQ&list=PLFE6E58F856038C69&index=9
'''
program to find all permutation of a given string
In permutation/combination type of problems, always take two strings
1. originalString
2.ProcessedSoFar

Try to think recursively solving the problem by moving the chars from original
to processed string
'''

def permutationsOfString(originalString, processedSoFar) :


    if(not originalString):
        print processedSoFar
        return

    for i in range(len(originalString)):


        #pop the char at index i from original list and append it to the other list
        processedSoFar.append(originalString[i])
        originalString.pop(i)

        permutationsOfString(originalString, processedSoFar)

        #remove the char which was appended to processedSoFar list and insert it
        #back at index i in originalString
        c = processedSoFar.pop()
        originalString.insert(i, c)





if __name__ == "__main__":

    print 'enter string to permut'
    originalString = list(raw_input())
    processedSoFar = []
    permutationsOfString(originalString, processedSoFar)

