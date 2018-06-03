#include "nqueenproblembasic.h"

NQueenProblemBasic::NQueenProblemBasic(int n) : countQueen(n) {
    solutionCountBoard = 0;
    solutionCountArray = 0;
    solutionCountArrayIter = 0;
    solutionCountBit = 0;
    for (int i = 0; i < countQueen * countQueen; i++) {
        board.push_back(0);
    }
    queenArray = unique_ptr<int[]>(new int[countQueen]);
    queenArrayIter = unique_ptr<int[]>(new int[countQueen]);
    for (int i = 0; i < countQueen; i++) {
        queenArray[i] = -100;
        queenArrayIter[i] = -100;
    }

}

void NQueenProblemBasic::initializeBoard() {
    board.clear();
    for (int i = 0; i < countQueen * countQueen; i++) {
        board.push_back(0);
    }
    queenArray = unique_ptr<int[]>(new int[countQueen]);
    queenArrayIter = unique_ptr<int[]>(new int[countQueen]);
    for (int i = 0; i < countQueen; i++) {
        queenArray[i] = -100;
        queenArrayIter[i] = -100;
    }
}

int NQueenProblemBasic::getCountQueen() const {
    return countQueen;
}

void NQueenProblemBasic::setCountQueen(int value) {
    countQueen = value;
    initializeBoard();
}

int NQueenProblemBasic::getSolutionCountBoard() const {
    return solutionCountBoard;
}

int NQueenProblemBasic::getSolutionCountArray() const {
    return solutionCountArray;
}

int NQueenProblemBasic::getSolutionCountArrayIter() const {
    return solutionCountArrayIter;
}

int NQueenProblemBasic::getSolutionCountBit() const {
    return solutionCountBit;
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

void NQueenProblemBasic::findSolutionBoard() {
    solutionCountBoard = 0;
    findSolutionBoardRecursive(0);
}

void NQueenProblemBasic::findSolutionBoardRecursive(int y) {
    if (y >= countQueen) {
        solutionCountBoard++;
        return;
    }
    for (int x = 0; x < countQueen; x++) {
        if (board[y * countQueen + x] == 0) {
            setQueen(x, y);
            findSolutionBoardRecursive(y + 1);
            removeQueen(x, y);
        }
    }
}

void NQueenProblemBasic::findSolutionArray() {
    solutionCountArray = 0;
    findSolutionArrayRecursive(0);
}

void NQueenProblemBasic::findSolutionArrayRecursive(int y) {
    if (y >= countQueen) {
        solutionCountArray++;
        return;
    }
    for (int x = 0; x < countQueen; x++) {
        bool valid = true;
        for (int i = 0; i < y; i++) {
            if (x == queenArray[i] || (x - queenArray[i]) == y - i || (x - queenArray[i]) == i - y) {
                valid = false;
                break;
            }
        }
        if (valid) {
            queenArray[y] = x;
            findSolutionArrayRecursive(y + 1);
        }
    }
}

void NQueenProblemBasic::findSolutionArrayIter() {
    solutionCountArrayIter = 0;
//    int y = 0, x = 0;
//    while (y < countQueen) {
//        while (x < countQueen) {
//            //valid position for queen?
//            bool valid = true;
//            for (int i = 0; i < y; i++) {
//                if (x == queenArrayIter[i] || (x - queenArrayIter[i]) == y - i || (x - queenArrayIter[i]) == i - y) {
//                    valid = false;
//                    break;
//                }
//            }
//
//            //if valid, goto next row
//            if (valid) {
//                queenArrayIter[y] = x;
//                x = 0;
//                break;
//            }
//            //if invalid, goto next column
//            else {
//                x++;
//            }
//        }
//        //no valid position found at this row
//        if (queenArrayIter[y] < 0) {
//            //search completed
//            if (y <= 0) {
//                break;
//            }
//            //goto the last row, set queen in the next column
//            else {
//                y--;
//                x = queenArrayIter[y] + 1;
//                queenArrayIter[y] = -100;
//                continue;
//            }
//        }
//        //reach the last row, solution found, set queen in the next column
//        if (y == countQueen - 1) {
//            solutionCountArrayIter++;
//            x = queenArrayIter[y] + 1;
//            queenArrayIter[y] = -100;
//            continue;
//        }
//        y++;
//    }

    int y = 0;
    queenArrayIter[y] = 0;
    while (y >= 0) {
        if (y < countQueen && queenArrayIter[y] < countQueen) {
            //valid position for queen?
            bool valid = true;
            for (int i = 0; i < y; i++) {
                if (queenArrayIter[y] == queenArrayIter[i] || (queenArrayIter[y] - queenArrayIter[i]) == y - i || (queenArrayIter[y] - queenArrayIter[i]) == i - y) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                y++;
                queenArrayIter[y] = 0;
            }
            else {
                queenArrayIter[y]++;
            }
        }
        else {
            if (y >= countQueen) {
                solutionCountArrayIter++;
            }
            y--;
            queenArrayIter[y]++;
        }
    }
}

void NQueenProblemBasic::findSolutionBit() {
    solutionCountBit = 0;
}



ostream &operator<<(ostream &os, NQueenProblemBasic &npb) {
    npb.printBoard(os);
    return os;
}
