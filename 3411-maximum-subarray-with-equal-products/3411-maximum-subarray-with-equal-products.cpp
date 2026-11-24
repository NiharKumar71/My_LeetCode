class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;
        int primes[4] = {2, 3, 5, 7};

        for (int l = 0; l < n; l++) {
            int sum[4] = {0, 0, 0, 0};
            int mn[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
            int mx[4] = {0, 0, 0, 0};

            for (int r = l; r < n; r++) {
                int x = nums[r];

                for (int i = 0; i < 4; i++) {
                    int cnt = 0;

                    while (x % primes[i] == 0) {
                        cnt++;
                        x /= primes[i];
                    }

                    sum[i] += cnt;
                    mn[i] = min(mn[i], cnt);
                    mx[i] = max(mx[i], cnt);
                }

                bool valid = true;

                for (int i = 0; i < 4; i++) {
                    if (sum[i] != mn[i] + mx[i]) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};