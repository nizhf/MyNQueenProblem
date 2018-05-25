#ifndef NQUEENPROBLEMBASIC_H
#define NQUEENPROBLEMBASIC_H

#include <vector>
#include <iostream>

using namespace std;

class NQueenProblemBasic
{
public:
    explicit NQueenProblemBasic(int n = 8);

    void initializeBoard();
    int getCountQueen() const;
    void setCountQueen(int value);
    int getSolutionCount() const;
    void printBoard(ostream &os = cout);

    void setInvalid(int x, int y);
    bool setQueen(int x, int y);
    bool removeQueen(int x, int y);

    void findSolution();

    friend ostream &operator<<(ostream &os, NQueenProblemBasic &npb);

protected:
    void findSolutionRecursive(int y);

private:
    int countQueen;
    int solutionCount;

    /* board
     *
     * y7 56 57 58 59 60 61 62 63
     * y6 48 49 50 51 52 53 54 55
     * y5 40 41 42 43 44 45 46 47
     * y4 32 33 34 35 36 37 38 39
     * y3 24 25 26 27 28 29 30 31
     * y2 16 17 18 19 20 21 22 23
     * y1  8  9 10 11 12 13 14 15
     * y0  0  1  2  3  4  5  6  7
     *    x0 x1 x2 x3 x4 x5 x6 x7
     *
     * at(y * countQueen + x)
     * 0 - empty
     * 1 - queen
     * -1 - invalid
     */
    vector<char> board;

};

#endif // NQUEENPROBLEMBASIC_H