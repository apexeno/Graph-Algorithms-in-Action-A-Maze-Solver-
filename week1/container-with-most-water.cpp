#include <vector>
#include <algorithm>
#include <climits>




class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;

        while (left < right) {
            int h = std::min(height[left], height[right]);
            int area = h * (right - left);
            maxWater = std::max(maxWater, area);

            
            if (height[left] <= height[right])
                left++;
            else
                right--;
        }

        return maxWater;
    }
};