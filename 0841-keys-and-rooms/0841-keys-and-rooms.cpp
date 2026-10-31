class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();

        vector<bool> visited(n, false);
        stack<int> st;

        st.push(0);
        visited[0] = true;

        int count = 1;

        while (!st.empty()) {
            int room = st.top();
            st.pop();

            for (int key : rooms[room]) {
                if (!visited[key]) {
                    visited[key] = true;
                    count++;
                    st.push(key);
                }
            }
        }

        return count == n;
    }
};