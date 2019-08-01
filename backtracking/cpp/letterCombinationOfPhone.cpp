#include <map>
class Solution {
    public:

        map<char, string> create_map() {

            map<char, string> m;
            m['1'] = "";
            m['2'] = "abc";
            m['3'] = "def";
            m['4'] = "ghi";
            m['5'] = "jkl";
            m['6'] = "mno";
            m['7'] = "pqrs";
            m['8'] = "tuv";
            m['9'] = "wxyz";
            m['0'] = "";
            m['*'] = "";
            m['#'] = "";

            return m;    
        };

        vector<string> letterCombinations(string digits) {

            map<char, string> keypad;
            string comb;
            vector<string> result;
            keypad = create_map();
            letterCombinationsUtil(digits, 0, comb, result, keypad);
            return result;
        }



        void letterCombinationsUtil(string digits, int i, string &comb, vector<string> &result, map<char, string> &keypad) {

            string str; int j;
            if(digits.length() == 0)
                return;

            if(i == digits.length()) {
                result.push_back(comb);
                return;
            }

            str = keypad[digits[i]];
            for(j=0; j<str.length(); j++) {
                comb.push_back(str[j]);
                letterCombinationsUtil(digits, i+1, comb, result, keypad);
                comb.pop_back();
            }


        }
};
