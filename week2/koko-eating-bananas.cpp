#include <vector>
#include <algorithm> 


class Solution {
public:
    int minEatingSpeed(std::vector<int>& piles, int h) {
        int lo = 1, hi = *std::max_element(piles.begin(), piles.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canFinish(piles, mid, h))
                hi = mid;      // mid works, try smaller
            else
                lo = mid + 1;  // mid too slow, need faster
        }
        return lo;
    }

private:
    bool canFinish(std::vector<int>& piles, int k, int h) {
        long long hours = 0;
        for (int p : piles)
            hours += (p + k - 1) / k;  // ceil(p/k)
        return hours <= h;
    }
};