
#include "Matrix.hpp"
#include "ma27.hpp"
#include <iostream>

#include <vector>
#include <gtest/gtest.h>

TEST(MA27Test, BuckyTest) {
/* Test generated with matlab:
clearvars

A = bucky;

b(:,1) = 1:size(A,1);

copyvalues(A,'A');
copyvalues(b,'b');
copyvalues(A\b,'x');

function copyvalues(A,basename)
s = '\t{\n';
if isvector(A)
    for i = 1:numel(A)
        s = sprintf('%s\t%s[%2d] = %s;\n', s, basename, i-1, num2str(A(i)));
    end
else
    [iRow,jCol] = find(A);
    for i = 1:nnz(A)
        s = sprintf('%s\t%s(%2d,%2d) = %s;\n',s, basename, iRow(i)-1,jCol(i)-1,num2str(A(iRow(i),jCol(i))));
    end
end
s = sprintf('%s}\n',s);
clipboard("copy",s);
end
*/
    std::size_t n = 60;
    CSRMatrix<double> A(n,n);
    {
	A( 1, 0) = 1;
	A( 4, 0) = 1;
	A( 5, 0) = 1;
	A( 0, 1) = 1;
	A( 2, 1) = 1;
	A(10, 1) = 1;
	A( 1, 2) = 1;
	A( 3, 2) = 1;
	A(15, 2) = 1;
	A( 2, 3) = 1;
	A( 4, 3) = 1;
	A(20, 3) = 1;
	A( 0, 4) = 1;
	A( 3, 4) = 1;
	A(25, 4) = 1;
	A( 0, 5) = 1;
	A( 6, 5) = 1;
	A( 9, 5) = 1;
	A( 5, 6) = 1;
	A( 7, 6) = 1;
	A(29, 6) = 1;
	A( 6, 7) = 1;
	A( 8, 7) = 1;
	A(41, 7) = 1;
	A( 7, 8) = 1;
	A( 9, 8) = 1;
	A(37, 8) = 1;
	A( 5, 9) = 1;
	A( 8, 9) = 1;
	A(11, 9) = 1;
	A( 1,10) = 1;
	A(11,10) = 1;
	A(14,10) = 1;
	A( 9,11) = 1;
	A(10,11) = 1;
	A(12,11) = 1;
	A(11,12) = 1;
	A(13,12) = 1;
	A(36,12) = 1;
	A(12,13) = 1;
	A(14,13) = 1;
	A(32,13) = 1;
	A(10,14) = 1;
	A(13,14) = 1;
	A(16,14) = 1;
	A( 2,15) = 1;
	A(16,15) = 1;
	A(19,15) = 1;
	A(14,16) = 1;
	A(15,16) = 1;
	A(17,16) = 1;
	A(16,17) = 1;
	A(18,17) = 1;
	A(31,17) = 1;
	A(17,18) = 1;
	A(19,18) = 1;
	A(52,18) = 1;
	A(15,19) = 1;
	A(18,19) = 1;
	A(21,19) = 1;
	A( 3,20) = 1;
	A(21,20) = 1;
	A(24,20) = 1;
	A(19,21) = 1;
	A(20,21) = 1;
	A(22,21) = 1;
	A(21,22) = 1;
	A(23,22) = 1;
	A(51,22) = 1;
	A(22,23) = 1;
	A(24,23) = 1;
	A(47,23) = 1;
	A(20,24) = 1;
	A(23,24) = 1;
	A(26,24) = 1;
	A( 4,25) = 1;
	A(26,25) = 1;
	A(29,25) = 1;
	A(24,26) = 1;
	A(25,26) = 1;
	A(27,26) = 1;
	A(26,27) = 1;
	A(28,27) = 1;
	A(46,27) = 1;
	A(27,28) = 1;
	A(29,28) = 1;
	A(42,28) = 1;
	A( 6,29) = 1;
	A(25,29) = 1;
	A(28,29) = 1;
	A(31,30) = 1;
	A(34,30) = 1;
	A(53,30) = 1;
	A(17,31) = 1;
	A(30,31) = 1;
	A(32,31) = 1;
	A(13,32) = 1;
	A(31,32) = 1;
	A(33,32) = 1;
	A(32,33) = 1;
	A(34,33) = 1;
	A(35,33) = 1;
	A(30,34) = 1;
	A(33,34) = 1;
	A(55,34) = 1;
	A(33,35) = 1;
	A(36,35) = 1;
	A(39,35) = 1;
	A(12,36) = 1;
	A(35,36) = 1;
	A(37,36) = 1;
	A( 8,37) = 1;
	A(36,37) = 1;
	A(38,37) = 1;
	A(37,38) = 1;
	A(39,38) = 1;
	A(40,38) = 1;
	A(35,39) = 1;
	A(38,39) = 1;
	A(56,39) = 1;
	A(38,40) = 1;
	A(41,40) = 1;
	A(44,40) = 1;
	A( 7,41) = 1;
	A(40,41) = 1;
	A(42,41) = 1;
	A(28,42) = 1;
	A(41,42) = 1;
	A(43,42) = 1;
	A(42,43) = 1;
	A(44,43) = 1;
	A(45,43) = 1;
	A(40,44) = 1;
	A(43,44) = 1;
	A(57,44) = 1;
	A(43,45) = 1;
	A(46,45) = 1;
	A(49,45) = 1;
	A(27,46) = 1;
	A(45,46) = 1;
	A(47,46) = 1;
	A(23,47) = 1;
	A(46,47) = 1;
	A(48,47) = 1;
	A(47,48) = 1;
	A(49,48) = 1;
	A(50,48) = 1;
	A(45,49) = 1;
	A(48,49) = 1;
	A(58,49) = 1;
	A(48,50) = 1;
	A(51,50) = 1;
	A(54,50) = 1;
	A(22,51) = 1;
	A(50,51) = 1;
	A(52,51) = 1;
	A(18,52) = 1;
	A(51,52) = 1;
	A(53,52) = 1;
	A(30,53) = 1;
	A(52,53) = 1;
	A(54,53) = 1;
	A(50,54) = 1;
	A(53,54) = 1;
	A(59,54) = 1;
	A(34,55) = 1;
	A(56,55) = 1;
	A(59,55) = 1;
	A(39,56) = 1;
	A(55,56) = 1;
	A(57,56) = 1;
	A(44,57) = 1;
	A(56,57) = 1;
	A(58,57) = 1;
	A(49,58) = 1;
	A(57,58) = 1;
	A(59,58) = 1;
	A(54,59) = 1;
	A(55,59) = 1;
	A(58,59) = 1;
    }

    std::vector<double> b(n);
    {
    b[ 0] = 1;
	b[ 1] = 2;
	b[ 2] = 3;
	b[ 3] = 4;
	b[ 4] = 5;
	b[ 5] = 6;
	b[ 6] = 7;
	b[ 7] = 8;
	b[ 8] = 9;
	b[ 9] = 10;
	b[10] = 11;
	b[11] = 12;
	b[12] = 13;
	b[13] = 14;
	b[14] = 15;
	b[15] = 16;
	b[16] = 17;
	b[17] = 18;
	b[18] = 19;
	b[19] = 20;
	b[20] = 21;
	b[21] = 22;
	b[22] = 23;
	b[23] = 24;
	b[24] = 25;
	b[25] = 26;
	b[26] = 27;
	b[27] = 28;
	b[28] = 29;
	b[29] = 30;
	b[30] = 31;
	b[31] = 32;
	b[32] = 33;
	b[33] = 34;
	b[34] = 35;
	b[35] = 36;
	b[36] = 37;
	b[37] = 38;
	b[38] = 39;
	b[39] = 40;
	b[40] = 41;
	b[41] = 42;
	b[42] = 43;
	b[43] = 44;
	b[44] = 45;
	b[45] = 46;
	b[46] = 47;
	b[47] = 48;
	b[48] = 49;
	b[49] = 50;
	b[50] = 51;
	b[51] = 52;
	b[52] = 53;
	b[53] = 54;
	b[54] = 55;
	b[55] = 56;
	b[56] = 57;
	b[57] = 58;
	b[58] = 59;
	b[59] = 60;
    }

    std::vector<double> x(n);
    {
	x[ 0] = 5.9167;
	x[ 1] = 0.91667;
	x[ 2] = 19.6667;
	x[ 3] = 38.4167;
	x[ 4] = 33.4167;
	x[ 5] = -33.3333;
	x[ 6] = 14.4167;
	x[ 7] = 58.4167;
	x[ 8] = 45.1667;
	x[ 9] = -14.3333;
	x[10] = -23.5833;
	x[11] = -1.8333;
	x[12] = 49.9167;
	x[13] = 57.9167;
	x[14] = 11.9167;
	x[15] = -36.3333;
	x[16] = -19.3333;
	x[17] = 41.4167;
	x[18] = 71.9167;
	x[19] = 15.6667;
	x[20] = -49.0833;
	x[21] = -15.5833;
	x[22] = 55.4167;
	x[23] = 63.4167;
	x[24] = -1.8333;
	x[25] = -39.3333;
	x[26] = 10.6667;
	x[27] = 68.1667;
	x[28] = 54.9167;
	x[29] = -18.0833;
	x[30] = 38.4167;
	x[31] = -34.5833;
	x[32] = -47.8333;
	x[33] = 9.6667;
	x[34] = 59.6667;
	x[35] = 22.1667;
	x[36] = -43.0833;
	x[37] = -35.0833;
	x[38] = 35.9167;
	x[39] = 69.4167;
	x[40] = 4.6667;
	x[41] = -51.5833;
	x[42] = -21.0833;
	x[43] = 39.6667;
	x[44] = 56.6667;
	x[45] = 8.4167;
	x[46] = -37.5833;
	x[47] = -29.5833;
	x[48] = 22.1667;
	x[49] = 43.9167;
	x[50] = 34.6667;
	x[51] = -24.8333;
	x[52] = -38.0833;
	x[53] = 5.9167;
	x[54] = 53.6667;
	x[55] = -13.0833;
	x[56] = -18.0833;
	x[57] = 0.66667;
	x[58] = 19.4167;
	x[59] = 14.4167;
    }

    CoordinateFormat<double> coo = A.toCoordinateFormat();

    // Have to increase the indices by 1 to match the fortran indexing
    std::vector<int> iRow(A.nnz());
    for (auto i = 0; i < A.nnz(); i++) {
        iRow[i] = (coo.iRow[i]+1);
    }
    std::vector<int> jCol(A.nnz());
    for (auto i = 0; i < A.nnz(); i++) {
        jCol[i] = (coo.jCol[i]+1);
    }
    ma27 solver(coo.mRows, A.nnz(), iRow.data(), jCol.data(), coo.values.data());

    EXPECT_EQ(solver.symbolicManipulation(), 0);
    EXPECT_EQ(solver.factoriseMatrix(), 0);
    
    EXPECT_EQ(solver.backsolve(b.data()), 0);

    for (auto i = 0; i < n; i++) {
        EXPECT_LT(std::abs(b[i]- x[i]), 1e-4);
    }

}


TEST(MA27Test, HSLDocsTest) {
    // Test from the HSL Docs https://www.hsl.rl.ac.uk/archive-specs/ma27.pdf

    std::size_t m = 5;
    std::size_t n = 7;
    CSRMatrix<double> A(m,n);
    A(1-1, 1-1) = 2.0;
    A(1-1, 2-1) = 3.0;
    A(2-1, 3-1) = 4.0;
    A(2-1, 5-1) = 6.0;
    A(3-1, 3-1) = 1.0;
    A(3-1, 4-1) = 5.0;
    A(5-1, 5-1) = 1.0;
    std::vector<double> b({8. ,45. ,31. ,15. ,17.});
    std::vector<double> b2({8. ,45. ,31. ,15. ,17.});

    CoordinateFormat<double> coo = A.toCoordinateFormat();
    
    // Have to increase the indices by 1 to match the fortran indexing
    std::vector<int> iRow(A.nnz());
    for (auto i = 0; i < A.nnz(); i++) {
        iRow[i] = (coo.iRow[i]+1);
    }
    std::vector<int> jCol(A.nnz());
    for (auto i = 0; i < A.nnz(); i++) {
        jCol[i] = (coo.jCol[i]+1);
    }
    ma27 solver(coo.mRows, A.nnz(), iRow.data(), jCol.data(), coo.values.data());

    EXPECT_EQ(solver.symbolicManipulation(), 0);
    EXPECT_EQ(solver.factoriseMatrix(), 0);
    
    EXPECT_EQ(solver.backsolve(b.data()), 0);

    std::vector<int> rows({1,1,2,2,3,3,5});
    std::vector<int> cols({1,2,3,5,3,4,5});
    std::vector<double> vals({2,3,4,6,1,5,1});

    ma27 hsl(m, 7, rows.data(), cols.data(), vals.data());
    EXPECT_EQ(hsl.symbolicManipulation(), 0);
    EXPECT_EQ(hsl.factoriseMatrix(), 0);
    EXPECT_EQ(hsl.backsolve(b2.data()), 0);

    for (auto i = 0; i < m; i++) {
        EXPECT_LT(std::abs(b.at(i) - b2.at(i)), 1e-4);
    }

}
