#!/bin/python

import sys
from collections import deque

#Remove Invalid Parentheses
#https://github.com/tongzhang1994/Facebook-Interview-Coding/blob/master/301.%20Remove%20Invalid%20Parentheses.java
# https://github.com/tongzhang1994

'''
BFS -> guarantee the number of parentheses that need to be removed is minimal
// With the input string s, we generate all possible states by removing one ( or
        // ), check if they are valid,
// if found valid ones on the current level, put them to res and we are done,
// otherwise add them to a queue and carry on to the next level
Time: T(n) = n x C(n, n) + (n-1) x C(n, n-1) + ... + 1 x C(n, 1) = n x 2^(n-1).
// In BFS we handle the states level by level, in the worst case, we need to
// handle all the levels,
// we can analyze the time complexity level by level and add them up to get the
// final complexity.
// On the first level, there's only one string which is the input string s,
// let's say the length of it is n, to check whether it's valid,
// we need O(n) time. On the second level, we remove one ( or ) from the first
// level, so there are C(n, n-1) new strings,
// each of them has n-1 characters, and for each string, we need to check
// whether it's valid or not, thus the total time complexity
// on this level is (n-1) x C(n, n-1). Come to the third level, total time
// complexity is (n-2) x C(n, n-2), so on and so forth...
Run: e.x. "(a)())()"
// q = ["(a)())()"]
//     ["a)())()", "(a())()", "(a))()", "(a)()()", "(a)()))", "(a)())("]
// visited = ["(a)())()", "a)())()", "(a())()", "(a))()", "(a)()()", "(a)()))",
// "(a)())("]
// res = ["(a())()", "(a)()()"]

'''

#check if the char is a parentheses or not
def isParentheses(c):
    if(c == '(' or c == ')'):
        return True
    else
        return False


#check if the string is a valid string, ie has valid combination of ( and )
def isValid(s):

    for i in range(len(s)):
        if(s[i] == '(')
            count++;
        elif(s[i] == ')')
            count--;

        if(count < 0)
            return false;

    return(count == 0)


def removeInvalidParentheses(s):






if __name__ == "__main__":

    print 'enter parentheses string'
    s = list(raw_input())
    removeInvalidParentheses(s)


