class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<int> diff(n);
        long long total = 0;
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            maxDiff = max(maxDiff, diff[i]);
        }

        long long k = (long long)k1 + k2;

        if (total <= k) return 0;

        int left = 0, right = maxDiff;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid) needed += d - mid;
            }

            if (needed <= k) right = mid;
            else left = mid + 1;
        }

        long long remaining = k;

        for (int i = 0; i < n; i++) {
            if (diff[i] > left) {
                remaining -= diff[i] - left;
                diff[i] = left;
            }
        }

        for (int i = 0; i < n && remaining > 0; i++) {
            if (diff[i] == left && left > 0) {
                diff[i]--;
                remaining--;
            }
        }

        long long ans = 0;

        for (int d : diff) {
            ans += 1LL * d * d;
        }

        return ans;
    }
};