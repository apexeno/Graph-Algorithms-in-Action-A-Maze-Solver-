#include <vector>
#include <algorithm> 



class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end()); // enables early break
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        backtrack(candidates, target, 0, current, result);
        return result;
    }

private:
    void backtrack(std::vector<int>& candidates, int remaining,
                   int start, std::vector<int>& current,
                   std::vector<std::vector<int>>& result) {
        if (remaining == 0) {          // exact sum → valid combination
            result.push_back(current);
            return;
        }
        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > remaining) break;  // sorted → all further too large
            current.push_back(candidates[i]);
            backtrack(candidates, remaining - candidates[i],
                      i,                 // ← i not i+1: allows reuse
                      current, result);
            current.pop_back();         // ← backtrack: undo the choice
        }
    }
};