class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 17;

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        vector<int> nxt(n + 1, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            if (!st.empty()) {
                nxt[i] = st.top();
            }

            st.push(i);
        }

        vector<vector<int>> up(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> sum(LOG, vector<long long>(n + 1, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            int j = nxt[i];
            sum[0][i] = 1LL * nums[i] * (j - i)
                      - (pref[j] - pref[i]);
        }

        for (int p = 1; p < LOG; p++) {
            for (int i = 0; i < n; i++) {
                int mid = up[p - 1][i];

                up[p][i] = up[p - 1][mid];

                sum[p][i] = sum[p - 1][i]
                          + sum[p - 1][mid];
            }
        }

        auto getCost = [&](int l, int r) {
            long long cost = 0;
            int cur = l;

            for (int p = LOG - 1; p >= 0; p--) {
                if (up[p][cur] <= r) {
                    cost += sum[p][cur];
                    cur = up[p][cur];
                }
            }

            cost += 1LL * nums[cur] * (r - cur + 1)
                  - (pref[r + 1] - pref[cur]);

            return cost;
        };

        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int lo = 0, hi = r;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (getCost(mid, r) <= k) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }

            ans += r - lo + 1;
        }

        return ans;
    }
};