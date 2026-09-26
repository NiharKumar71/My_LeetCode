class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key -> value
        for (auto &item : knowledge) {
            mp[item[0]] = item[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] != '(') {
                ans += s[i];
                continue;
            }

            // Find ')'
            int j = i + 1;
            while (s[j] != ')') {
                j++;
            }

            // Extract key
            string key = s.substr(i + 1, j - i - 1);

            // Replace key
            if (mp.count(key)) {
                ans += mp[key];
            } else {
                ans += "?";
            }

            // Skip everything through ')'
            i = j;
        }

        return ans;
    }
};