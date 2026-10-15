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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* curr = head;
        int count = 0;

        while (curr != nullptr && count < k) {
            curr = curr->next;
            count++;
        }

        if (count < k) {
            return head;
        }

        curr = head;
        ListNode* prev = nullptr;
        ListNode* nextNode = nullptr;

        for (int i = 0; i < k; i++) {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        head->next = reverseKGroup(curr, k);

        return prev;
    }
};