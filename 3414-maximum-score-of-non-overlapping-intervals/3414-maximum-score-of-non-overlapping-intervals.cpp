class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store: {start, end, weight, original index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by ending time
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[0] < y[0];
        });

        vector<long long> ends(n);

        for (int i = 0; i < n; i++) {
            ends[i] = a[i][1];
        }

        // prev[i] = last interval which doesn't overlap with i
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            int l = a[i][0];

            int pos = lower_bound(ends.begin(), ends.begin() + i, l) - ends.begin();

            prev[i] = pos - 1;
        }

        // dp[i][k] = best result using first i intervals and at most k intervals
        vector<vector<long long>> dp(n + 1, vector<long long>(5, -1));
        vector<vector<vector<int>>> chosen(n + 1, vector<vector<int>>(5));

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            int idx = i - 1;

            for (int k = 0; k <= 4; k++) {

                // Don't take this interval
                if (dp[i - 1][k] != -1) {
                    dp[i][k] = dp[i - 1][k];
                    chosen[i][k] = chosen[i - 1][k];
                }

                // Take this interval
                if (k > 0) {
                    int p = prev[idx] + 1;

                    if (dp[p][k - 1] != -1) {
                        long long newWeight =
                            dp[p][k - 1] + a[idx][2];

                        vector<int> candidate = chosen[p][k - 1];
                        candidate.push_back((int)a[idx][3]);

                        sort(candidate.begin(), candidate.end());

                        if (newWeight > dp[i][k] ||
                            (newWeight == dp[i][k] &&
                             candidate < chosen[i][k])) {

                            dp[i][k] = newWeight;
                            chosen[i][k] = candidate;
                        }
                    }
                }
            }
        }

        // Find maximum weight among at most 4 intervals
        long long bestWeight = -1;
        vector<int> answer;

        for (int k = 0; k <= 4; k++) {
            if (dp[n][k] > bestWeight ||
                (dp[n][k] == bestWeight &&
                 chosen[n][k] < answer)) {

                bestWeight = dp[n][k];
                answer = chosen[n][k];
            }
        }

        return answer;
    }
}; 