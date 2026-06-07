#include <iostream>
#include <vector>

int searchInRotatedArray(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
            return mid;

        // Determine which part is sorted
        if (nums[left] <= nums[mid]) { // Left part is sorted
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } else { // Right part is sorted
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    return -1; // Target not found
}

int main() {
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    int index = searchInRotatedArray(nums, target);
    if (index != -1)
        std::cout << "Element found at index: " << index << std::endl;
    else
        std::cout << "Element not found" << std::endl;

    return 0;
}