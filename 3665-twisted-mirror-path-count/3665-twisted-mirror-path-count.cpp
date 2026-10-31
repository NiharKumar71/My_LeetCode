class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> rightDest(m, vector<int>(n, -1));
        vector<vector<int>> downDest(m, vector<int>(n, -1));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 0) continue;

                if (i + 1 < m) {
                    if (grid[i + 1][j] == 0)
                        rightDest[i][j] = (i + 1) * n + j;
                    else
                        rightDest[i][j] = downDest[i + 1][j];
                }

                if (j + 1 < n) {
                    if (grid[i][j + 1] == 0)
                        downDest[i][j] = i * n + j + 1;
                    else
                        downDest[i][j] = rightDest[i][j + 1];
                }
            }
        }

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                if (j + 1 < n) {
                    int dest = grid[i][j + 1] == 0
                        ? i * n + j + 1
                        : rightDest[i][j + 1];

                    if (dest != -1) {
                        int r = dest / n;
                        int c = dest % n;

                        dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                    }
                }

                if (i + 1 < m) {
                    int dest = grid[i + 1][j] == 0
                        ? (i + 1) * n + j
                        : downDest[i + 1][j];

                    if (dest != -1) {
                        int r = dest / n;
                        int c = dest % n;

                        dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};