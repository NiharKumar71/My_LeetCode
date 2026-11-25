class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> sa(n), rank(n), newRank(n), lcp(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = nums[i];
        }

        for (int len = 1; len < n; len *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int ra = (a + len < n) ? rank[a + len] : -1;
                int rb = (b + len < n) ? rank[b + len] : -1;

                return ra < rb;
            });

            newRank[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                int ra = (a + len < n) ? rank[a + len] : -1;
                int rb = (b + len < n) ? rank[b + len] : -1;

                newRank[b] = newRank[a] +
                    (rank[a] != rank[b] || ra != rb);
            }

            rank = newRank;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        vector<int> pos(n);

        for (int i = 0; i < n; i++) {
            pos[sa[i]] = i;
        }

        int h = 0;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            if (p == 0) {
                h = 0;
                continue;
            }

            int j = sa[p - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[p] = h;

            if (h > 0)
                h--;
        }

        int ans = n;

        for (int i = 0; i < n; i++) {
            int p = pos[i];
            int longest = lcp[p];

            if (p + 1 < n) {
                longest = max(longest, lcp[p + 1]);
            }

            if (longest < n - i) {
                ans = min(ans, longest + 1);
            }
        }

        return ans;
    }
};