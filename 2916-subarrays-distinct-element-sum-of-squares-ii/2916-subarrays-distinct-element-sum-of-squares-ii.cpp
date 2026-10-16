
class LazySegmentTree {
    static const long long MOD = 1000000007;
    int n;
    vector<long long> sum, sq, lazy;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;

        sq[node] = (sq[node] + 2LL * val % MOD * sum[node] % MOD
                    + val * val % MOD * len % MOD) % MOD;

        sum[node] = (sum[node] + val * len) % MOD;
        lazy[node] = (lazy[node] + val) % MOD;
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0 || l == r) return;

        int mid = l + (r - l) / 2;
        long long val = lazy[node];

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        lazy[node] = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);

        int mid = l + (r - l) / 2;

        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
        sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
    }

public:
    LazySegmentTree(int size) : n(size) {
        sum.assign(4 * n, 0);
        sq.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void updateRange(int l, int r) {
        if (l <= r) {
            update(1, 0, n - 1, l, r);
        }
    }

    long long getSquareSum() {
        return sq[1];
    }
};

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1000000007;
        int n = nums.size();

        LazySegmentTree tree(n);
        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last.count(nums[i]) ? last[nums[i]] : -1;

            tree.updateRange(prev + 1, i);
            last[nums[i]] = i;

            ans = (ans + tree.getSquareSum()) % MOD;
        }

        return (int)ans;
    }
};
