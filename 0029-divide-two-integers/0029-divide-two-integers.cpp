class Solution {
public:
    int divide(int dividend, int divisor) {
        // Overflow case
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long a = dividend;
        long long b = divisor;

        // Result ka sign
        bool negative = (a < 0) ^ (b < 0);

        // Positive values
        a = abs(a);
        b = abs(b);

        long long ans = 0;

        // Binary division
        while (a >= b) {
            long long temp = b;
            long long multiple = 1;

            while (a >= (temp << 1)) {
                temp <<= 1;
                multiple <<= 1;
            }

            a -= temp;
            ans += multiple;
        }

        if (negative)
            ans = -ans;

        return (int)ans;
    }
};