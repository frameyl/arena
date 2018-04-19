/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* it1 = l1;
        ListNode* it2 = l2;
        int carry = 0;
        ListNode* result = NULL, *it = NULL;
        while (it1 || it2) {
            int value1 = (it1 ? it1->val : 0);
            int value2 = (it2 ? it2->val : 0);

            int res_value = value1+value2+carry;

            carry = res_value / 10;
            ListNode* it_cur = new ListNode(res_value % 10);
            //if (!it_cur) return NULL;

            if (it) {
                it->next = it_cur;
                it = it_cur;
            } else {
                result = it = it_cur;
            }

            if(it1) it1 = it1->next;
            if(it2) it2 = it2->next;
        }
        if (carry) it->next = new ListNode(carry);
        return result;
    };
};
