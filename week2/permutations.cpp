#include <vector>
#include <algorithm> 

class Solution {
public:
    void getperm(std::vector<int>& nums, int idx, std::vector<std::vector<int>>& ans) {
        if (idx == nums.size()) {
            ans.push_back(nums);
            return;
        }
        for (int i = idx; i < nums.size(); ++i) {
            std::swap(nums[i], nums[idx]);
            getperm(nums, idx + 1, ans);

            // Backtrack to restore the original state
            std::swap(nums[i], nums[idx]);
        }
    }

    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        getperm(nums, 0, ans);
        return ans;
    }
};