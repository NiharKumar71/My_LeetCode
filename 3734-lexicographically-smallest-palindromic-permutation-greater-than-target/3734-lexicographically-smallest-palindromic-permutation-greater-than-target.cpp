class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
       vector<int> cnt(26);

for (char c : s) {
    cnt[c - 'a']++;
}

// Palindrome possible hai ya nahi
int odd = 0;
for (int i = 0; i < 26; i++) {
    odd += cnt[i] % 2;
}

if (odd > 1) {
    return "";
}

// Odd character for middle
int mid = -1;

if (s.size() % 2 == 1) {
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2) {
            mid = i;
            cnt[i]--;
            break;
        }
    }
}

// cnt ab first half ke characters represent karega
string result;
int i = 0;

for (; i < target.size() / 2; i++) {

    int c = target[i] - 'a';

    cnt[c] -= 2;
    result.push_back(target[i]);

    if (cnt[c] < 0) {
        break;
    }
}

// Agar target ka first half exactly ban gaya
if (i == target.size() / 2) {

    if (target.size() % 2) {
        result.push_back('a' + mid);
    }

    string ans = result;

    for (int j = (int)result.size() - 1 - (target.size() % 2);
         j >= 0; j--) {
        ans.push_back(result[j]);
    }

    if (ans > target) {
        return ans;
    }

    if (target.size() % 2) {
        result.pop_back();
    }
}

// Ab peeche jaakar next bigger character try karo
while (!result.empty()) {

    char last = result.back();
    result.pop_back();

    int c = last - 'a';
    cnt[c] += 2;

    for (int j = c + 1; j < 26; j++) {

        if (cnt[j] < 2) {
            continue;
        }

        cnt[j] -= 2;
        result.push_back('a' + j);

        // Remaining characters smallest order mein
        for (int k = 0; k < 26; k++) {
            while (cnt[k] >= 2) {
                cnt[k] -= 2;
                result.push_back('a' + k);
            }
        }

        if (target.size() % 2) {
            result.push_back('a' + mid);
        }

        string ans = result;

        for (int k = (int)result.size() - 1 - (target.size() % 2);
             k >= 0; k--) {
            ans.push_back(result[k]);
        }

        return ans;
    }
}

return ""; 
    }
};