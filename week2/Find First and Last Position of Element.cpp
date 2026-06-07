#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) {
        return {firstSum(nums, target), lastSum(nums, target)};
    }

private:
    int firstSum(const std::vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, result = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                result = mid;
                high = mid - 1; // Continue to search in the left half
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
    }

        return result;
    }
    int lastSum(const std::vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, result = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                result = mid;
                low = mid + 1; // Continue to search in the right half
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
    }

        return result;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {5,7,7,8,8,10};
    int target = 8;

    std::vector<int> result = sol.searchRange(nums, target);

    std::cout << "First position: " << result[0] << ", Last position: " << result[1] << std::endl;

    return 0;
}
