#include <vector>

class Solution {
public:
    bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x == 0) return true;

    int orig = x;  

    int n = 0;
    while (x > 0) {  
        x /= 10;
        n++;
    }

    std::vector<int> A(n);  
    for (int i = 0; i < n; i++) {
        A[i] = orig % 10;  
        orig /= 10;
    }

    for (int j = 0; j < n; j++) {
        if (A[j] != A[n - 1 - j])
            return false;  
    }
    return true;  
}
};