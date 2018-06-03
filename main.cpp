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

TEST(N_Queen_Problem_Test_14, Handle_bit) {
    NQueenProblemBasic npb(14);
    npb.findSolutionBit();
    EXPECT_EQ(npb.getSolutionCountBit(), 365596);
}

struct dataset {
    dataset(int n, int count) : n(n), count(count){}
    int n;
    int count;
};

class NQueenProblemTest : public ::testing::TestWithParam<struct dataset> {

};

TEST_P(NQueenProblemTest, Handle_Bit) {
    struct dataset currentData = GetParam();
    NQueenProblemBasic npb(currentData.n);
    npb.findSolutionBit();
    EXPECT_EQ(npb.getSolutionCountBit(), currentData.count);
}

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

//INSTANTIATE_TEST_CASE_P(Solution_Count, NQueenProblemTest, ::testing::Values(dataset(8, 92), dataset(9, 352), dataset(10, 724), dataset(11, 2680), dataset(12, 14200), dataset(13, 73712), dataset(14, 365596)));
INSTANTIATE_TEST_CASE_P(Solution_Count, NQueenProblemTest, ::testing::Values(dataset(8, 92), dataset(9, 352), dataset(10, 724), dataset(11, 2680), dataset(12, 14200)));

int main(int argc, char **argv)
{
    NQueenProblemBasic npb;
    for (int i = 8; i <= 14; i++) {
        npb.setCountQueen(i);
        npb.findSolutionBit();
        cout << i << " Queen Problem: " << npb.getSolutionCountBit() << " solutions!" << endl;
    }
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

