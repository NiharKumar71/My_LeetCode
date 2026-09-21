class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // prev[r] = number of subarrays ending at previous index
        // whose product % k == r
        vector<long long> prev(k, 0);

        for (int num : nums) {
            int x = num % k;

            vector<long long> cur(k, 0);

            // Start a new subarray with just nums[i]
            cur[x]++;

            // Extend every subarray ending at the previous position
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * x) % k;
                cur[newRemainder] += prev[r];
            }

            // Every subarray ending here is a valid operation
            for (int r = 0; r < k; r++) {
                ans[r] += cur[r];
            }

            prev = cur;
        }

        return ans;
    }
};