
//
// Created by arunm619 on 24/9/18.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


/**
* Sudoku Solver class can solve 9 x 9 board which is solvable
**/
class SudokuSolver {
private:

    vector<vector<char>> board;

    /**
     *   \brief isSolvable method.
     *
     *   Checks if a 9 x 9 board is solvable or not.
     *
     *   \param none.
     *   \return A bool.
     *   true means is solvable, false otherwise.
     *
     **/
    bool isSolvable() {
        short rows[9]{};
        short cols[9]{};
        short grids[9]{};

        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == '?')
                    continue;

                int current = 1 << (board[row][col] - '1');

                if (rows[row] & current) return false;
                if (cols[col] & current) return false;
                if (grids[row / 3 * 3 + col / 3] & current) return false;

                rows[row] |= current;
                cols[col] |= current;
                grids[row / 3 * 3 + col / 3] |= current;
            }
        }

        return true;
    }

    /**
   *   \brief solve method.
   *
   *   solves a solvable 9 x 9 board
   *   using backtracking
   *
   *   \param @board.
   *   \return bool.
   *   if solvable, solves it in place and returns true.
   *   no change, otherwise and returns false
   *
   **/

    bool solveHelper(vector<vector<char>> &board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == '?') {
                    for (char set = '1'; set <= '9'; set++) {
                        if (isValid(board, row, col, set)) {
                            board[row][col] = set;

                            if (solveHelper(board)) return true;

                            board[row][col] = '?';
                        }
                    }
                    return false;
                }

            }
        }
        return true;
    }

public:

    SudokuSolver() = default;

    /**
     *   \brief prettyPrint method.
     *
     *   Prints  a 9 x 9 board.
     *
     *   \param none.
     *   \return void.
     *
     **/

    void prettyPrint(int callFrom, const string &time = "") {

        switch (callFrom) {
            case 1:
                cout << " Board Loaded Successfully";
                break;
            case 2:
                cout << " Board Solved in " << time << " microseconds";
                break;
            default:
                break;
        }

        endl(cout);

        for (auto row : board) {
            for (auto ele : row) {
                cout << " " << ele << " ";
            }
            endl(cout);
        }

        endl(cout);
    }

    /**
     *   \brief chooseBoard method.
     *
     *   selects the file to be opened
     *   and loads the numbers on to the board.
     *
     *   \param string filename.
     *   \return void.
     *
     *
     **/

    void chooseBoard(const string &level) {

        ifstream puzzleFile(level);
        vector<char> temp;

        if (puzzleFile.is_open()) {
            cout << " Opening file \"" << level << "\"" << endl;
            string line;
            //cout << line << endl;
            while (getline(puzzleFile, line)) {
                temp.clear();
                istringstream iss(line);
                string current;
                while (getline(iss, current, ' ')) {
                    temp.push_back(current[0]);
                }

                board.push_back(temp);
            }

            prettyPrint(1);

        } else {
            cout << " Error Opening the file " << level << endl;
        }
        puzzleFile.close();

    }

    /**
 *   \brief solve method.
 *
 *   public method to call solveHelper Method
 *
 *   \param none.
 *   \return void.
 *   if solvable, solves it in place.
 *   no change, otherwise
 *
 **/

    void solve() {
        if (!isSolvable()) {
            cout << " The current puzzle is not solvable " << endl;
            return;
        }

        // Get starting timepoint
        auto start = high_resolution_clock::now();

        solveHelper(board);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        string units = to_string(duration.count());

        prettyPrint(2, units);
    }

    /**
 *   \brief isValid method.
 *
 *   Checks if a 9 x 9 board is valid or not
 *   after inserting a number.
 *   \param @board, @row,@col,@set.
 *   \return A bool.
 *   returns true if solvable, false otherwise.
 *
 *  board - 9 x 9 board
 *  set - new number inserted.
 *  row - row number
 *  col - column number
 **/

    bool isValid(const vector<vector<char>> &board, int row, int col, char set) {
        for (int r = 0; r < 9; r++) {
            if (board[r][col] == set) return false;
        }

        for (int c = 0; c < 9; c++) {
            if (board[row][c] == set) return false;
        }

        for (int r = row / 3 * 3; r < row / 3 + 1 * 3; r++) {
            for (int c = col / 3 * 3; c < col / 3 + 1 * 3; c++) {
                if (board[r][c] == set) return false;
            }
        }

        return true;
    }

};
