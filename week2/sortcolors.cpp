#include <vector>
#include <algorithm> // For std::swap

class Solution {
public:
    void sortColors(std::vector<int>& nums) {
    int low = 0, mid = 0, high = (int)nums.size() - 1;

    while (mid <= high) {
            if (nums[mid] == 0) {
                std::swap(nums[low], nums[mid]);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                std::swap(nums[mid], nums[high]);
                high--;
    }
}
    }
};