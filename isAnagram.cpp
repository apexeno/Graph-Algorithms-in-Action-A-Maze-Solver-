#include <iostream>
#include <string>
#include <vector>


class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        if (s.length() != t.length())
            return false;

        std::vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        for (char c : t)
            freq[c - 'a']--;

        for(int i=0;i<26;i++){
            if(freq[i]!=0)
                return false;
        }

        return true;
    }
};