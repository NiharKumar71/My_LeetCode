class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                k &= nums[i];
            }
        }

        return k == INT_MAX ? 0 : k;
    }
};