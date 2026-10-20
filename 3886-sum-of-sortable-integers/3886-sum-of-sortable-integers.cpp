
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;
            int prevMax = -1;

            for (int start = 0; start < n; start += k) {
                int mn = nums[start];
                int mx = nums[start];
                int descents = 0;

                for (int j = 0; j < k; j++) {
                    int idx = start + j;
                    mn = min(mn, nums[idx]);
                    mx = max(mx, nums[idx]);

                    int nextIdx = start + (j + 1) % k;
                    if (nums[idx] > nums[nextIdx]) {
                        descents++;
                    }
                }

                if (descents > 1 || (start > 0 && prevMax > mn)) {
                    ok = false;
                    break;
                }

                prevMax = mx;
            }

            if (ok) ans += k;
        }

        return ans;
    }
};
