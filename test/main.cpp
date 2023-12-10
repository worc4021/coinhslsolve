
#include "Matrix.hpp"
#include "ma27.hpp"
#include <iostream>

#include <vector>

int main (int argc, char *argv[])
{
    std::size_t n = 5;
    /* ====== Begin Data ====== */

    // A[0][0] = 2; A[0][1] = 3;
    // A[1][0] = 3;              A[1][2] = 4;              A[1][4] = 6;
    //              A[2][1] = 4; A[2][2] = 1; A[2][3] = 5;
    //                           A[3][2] = 5;
    //              A[4][1] = 6;                           A[4][4] = 1;
    
    CSRMatrix<double> A(n,n);
    A(0,0) = 2; A(0,1) = 4;
    A(1,0) = 3;              A(1,2) = 4;              A(1,4) = 6;
                 A(2,1) = 4; A(2,2) = 1; A(2,3) = 5;
                              A(3,2) = 5;
                                                      A(4,4) = 1;
                 A(4,1) = 6;                           
                
    A(0,1) += 3;

    A.print();

    auto foo = A.toCoordinateFormat();

    std::vector<double> b(n);
    b[0] = 8.; b[1] = 45.; b[2] = 31.; b[3] = 15.; b[4] = 17.;
    std::vector<double> b2(n);
    b2[0] = 1.; b2[1] = 2.; b2[2] = 1.; b2[3] = 2.; b2[4] = 3.;
    
    std::size_t nz = foo.iRow.size();

    std::vector<int> iRow(nz);
    for (auto i = 0; i < nz; i++) {
        iRow[i] = foo.iRow[i];
    }
    std::vector<int> jCol(nz);
    for (auto i = 0; i < nz; i++) {
        jCol[i] = foo.jCol[i];
    }

    ma27 solver(foo.mRows, nz, iRow.data(), jCol.data(), foo.values.data());

    std::cout << "(";
    for (auto i = 0; i < n; i++) {
        std::cout << b[i] << ", ";
    }
    std::cout << ")" << std::endl;
    solver.backsolve(b.data());

    std::cout << "(";
    for (auto i = 0; i < n; i++) {
        std::cout << b[i] << ", ";
    }
    std::cout << ")" << std::endl;

    std::cout << "Got To the end" << std::endl;

    /* ====== Test linSolve ====== */
    // std::cout<<"====== Test linSolve ======"<<std::endl;
	// MA27 linSolveT27(n, nz, A);
    /*
     * Here we set the vector type to be double* and the matrix type to be double**
     * Currently it only accepts dynamically allocated arrays, 
     * becasue of the implementation of MA27 and MA57.
     */
    
    // printSystem(n,n,A,b);
    
    // /*
    //  * Test MA27
    //  */
    
    // linSolveT27.Factorize();
    // linSolveT27.Solve(b);
    // auto sol27_1 = linSolveT27.getSol();
    
    // std::cout<<"Solution for Ax = b using MA27:"<<std::endl;
    // printSol(sol27_1);
    
    
    /*
     * Just the change right hand side; no need to factorize the matirx again.
     */
    // printSystem(n,n,A,b2);
    
    // linSolveT27.Solve(b2);
    // auto sol27_2 = linSolveT27.getSol();
    // std::cout<<"Solution for Ax = b2 using MA27:"<<std::endl;
    // printSol(sol27_2);
    
    /* ====== End linSolve ====== */
    
    
    /* Release memory*/
    // for (int i=0; i<5; i++)
    // {
    //     delete[] A[i];
    // }
    // delete[] A;
    
    return 0;
}
