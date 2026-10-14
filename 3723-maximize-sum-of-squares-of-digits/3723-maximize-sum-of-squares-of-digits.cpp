class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num) {
            return "";
        }

        string ans(num, '0');

        for (int i = 0; i < num; i++) {
            int digit = min(9, sum);
            ans[i] = '0' + digit;
            sum -= digit;
        }

        if (sum > 0) {
            return "";
        }

        sort(ans.begin(), ans.end(), greater<char>());
        return ans;
    }
};