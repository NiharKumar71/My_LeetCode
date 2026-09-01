class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
int n = classroom[0].size();

int sr = 0, sc = 0;
int litterCount = 0;

vector<vector<int>> id(m, vector<int>(n, -1));

for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        if (classroom[i][j] == 'S') {
            sr = i;
            sc = j;
        }
        if (classroom[i][j] == 'L') {
            id[i][j] = litterCount++;
        }
    }
}

int totalMask = 1 << litterCount;

if (litterCount == 0)
    return 0;

struct State {
    int r, c, e, mask;
};

queue<State> q;

vector<vector<vector<vector<bool>>>> vis(
    m,
    vector<vector<vector<bool>>>(
        n,
        vector<vector<bool>>(
            energy + 1,
            vector<bool>(totalMask, false)
        )
    )
);

q.push({sr, sc, energy, 0});
vis[sr][sc][energy][0] = true;

int moves = 0;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

while (!q.empty()) {

    int sz = q.size();

    while (sz--) {

        State cur = q.front();
        q.pop();

        if (cur.mask == totalMask - 1)
            return moves;

        // If energy is 0, we cannot move unless we are on R.
        if (cur.e == 0)
            continue;

        for (int d = 0; d < 4; d++) {

            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];

            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;

            if (classroom[nr][nc] == 'X')
                continue;

            int ne = cur.e - 1;
            int nmask = cur.mask;

            // Collect litter
            if (classroom[nr][nc] == 'L') {
                nmask |= (1 << id[nr][nc]);
            }

            // Reset energy on R
            if (classroom[nr][nc] == 'R') {
                ne = energy;
            }

            if (!vis[nr][nc][ne][nmask]) {
                vis[nr][nc][ne][nmask] = true;
                q.push({nr, nc, ne, nmask});
            }
        }
    }

    moves++;
}

return -1;
    }
};