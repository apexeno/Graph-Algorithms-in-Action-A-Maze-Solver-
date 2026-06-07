#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_set<char> window;
        int left = 0, maxLen = 0;

        for(int right = 0; right < s.size(); right++){
        
            while(window.find(s[right]) != window.end()) {
            window.erase(s[left]);
            left++;
        }

     window.insert(s[right]);

            maxLen = std::max(maxLen, right - left + 1);

     }   
     return maxLen;
    }
};

