class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());

        if (!st.count(endWord)) return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        st.erase(beginWord);

        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            if (word == endWord) return steps;

            for (int i = 0; i < word.size(); i++) {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    if (ch == original) continue;

                    word[i] = ch;

                    if (st.count(word)) {
                        q.push({word, steps + 1});
                        st.erase(word);
                    }
                }

                word[i] = original;
            }
        }

        return 0;
    }
};