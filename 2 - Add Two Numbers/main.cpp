
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        int residue = 0;
        while (!(l1 == nullptr && l2 == nullptr && residue == 0)) {
            current->next = new ListNode(0);
            current = current->next;
                
            current->val = residue;
            if (l1 != nullptr) {
                current->val += l1->val;
            }
            if (l2 != nullptr) {
                current->val += l2->val;
            }
            if (current->val >= 10) {
                current->val -= 10;
                residue = 1;
            } else {
                residue = 0;
            }            
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead; // Clean up the dummy head node
        return result;
    }
};