class Solution {
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            vector<vector<int>> result;
            vector<int> temp; 

            if(nums.size() == 0){
                return result;
            }

            permutUtil(temp, nums, result);
            return result;

        }

        void permutUtil(vector<int>& temp, vector<int>& nums, vector<vector<int>>& result) {

            int i, n1, n2;
            if(nums.size() == 0) {
                result.push_back(temp);
                return;
            }
            for(i=0; i< nums.size(); i++) {
                n1 = nums[i]; // get the element in the array
                temp.push_back(n1); // push it to temp array
                nums.erase(nums.begin() + i); // erase it fro original array
                permutUtil(temp, nums, result);  // recurse with num
                temp.pop_back(); // pop the element from the temp array
                nums.insert(nums.begin()+i, n1); // insert it back to the original array

            }
        }
};
