#pragma once
#include "FCMangle.h"
#include <cstddef>

using Integer = int;
using Real = double;

extern "C" {
    void FC_ma27id(     Integer *ICNTL, Real* CNTL);

    void FC_ma27ad(     Integer& N, Integer& NZ, 
                        Integer* IRN, Integer* ICN, 
                        Integer* IW, Integer& LIW, 
                        Integer* IKEEP, Integer* IW1,
                        Integer& NSTEPS, Integer& IFLAG,
                        Integer* ICNTL,Real* CNTL, 
                        Integer* INFO, Real& OPS);
    
    void FC_ma27bd(     Integer& N, Integer& NZ, 
                        Integer* IRN, Integer* ICN, 
                        Real* A, Integer& LA, 
                        Integer* IW, Integer& LIW, 
                        Integer* IKEEP, Integer& NSTEPS, 
                        Integer& MAXFRT, Integer* IW1, 
                        Integer* ICNTL, Real* CNTL, 
                        Integer* INFO);
    

    void  FC_ma27cd(    Integer& N, Real* A, 
                        Integer& LA, Integer* IW, 
                        Integer& LIW, Real* W, 
                        Integer& MAXFRT, Real* RHS,
                        Integer* IW1, Integer& NSTEPS, 
                        Integer* ICNTL, Integer* INFO );

}

#include <vector>
#include <array>

template<class T> inline T max(T a, T b) {
    return a > b ? a : b;
}

inline void convert(const int *x, std::vector<Integer>& y, int length) {
    for (auto i = 0; i < length; i++)
        y[i] = x[i];
}

class ma27 {
    public:
        std::array<Integer, 30> ICNTL;
        std::array<Integer, 20> INFO;
    private:
        std::array<Real, 5> CNTL;
        Integer NZ, N, LIW, NSTEPS, IFLAG, MAXFRT, LA;
        Real OPS;
        std::vector<Integer> IRN, ICN, IW, IW1, IKEEP;
        std::vector<Real> A, W, Avals;

    public:
        ma27(int n, int nz, const int *irn, const int *jcn, const Real *a) : 
            NZ(nz), N(n), IRN(nz),
            ICN(nz), Avals(a, a+nz), A(0),
            IW(max(2*nz+3*n+1,nz+3*n+1)*2), 
            LIW(max(2*nz+3*n+1,nz+3*n+1)*2), IKEEP(3*n),
            IW1(2*n), W(0)
        {
            convert(irn, IRN, nz);
            convert(jcn, ICN, nz);
            
            Integer* icntl_ = ICNTL.data();
            Real* cntl_     = CNTL.data();

            FC_ma27id(icntl_, cntl_);
            
            ICNTL[1-1] = 0;
            ICNTL[2-1] = 0;
            // ICNTL[3-1] = 2;
        }

        Integer symbolicManipulation(void) {
            Integer IFLAG(0);
            Integer* irn_   = IRN.data();
            Integer* icn_   = ICN.data();
            Integer* iw_    = IW.data();
            Integer* iw1_   = IW1.data();
            Integer* ikeep_ = IKEEP.data();
            Integer* icntl_ = ICNTL.data();
            Real* cntl_     = CNTL.data();
            Integer* info_  = INFO.data();


            FC_ma27ad(N, NZ, irn_, icn_, iw_, LIW, ikeep_, iw1_, NSTEPS, IFLAG, icntl_, cntl_, info_, OPS);
            
            Integer nrlnec(INFO[5-1]);
            Integer nirnec(INFO[6-1]);

            LIW = 5*nirnec;
            LA = max(NZ, 5*nrlnec);

            IW.resize(LIW);
            A.resize(LA);
            IW1.resize(NSTEPS);

            std::copy(Avals.begin(), Avals.end(), A.begin());

            return INFO[0];
        }

        Integer factoriseMatrix(void){

            Integer* irn_   = IRN.data();
            Integer* icn_   = ICN.data();
            Integer* iw_    = IW.data();
            Integer* ikeep_ = IKEEP.data();
            Integer* iw1_   = IW1.data();
            Real* a_        = A.data();
            Integer* icntl_ = ICNTL.data();
            Real* cntl_     = CNTL.data();
            Integer* info_  = INFO.data();

            FC_ma27bd(N, NZ, irn_, icn_, a_, LA, iw_, LIW, ikeep_ , NSTEPS, MAXFRT, iw1_, icntl_, cntl_, info_);

            W.resize(MAXFRT);

            return INFO[0];
        }

        Integer backsolve(Real* rhs) {

            Real* a_      = A.data();
            Integer* iw_  = IW.data();
            Real* w_      = W.data();
            Integer* iw1_ = IW1.data();
            Integer* icntl_ = ICNTL.data();
            Integer* info_  = INFO.data();

            FC_ma27cd(N, a_, LA, iw_, LIW, w_, MAXFRT, rhs, iw1_, NSTEPS, icntl_, info_);

            return INFO[0];
        }

        Integer getLA(void) const {
            return LA;
        }
};