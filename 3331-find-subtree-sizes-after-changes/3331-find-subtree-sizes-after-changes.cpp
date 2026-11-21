class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent(n, -1);
        vector<int> last(26, -1);
        vector<int> old(n, -1);

        stack<pair<int, int>> st;
        st.push({0, 0});

        while (!st.empty()) {
            auto [u, state] = st.top();
            st.pop();

            int c = s[u] - 'a';

            if (state == 0) {
                old[u] = last[c];

                if (u == 0) {
                    newParent[u] = -1;
                } else {
                    newParent[u] = (last[c] == -1) ? parent[u] : last[c];
                }

                last[c] = u;

                st.push({u, 1});

                for (int v : adj[u]) {
                    st.push({v, 0});
                }
            } else {
                last[c] = old[u];
            }
        }

        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> order;
        stack<int> st2;
        st2.push(0);

        while (!st2.empty()) {
            int u = st2.top();
            st2.pop();

            order.push_back(u);

            for (int v : tree[u]) {
                st2.push(v);
            }
        }

        vector<int> ans(n, 1);

        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            ans[newParent[u]] += ans[u];
        }

        return ans;
    }
};