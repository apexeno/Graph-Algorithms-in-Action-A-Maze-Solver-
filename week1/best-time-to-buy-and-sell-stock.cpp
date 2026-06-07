#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int i = 0; i < prices.size(); i++) {
            if (prices[i] < minPrice)
                minPrice = prices[i];          
            else if (prices[i] - minPrice > maxProfit)
                maxProfit = prices[i] - minPrice; 
        }
        return maxProfit;
    }
};