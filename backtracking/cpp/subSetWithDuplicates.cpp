class Solution {
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            vector<vector<int>> result;
            vector<int> temp; 
            int i = 0;

            if(nums.size() == 0){
                return result;
            }
            sort(nums.begin(), nums.end());
            subsetsWithDupUtil(temp, nums, result, i);
            return result;
        }

        void subsetsWithDupUtil(vector<int> temp, vector<int> nums, vector<vector<int>>& result, int i) {

            if(nums.size() == 0) {
                return;
            } 
            result.push_back(temp);

            for (int j = i; j < nums.size(); j++) {
                if (j > i && nums[j] == nums[j - 1]) continue;
                temp.push_back(nums[j]);
                subsetsWithDupUtil(temp, nums, result, j + 1);
                temp.pop_back();
            }
        }
};
