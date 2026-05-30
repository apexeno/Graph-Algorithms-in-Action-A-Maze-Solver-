#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <set>


class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
      int n = nums.size(); 

      int count = 0;
      
      std::vector<int> prefsum(n + 1, 0);
      prefsum[0]=nums[0];

      for(int i =1; i<n; i++){
        prefsum[i] = prefsum[i-1] + nums[i];   
      }  
      std::unordered_map<int, int> m; 
      for(int j=0; j<n; j++){
        if(prefsum[j]==k) count++;
        
        int val = prefsum[j] - k;
        if(m.count(val)) count += m[val];
        

        m[prefsum[j]]++;
      }
      return count;
    }
};