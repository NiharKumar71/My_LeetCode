class Solution {
public:
    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            }
            else if (c == ')') {
                balance--;

                if (balance < 0)
                    return false;
            }
        }

        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            // If valid, this is the minimum-removal level
            if (isValid(cur)) {
                ans.push_back(cur);
                found = true;
            }

            // Don't generate strings with more removals
            // once a valid level has been found.
            if (found)
                continue;

            for (int i = 0; i < cur.size(); i++) {
                // Only remove parentheses
                if (cur[i] != '(' && cur[i] != ')')
                    continue;

                string next = cur.substr(0, i) + cur.substr(i + 1);

                if (!visited.count(next)) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};