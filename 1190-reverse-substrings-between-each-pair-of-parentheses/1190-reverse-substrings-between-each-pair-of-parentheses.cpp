class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string curr = "";

        for (char c : s) {

            if (c == '(') {
                // Save everything before this '('
                st.push(curr);
                curr = "";
            }
            else if (c == ')') {
                // Reverse the current innermost substring
                reverse(curr.begin(), curr.end());

                // Add it to the previous level
                curr = st.top() + curr;
                st.pop();
            }
            else {
                curr += c;
            }
        }

        return curr;
    }
};