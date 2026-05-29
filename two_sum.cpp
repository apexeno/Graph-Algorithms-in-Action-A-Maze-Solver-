#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        for(int i = 1; i < nums.size(); i++){
            for(int j = 0; j < i; j++){
            if(nums[i] + nums[j] == target){ 
                    return {j, i};
            }
        }
   }
        return {};
    }
};

// Better solution using hash map: O(n) time complexity and O(n) space complexity
// std::vector<int> twoSum(std::vector<int>& nums, int target) {
//     std::unordered_map<int, int> seen;   // value → index

//     for (int i = 0; i < nums.size(); i++) {
//         int complement = target - nums[i];

//         if (seen.count(complement))         // complement seen before?
//             return {seen[complement], i};   // return its index and current index

//         seen[nums[i]] = i;                  // store current value → index
//     }
//     return {};
// }
