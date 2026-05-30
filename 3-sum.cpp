#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <set>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::sort(nums.begin(),nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> result ;

        for(int i=0; i<n; i++){

            if(i>0 && nums[i]==nums[i-1]) continue;
            if(nums[i]>0) break;

            int L=i+1,R=n-1;
             
            while(L<R){
                int sum= nums[i] + nums[R] + nums[L];
                if(sum==0){
                    result.push_back({nums[i] , nums[R] , nums[L]});
                    
                    while(L<R && nums[L]==nums[L+1]) L++;
                    while(L<R && nums[R]==nums[R-1]) R--;
                    L++;R--;
                } else if(sum<0){
                    L++;
                }else{ 
                    R--;
                }
            }
        }
        return result;
    }
};