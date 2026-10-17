
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<pair<int, int>, int>> arr;

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int sum = 0;

            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }

            arr.push_back({{sum, nums[i]}, i});
        }

        sort(arr.begin(), arr.end());

        vector<int> visited(n, 0);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || arr[i].second == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = 1;
                j = arr[j].second;
                cycleSize++;
            }

            if (cycleSize > 1) {
                swaps += cycleSize - 1;
            }
        }

        return swaps;
    }
};
