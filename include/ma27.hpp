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

#include <memory>

template<class T> inline T max(T a, T b) {
    return a > b ? a : b;
}

inline void convert(const int *x, Integer *y, int length) {
    for (auto i = 0; i < length; i++)
        y[i] = x[i];
}

class ma27 {
    public:
        Integer ICNTL[30], INFO[20];
    private:
        Real CNTL[5];
        Integer NZ, N, LIW, NSTEPS, IFLAG, MAXFRT, LA;
        Real OPS;
        std::unique_ptr<Integer[]> IRN, ICN, IW, IW1, IKEEP;
        std::unique_ptr<Real[]> A, W, Avals;

        void symbolicManipulation(void) {
            Integer IFLAG(0);
            Integer* irn_   = IRN.get();
            Integer* icn_   = ICN.get();
            Integer* iw_    = IW.get();
            Integer* iw1_   = IW1.get();
            Integer* ikeep_ = IKEEP.get();

            FC_ma27ad(N, NZ, irn_, icn_, iw_, LIW, ikeep_, iw1_, NSTEPS, IFLAG, ICNTL, CNTL, INFO, OPS);
            
            Integer nrlnec(INFO[5-1]);
            Integer nirnec(INFO[6-1]);

            LIW = 5*nirnec;
            LA = max(NZ, 5*nrlnec);

            IW.reset(new Integer[LIW]);
            A.reset(new Real[LA]);
            IW1.reset(new Integer[NSTEPS]);

        }

        void factoriseMatrix(void){

            Integer* irn_   = IRN.get();
            Integer* icn_   = ICN.get();
            Integer* iw_    = IW.get();
            Integer* ikeep_ = IKEEP.get();
            Integer* iw1_   = IW1.get();
            Real* a_        = A.get();

            for (auto i = 0; i < NZ; i++)
                A[i] = Avals[i];

            FC_ma27bd(N, NZ, irn_, icn_, a_, LA, iw_, LIW, ikeep_ , NSTEPS, MAXFRT, iw1_, ICNTL, CNTL, INFO);

            W.reset(new Real[MAXFRT]);

        }
    public:
        ma27(int n, int nz, const int *irn, const int *jcn, const Real *a) : 
            NZ(nz), N(n), IRN(new Integer[nz]),
            ICN(new Integer[nz]), Avals(new Real[nz]), A(nullptr),
            IW(new Integer[max(2*nz+3*n+1,nz+3*n+1)*2]), 
            LIW(max(2*nz+3*n+1,nz+3*n+1)*2), IKEEP(new Integer[3*n]),
            IW1(new Integer[2*n]), W(nullptr)
        {
            convert(irn, IRN.get(), nz);
            convert(jcn, ICN.get(), nz);
            std::copy(a, a+nz, Avals.get());
            
            FC_ma27id(ICNTL, CNTL);
            
            ICNTL[1-1] = 0;
            ICNTL[2-1] = 0;
            // ICNTL[3-1] = 2;

            symbolicManipulation();
            factoriseMatrix();
        }

        

        void backsolve(Real* rhs) {

            Real* a_      = A.get();
            Integer* iw_  = IW.get();
            Real* w_      = W.get();
            Integer* iw1_ = IW1.get();
            
             FC_ma27cd(N, a_, LA, iw_, LIW, w_, MAXFRT, rhs, iw1_, NSTEPS, ICNTL, INFO);
        }

        void getICNTL(Integer* icntl) const {
            for(auto i = 0; i < 30; i++)
                icntl[i] = ICNTL[i];
        }

        void getInfo(Integer* info) const {
            for (auto i = 0; i < 20; i++)
                info[i] = INFO[i];
        }

        Integer getLA(void) const {
            return LA;
        }
};