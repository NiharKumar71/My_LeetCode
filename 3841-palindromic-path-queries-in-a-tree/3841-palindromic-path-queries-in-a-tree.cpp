class Solution {
    struct SegTree {
        int n;
        vector<int> tree;

        SegTree(vector<int>& a) {
            n = a.size();
            tree.assign(4 * n, 0);
            build(1, 0, n - 1, a);
        }

        void build(int p, int l, int r, vector<int>& a) {
            if (l == r) {
                tree[p] = a[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m, a);
            build(p * 2 + 1, m + 1, r, a);
            tree[p] = tree[p * 2] ^ tree[p * 2 + 1];
        }

        void update(int p, int l, int r, int i, int val) {
            if (l == r) {
                tree[p] = val;
                return;
            }
            int m = (l + r) / 2;
            if (i <= m) update(p * 2, l, m, i, val);
            else update(p * 2 + 1, m + 1, r, i, val);
            tree[p] = tree[p * 2] ^ tree[p * 2 + 1];
        }

        int query(int p, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr) return tree[p];
            if (r < ql || l > qr) return 0;
            int m = (l + r) / 2;
            return query(p * 2, l, m, ql, qr) ^
                   query(p * 2 + 1, m + 1, r, ql, qr);
        }

        void update(int i, int val) {
            update(1, 0, n - 1, i, val);
        }

        int query(int l, int r) {
            if (l > r) return 0;
            return query(1, 0, n - 1, l, r);
        }
    };

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n), sz(n, 1), heavy(n, -1);
        vector<int> order = {0};
        parent[0] = 0;

        for (int i = 0; i < (int)order.size(); ++i) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }

        for (int i = n - 1; i > 0; --i) {
            int u = order[i], p = parent[u];
            sz[p] += sz[u];
            if (heavy[p] == -1 || sz[u] > sz[heavy[p]])
                heavy[p] = u;
        }

        vector<int> head(n), pos(n), base(n);
        int timer = 0;
        vector<pair<int, int>> st = {{0, 0}};

        while (!st.empty()) {
            auto [u, h] = st.back();
            st.pop_back();

            for (int x = u; x != -1; x = heavy[x]) {
                head[x] = h;
                pos[x] = timer;
                base[timer++] = 1 << (s[x] - 'a');

                for (int v : adj[x]) {
                    if (v != parent[x] && v != heavy[x])
                        st.push_back({v, v});
                }
            }
        }

        SegTree seg(base);
        vector<bool> ans;

        auto pathXor = [&](int u, int v) {
            int res = 0;
            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]])
                    swap(u, v);
                res ^= seg.query(pos[head[u]], pos[u]);
                u = parent[head[u]];
            }
            if (depth[u] > depth[v]) swap(u, v);
            res ^= seg.query(pos[u], pos[v]);
            return res;
        };

        for (auto& q : queries) {
            if (q[0] == 'u') {
                int u = stoi(q.substr(7));
                char c = q.back();
                s[u] = c;
                seg.update(pos[u], 1 << (c - 'a'));
            } else {
                int p = q.find(' ', 6);
                int u = stoi(q.substr(6, p - 6));
                int v = stoi(q.substr(p + 1));
                int mask = pathXor(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};