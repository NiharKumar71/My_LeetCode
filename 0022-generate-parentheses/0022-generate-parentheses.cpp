class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;

        function<void(int, int)> backtrack = [&](int open, int close) {
            // We have used all brackets
            if (open == n && close == n) {
                ans.push_back(cur);
                return;
            }

            // Add '('
            if (open < n) {
                cur.push_back('(');
                backtrack(open + 1, close);
                cur.pop_back();
            }

            // Add ')'
            if (close < open) {
                cur.push_back(')');
                backtrack(open, close + 1);
                cur.pop_back();
            }
        };

        backtrack(0, 0);
        return ans;
    }
};