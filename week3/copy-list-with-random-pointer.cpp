class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        Node* newHead = head->next;
        curr = head;
        while (curr) {
            Node* copy = curr->next;
            curr->next = copy->next;
            copy->next = copy->next ? copy->next->next : nullptr;
            curr = curr->next;
        }

        return newHead;
    }
};
