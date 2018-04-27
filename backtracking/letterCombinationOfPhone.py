#letter combinations of a phone number
#!/bin/python
import sys

phoneMap = {
        "1": [],
        "2": ['a','b','c'],
        "3": ['d', 'e', 'f'],
        "4": ['g', 'h', 'i'],
        "5": ['j', 'k', 'l'],
        "6": ['m', 'n', 'o'],
        "7": ['p', 'q', 'r', 's'],
        "8": ['t', 'u', 'v'],
        "9": ['w', 'x', 'y', 'z'],
        "0": [],
        "*": [],
        "#": []
        }


def letterCombinationUtil(digitList, index, phoneMap, processedSoFar):

    if(index == len(digitList)):
        print processedSoFar
        return

    for c in phoneMap[digitList[index]]:
        processedSoFar.append(c)
        letterCombinationUtil(digitList, index+1, phoneMap, processedSoFar)
        processedSoFar.pop()

def letterCombination(digitsList):
    processedSoFar = []

    #if digit string have any character which does not have letter mapping, then
    # we return empty list
    '''
    for digit in digits:
        if( not phoneMap[digit] ):
            print []
    '''
    letterCombinationUtil(digitList, 0, phoneMap, processedSoFar)


if __name__ == "__main__":

    print 'enter digits string'
    digitList = list(raw_input())
    letterCombination(digitList)
