class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int sx = 0, sy = 0, k = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    sx = i;
                    sy = j;
                }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    k = max(k, grid[i][j] - 'a' + 1);
                }
            }
        }

        int target = (1 << k) - 1;

        vector<vector<vector<bool>>> vis(
            m, vector<vector<bool>>(n, vector<bool>(1 << k, false))
        );

        queue<tuple<int, int, int, int>> q;

        q.push({sx, sy, 0, 0});
        vis[sx][sy][0] = true;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        while (!q.empty()) {
            auto [x, y, mask, dist] = q.front();
            q.pop();

            if (mask == target) return dist;

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                char ch = grid[nx][ny];

                if (ch == '#') continue;

                if (ch >= 'A' && ch <= 'F') {
                    int bit = ch - 'A';
                    if (!(mask & (1 << bit))) continue;
                }

                int newMask = mask;

                if (ch >= 'a' && ch <= 'f') {
                    newMask |= (1 << (ch - 'a'));
                }

                if (!vis[nx][ny][newMask]) {
                    vis[nx][ny][newMask] = true;
                    q.push({nx, ny, newMask, dist + 1});
                }
            }
        }

        return -1;
    }
};