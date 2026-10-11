class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            // Special element tab hai jab i, n ko divide kare
            if (n % i == 0) {
                ans += nums[i - 1] * nums[i - 1];
            }
        }

        return ans;
    }
};