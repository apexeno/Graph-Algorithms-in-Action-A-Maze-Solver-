#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        // Sort intervals by their start time
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0];
        });

        std::vector<std::vector<int>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            // Get the last merged interval
            auto& last = merged.back();

            // If current interval overlaps with the last merged interval
            if (intervals[i][0] <= last[1]) {
                // Update the end time of last merged interval
                last[1] = std::max(last[1], intervals[i][1]);
            } else {
                // No overlap, simply add the current interval
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};