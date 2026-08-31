/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
   vector<int> ans = {-1, -1};

if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
    return ans;
}

ListNode* prev = head;
ListNode* curr = head->next;

int pos = 1;

int first = -1;
int last = -1;
int minDist = INT_MAX;

while (curr->next != nullptr) {

    int val = curr->val;

    if ((val > prev->val && val > curr->next->val) ||
        (val < prev->val && val < curr->next->val)) {

        if (first == -1) {
            first = pos;
        } 
        else {
            minDist = min(minDist, pos - last);
        }

        last = pos;
    }

    prev = curr;
    curr = curr->next;
    pos++;
}

if (first == -1 || first == last) {
    return {-1, -1};
}

int maxDist = last - first;

return {minDist, maxDist};     
    }
};
