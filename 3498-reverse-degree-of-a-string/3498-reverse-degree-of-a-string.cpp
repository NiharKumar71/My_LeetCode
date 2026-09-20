class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            // Reverse alphabet value:
            // a -> 26, b -> 25, ..., z -> 1
            int value = 'z' - s[i] + 1;

            // Position in the string is i + 1
            ans += value * (i + 1);
        }

        return ans;
    }
};