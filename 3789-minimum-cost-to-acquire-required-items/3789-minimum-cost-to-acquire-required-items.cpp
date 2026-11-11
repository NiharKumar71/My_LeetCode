class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long a = need1;
        long long b = need2;

        long long ans1 = a * cost1 + b * cost2;

        long long common = min(a, b);
        long long ans2 = common * costBoth
                       + (a - common) * cost1
                       + (b - common) * cost2;

        long long extra = max(a, b);
        long long ans3 = extra * costBoth;

        return min({ans1, ans2, ans3});
    }
};