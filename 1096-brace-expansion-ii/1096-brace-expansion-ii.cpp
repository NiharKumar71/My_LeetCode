class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int pos = 0;

        set<string> result = parseExpression(expression, pos);

        return vector<string>(result.begin(), result.end());
    }

private:
    set<string> parseExpression(string& s, int& pos) {
        set<string> result = parseTerm(s, pos);

        while (pos < s.size() && s[pos] == ',') {
            pos++;

            set<string> next = parseTerm(s, pos);

            // Union
            result.insert(next.begin(), next.end());
        }

        return result;
    }

    set<string> parseTerm(string& s, int& pos) {
        set<string> result = {""};

        while (pos < s.size() &&
               s[pos] != '}' &&
               s[pos] != ',') {

            set<string> next = parseFactor(s, pos);

            set<string> temp;

            // Concatenation
            for (const string& a : result) {
                for (const string& b : next) {
                    temp.insert(a + b);
                }
            }

            result = temp;
        }

        return result;
    }

    set<string> parseFactor(string& s, int& pos) {
        set<string> result;

        if (s[pos] == '{') {
            pos++;  // skip '{'

            result = parseExpression(s, pos);

            pos++;  // skip '}'
        }
        else {
            result.insert(string(1, s[pos]));
            pos++;
        }

        return result;
    }
};