#include<iostream>
#include<vector>
#include<algorithm>


class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
     int Smax= INT_MIN;
     int curr=0;
     for(int i=0; i<nums.size();i++){
        curr = curr + nums[i];
        Smax = std::max(curr,Smax);

        if(curr<0) {
            curr=0;
        }
    }  
    
    return Smax; 
    }
};