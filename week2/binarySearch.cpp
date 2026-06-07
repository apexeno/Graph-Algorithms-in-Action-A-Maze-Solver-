#include <iostream>
#include <vector>

bool binarySearch(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
            return true;
        else if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 5;

    if (binarySearch(nums, target))
        std::cout << "Element found" << std::endl;
    else
        std::cout << "Element not found" << std::endl;

    return 0;
}