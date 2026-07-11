// 733. Flood Fill
// Difficulty: Easy
// Topic: Graph - BFS/DFS

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];
        if (originalColor == color) return image;
        dfs(image, sr, sc, originalColor, color);
        return image;
    }

    void dfs(vector<vector<int>>& image, int r, int c, int originalColor, int newColor) {
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() || image[r][c] != originalColor)
            return;
        image[r][c] = newColor;
        dfs(image, r + 1, c, originalColor, newColor);
        dfs(image, r - 1, c, originalColor, newColor);
        dfs(image, r, c + 1, originalColor, newColor);
        dfs(image, r, c - 1, originalColor, newColor);
    }
};
