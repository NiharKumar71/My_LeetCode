class Solution {
public:
    static const int MAXK = 5;

    struct Node {
        int prod;
        int cnt[MAXK];

        Node() {
            prod = 1;
            for (int i = 0; i < MAXK; i++)
                cnt[i] = 0;
        }
    };

    int n, k;
    vector<Node> tree;

    Node mergeNodes(const Node& a, const Node& b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        // Prefixes completely inside the left segment
        for (int r = 0; r < k; r++) {
            res.cnt[r] = a.cnt[r];
        }

        // Prefixes = whole left + prefix of right
        for (int r = 0; r < k; r++) {
            int nr = (a.prod * r) % k;
            res.cnt[nr] += b.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, const vector<int>& nums) {
        if (l == r) {
            tree[node].prod = nums[l] % k;
            tree[node].cnt[tree[node].prod] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = mergeNodes(tree[node * 2],
                                 tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            tree[node].prod = value % k;

            for (int i = 0; i < k; i++)
                tree[node].cnt[i] = 0;

            tree[node].cnt[tree[node].prod] = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, value);
        else
            update(node * 2 + 1, mid + 1, r, idx, value);

        tree[node] = mergeNodes(tree[node * 2],
                                 tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return mergeNodes(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int K,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        k = K;

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};