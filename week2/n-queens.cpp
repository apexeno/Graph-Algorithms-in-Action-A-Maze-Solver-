#include <vector>
#include <string>

class Solution {
private:
    void solve(int row, int n, std::vector<std::string>& board,
               std::vector<bool>& cols, std::vector<bool>& diag1, std::vector<bool>& diag2,
               std::vector<std::vector<std::string>>& ans) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            // Check if column, major diagonal, or minor diagonal is occupied
            if (cols[col] || diag1[row + col] || diag2[row - col + n]) {
                continue;
            }

            // Place queen
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + n] = true;

            // Recurse to next row
            solve(row + 1, n, board, cols, diag1, diag2, ans);

            // Backtrack
            board[row][col] = '.';
            cols[col] = diag1[row + col] = diag2[row - col + n] = false;
        }
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> board(n, std::string(n, '.'));
        
        std::vector<bool> cols(n, false);
        std::vector<bool> diag1(2 * n, false); // For tracking row + col
        std::vector<bool> diag2(2 * n, false); // For tracking row - col + n

        solve(0, n, board, cols, diag1, diag2, ans);
        return ans;
    }
};