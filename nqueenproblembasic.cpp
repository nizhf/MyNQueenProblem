#include "nqueenproblembasic.h"

NQueenProblemBasic::NQueenProblemBasic(int n) : countQueen(n) {
    solutionCount = 0;
    for (int i = 0; i < countQueen * countQueen; i++) {
        board.push_back(0);
    }
}

void NQueenProblemBasic::initializeBoard() {
    board.clear();
    for (int i = 0; i < countQueen * countQueen; i++) {
        board.push_back(0);
    }
}

int NQueenProblemBasic::getCountQueen() const {
    return countQueen;
}

void NQueenProblemBasic::setCountQueen(int value) {
    countQueen = value;
    initializeBoard();
}

int NQueenProblemBasic::getSolutionCount() const {
    return solutionCount;
}

void NQueenProblemBasic::printBoard(ostream &os) {
    os << endl;
    for (int y = countQueen - 1; y >= 0; y--) {
        os << y << "  ";
        for (int x = 0; x < countQueen; x++) {
            switch (board[y * countQueen + x]) {
            case 0:
                os << "| ";
                break;
            case 1:
                os << "|O";
                break;
            case -1:
                os << "|X";
                break;
            default:
                break;
            }
        }
        os << "|" << endl;
    }
    os << "   ";
    for (int i = 0; i < countQueen; i++)
        os << " " << i;
    os << endl;
}

void NQueenProblemBasic::setInvalid(int x, int y) {
    if (x < 0 || x >= countQueen || y < 0 || y >= countQueen)
        throw "Invalid Index!";

    int backDiagXBegin = 0;
    int backDiagYBegin = 0;
    int diagXBegin = 0;
    int diagYBegin = 0;

    if (x >= y) {
        backDiagXBegin = x - y;
        backDiagYBegin = 0;
    }
    else {
        backDiagXBegin = 0;
        backDiagYBegin = y - x;
    }

    if (countQueen - x >= y) {
        diagXBegin = x + y;
        diagYBegin = 0;
    }
    else {
        diagXBegin = countQueen - 1;
        diagYBegin = x + y - countQueen + 1;
    }

    for (int i = 0; i < countQueen; i++) {
        //same column
        if (board[i * countQueen + x] == 0)
            board[i * countQueen + x] = -1;
        //same row
        if (board[y * countQueen + i] == 0)
            board[y * countQueen + i] = -1;
        //same diagonal
        if (diagYBegin + i < countQueen && diagXBegin - i >= 0 && board[(diagYBegin + i) * countQueen + diagXBegin - i] == 0)
            board[(diagYBegin + i) * countQueen + diagXBegin - i] = -1;
        //same back diagonal
        if (backDiagYBegin + i < countQueen && backDiagXBegin + i < countQueen && board[(backDiagYBegin + i) * countQueen + backDiagXBegin + i] == 0)
            board[(backDiagYBegin + i) * countQueen + backDiagXBegin + i] = -1;
    }

}

bool NQueenProblemBasic::setQueen(int x, int y) {
    if (x < 0 || x >= countQueen || y < 0 || y >= countQueen)
        throw "Invalid Index!";
    if (board[y * countQueen + x] == 0) {
        board[y * countQueen + x] = 1;
        setInvalid(x, y);
        return true;
    }
    return false;
}

bool NQueenProblemBasic::removeQueen(int x, int y) {
    if (x < 0 || x >= countQueen || y < 0 || y >= countQueen)
        throw "Invalid Index!";
    if (board[y * countQueen + x] == 1) {
        //remove current Queen
        board[y * countQueen + x] = 0;

        //record other Queens
        vector<int> queenX, queenY;
        for (int yy = 0; yy < countQueen; yy++) {
            for (int xx = 0; xx < countQueen; xx++) {
                if (board[yy * countQueen + xx] == 1) {
                    queenX.push_back(xx);
                    queenY.push_back(yy);
                }
            }
        }

        //clear board and place back other queens
        initializeBoard();
        for (int i = 0; i < queenX.size(); i++)
            setQueen(queenX[i], queenY[i]);
        return true;
    }
    return false;
}

void NQueenProblemBasic::findSolution() {
    solutionCount = 0;
    findSolutionRecursive(0);
}

void NQueenProblemBasic::findSolutionRecursive(int y) {
    if (y >= countQueen) {
        solutionCount++;
        return;
    }
    for (int x = 0; x < countQueen; x++) {
        if (board[y * countQueen + x] == 0) {
            setQueen(x, y);
            findSolutionRecursive(y + 1);
            removeQueen(x, y);
        }
    }
}

ostream &operator<<(ostream &os, NQueenProblemBasic &npb) {
    npb.printBoard(os);
    return os;
}
