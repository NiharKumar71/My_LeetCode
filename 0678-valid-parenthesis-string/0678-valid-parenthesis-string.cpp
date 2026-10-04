class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;   // minimum possible open brackets
        int high = 0;  // maximum possible open brackets

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // treat '*' as ')'
                high++;  // treat '*' as '('
            }

            // We can never have fewer than 0 unmatched '('
            low = max(low, 0);

            // Even the maximum possibility is invalid
            if (high < 0)
                return false;
        }

        // We need some interpretation where all '(' are matched
        return low == 0;
    }
};