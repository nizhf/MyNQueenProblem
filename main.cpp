#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "nqueenproblembasic.h"

using namespace std;


int main(int argc, char **argv)
{
    NQueenProblemBasic npb(8);
    npb.findSolution();
    cout << "8 Queen Problem: " << npb.getSolutionCount() << " Solutions total!" << endl;

    npb.setCountQueen(9);
    npb.findSolution();
    cout << "9 Queen Problem: " << npb.getSolutionCount() << " Solutions total!" << endl;

    npb.setCountQueen(10);
    npb.findSolution();
    cout << "10 Queen Problem: " << npb.getSolutionCount() << " Solutions total!" << endl;

    npb.setCountQueen(11);
    npb.findSolution();
    cout << "11 Queen Problem: " << npb.getSolutionCount() << " Solutions total!" << endl;

}

