/*
 *https://www.youtube.com/watch?v=NdF1QDTRkck&index=10&list=PLFE6E58F856038C69
 *start from 12:18
 *
 *program to find all subset of a given string:
 *
 *    All subsets(of a string of n chars) is the sum of number of ways of choosing
 *    0 to n chars.
 *
 *    No of subsets = nC0 + nC1 + nC2 + ....+ nCn
 *
 *In permutation/combination type of problems, always take two strings
 *1. originalString
 *2.ProcessedSoFar
 *
 *Try to think recursively solving the problem by moving the chars from original
 *to processed string
 *
 *
 *idea is to  take an element and
 *1. seperate it from the input
 *2. can either include it in subset or not
 *3. recursively form subsets including it
 *4. recursively form subsets excluding it
 *
 *nCr = no of ways when one elements is included in subset + no of ways when an
 *element is excluded from subset
 *
 *ir nCr =  n-1Cr-1 ( element included : no of ways to choose the remaining r-1
 *from n-1) + n-1Cr (element excluded : no of ways to choose r1 from n-1 )
 */


class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            vector<vector<int>> result;
            vector<int> temp; 

            if(nums.size() == 0){
                return result;
            }

            subsetUtil(temp, nums, result);
            return result;
        }

        /*note that we dont pass the nums and temp array as reference*/
        void subsetUtil(vector<int> temp, vector<int> nums, vector<vector<int>>& result) {

            int i, n, front;
            if(nums.size() == 0) {
                result.push_back(temp);
                return;
            } else {

                //push the first element to temp array (ie include element in subset)
                temp.push_back(nums[0]);
                //delete the first element from the original array 
                nums.erase(nums.begin());
                subsetUtil(temp, nums, result); // recurse
                temp.pop_back(); //remove the element from temp ( ie exclude element from subset)
                subsetUtil(temp, nums, result);// recurse
            }
        }
};
