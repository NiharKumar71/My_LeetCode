class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> bonus(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    bonus[i]++;
                }
            }
        }

        const int NEG = -1000000000;
        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int value = bonus[i];

            vector<int> ndp = dp;

            for (int r = 0; r < price && r <= budget; r++) {
                int best = NEG;

                for (int c = r + price; c <= budget; c += price) {
                    int prev = c - price;
                    int t = (prev - r) / price;

                    if (dp[prev] != NEG) {
                        best = max(best, dp[prev] - t);
                    }

                    if (best != NEG) {
                        ndp[c] = max(
                            ndp[c],
                            (c - r) / price + value + best
                        );
                    }
                }
            }

            dp = ndp;
        }

        return *max_element(dp.begin(), dp.end());
    }
};