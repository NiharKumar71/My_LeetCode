class Solution {
public:
    int minInsertions(string s) {
        int open = 0;
        int insertions = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } else {
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } else {
                    insertions++;
                }

                open--;

                if (open < 0) {
                    insertions++;
                    open = 0;
                }
            }
        }

        return insertions + open * 2;
    }
};