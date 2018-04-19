class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_table;
        for(int i=0; i<nums.size(); i++) {
            int right = target - nums[i];
            if(hash_table.count(right)) {
                return {hash_table[right],i};
            }
            hash_table[nums[i]] =  i;
        }
        return {-1};
    }
};
