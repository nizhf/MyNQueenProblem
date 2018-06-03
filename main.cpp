#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "nqueenproblembasic.h"
#include "gtest/gtest.h"

using namespace std;

TEST(N_Queen_Problem_Test_Trivial, Handle_board) {
    NQueenProblemBasic npb;
    npb.findSolutionBoard();
    EXPECT_EQ(npb.getSolutionCountBoard(), 92);
}

struct dataset {
    dataset(int n, int count) : n(n), count(count){}
    int n;
    int count;
};

class NQueenProblemTest : public ::testing::TestWithParam<struct dataset> {

};

TEST_P(NQueenProblemTest, Handle_Array_Iterative) {
    struct dataset currentData = GetParam();
    NQueenProblemBasic npb(currentData.n);
    npb.findSolutionArrayIter();
    EXPECT_EQ(npb.getSolutionCountArrayIter(), currentData.count);
}

TEST_P(NQueenProblemTest, Handle_Array) {
    struct dataset currentData = GetParam();
    NQueenProblemBasic npb(currentData.n);
    npb.findSolutionArray();
    EXPECT_EQ(npb.getSolutionCountArray(), currentData.count);
}

TEST_P(NQueenProblemTest, Handle_Board) {
    struct dataset currentData = GetParam();
    NQueenProblemBasic npb(currentData.n);
    npb.findSolutionBoard();
    EXPECT_EQ(npb.getSolutionCountBoard(), currentData.count);
}

INSTANTIATE_TEST_CASE_P(Solution_Count, NQueenProblemTest, ::testing::Values(dataset(8, 92), dataset(9, 352), dataset(10, 724), dataset(11, 2680), dataset(12, 14200), dataset(13, 73712), dataset(14, 365596)));

int main(int argc, char **argv)
{
//    NQueenProblemBasic npb(13);
//    npb.findSolutionArray();
//    npb.findSolutionArrayIter();
//    cout << npb.getSolutionCountArray() << "  " << npb.getSolutionCountArrayIter() << endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

