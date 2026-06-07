#include <vector>
#include <iostream>

class Solution {
public:
    void solve(const std::vector<int>& nums, std::vector<int>& current,
               int i, std::vector<std::vector<int>>& allsubsets) {

    if (i == nums.size()) {
        allsubsets.push_back(current);                 
        return;
    }

        // Include the current element
        current.push_back(nums[i]);
    solve(nums, current, i + 1, allsubsets);

        // Skip the current element
        current.pop_back();
    solve(nums, current, i + 1, allsubsets);
}

    std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
        std::vector<std::vector<int>> allsubsets;
    allsubsets.reserve(1 << nums.size());              
        std::vector<int> current;
    current.reserve(nums.size());                      

    solve(nums, current, 0, allsubsets);
    return allsubsets;
}
};

int main() {
    Solution sol;
    std::vector<int> nums = {1, 2, 3};

    auto subsets = sol.subsets(nums);

    for (const auto& subset : subsets) {
        std::cout << "[";
        for (size_t i = 0; i < subset.size(); ++i) {
            std::cout << subset[i];
            if (i != subset.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}
