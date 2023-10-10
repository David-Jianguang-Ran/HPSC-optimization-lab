//  ================================================================================
//  ||                                                                            ||
//  ||              esPIC                                                         ||
//  ||              ------------------------------------------------------        ||
//  ||              E L E C T R O S T I C   P A R T I C L E - I N - C E L L       ||
//  ||                                                                            ||
//  ||              D E M O N S T R A T I O N   C O D E                           ||
//  ||              ------------------------------------------------------        ||
//  ||                                                                            ||
//  ||       Developed by: Scott R. Runnels, Ph.D.                                ||
//  ||                     University of Colorado Boulder                         ||
//  ||                                                                            ||
//  ||                For: CU Boulder CSCI 4576/5576 and associated labs          ||
//  ||                                                                            ||
//  ||           Copyright 2020 Scott Runnels                                     ||
//  ||                                                                            ||
//  ||                     Not for distribution or use outside of the             ||
//  ||                     this course.                                           ||
//  ||                                                                            ||
//  ================================================================================

#include "ContiguousArray.h"

  //  ==
  //  ||
  //  ||  Perform Jacobiiterations on nField X nField linear
  //  ||  system:  A*Solution = RHS
  //  ||
  //  ==

void GS_or_Jacobi(int max_iter , VD RHS, VD &Solution , mpiInfo &myMPI , int GSorJacobi, int &finalIterCount )
  {
    int converged, it_converged;
    int iter = 0;
    double newval;
    double cur_delta = 0.;
    double max_delta = 0.;
    double tol;

    MPI_Status status;
    int        tag = 0;
    int        err;
    int        global_converged;
    int        zero = 0;
    int        one  = 1;
    

    VD SolutionNew; SolutionNew.resize(Solution.size());

    //    rLOOP Solution[r] = 0.;
    tol       = 1.e-04;
    
    // ====================================================
    // Begin Iterations
    // ====================================================
    
    converged = 0;


    // OPTIMIZATION HERE
    // cache inverse of diag in the unused space in the beginning of each row
    rLOOP Acoef.at(r, 0) = 1.0 / Acoef.at(r, 1);


    while ( converged == 0 )
      {
	// ----------------------------------------------
	// (1) Parallel communication on PE Boundaries
	// ----------------------------------------------
	
	myMPI.ExchangeBoundaryInfo(Solution,b);

	// ----------------------------------------------
	// (2) Convergence
	// ----------------------------------------------
	
	if ( ++iter > max_iter )
	  {
	    finalIterCount = iter;
	    return;
	  }

	max_delta    = 0.;  it_converged = 1;

	// ----------------------------------------------
	// (3) One Jacobi Iteration
	// ----------------------------------------------



	rLOOP
	  {

	    
	    // (3.1) Compute new guess for row r

	    newval = b[r];
        // OPTIMIZATION using ContiguousArray class
        double* a_addr = Acoef.get_addr(r, 2);
        int* j_addr = Jcoef.get_addr(r, 2);
        for (int c = 2; c <= bandwidth; ++c) {
            newval -= *a_addr * Solution[*j_addr];
            ++a_addr;
            ++j_addr;
        }
        newval *= *(a_addr - bandwidth - 1);

	    // (3.2) Convergence check

	    cur_delta  = fabs(Solution[r] - newval);

	    if ( cur_delta > tol ) it_converged = 0;

	    // (3.3) Record new value in solution

	    SolutionNew[r]       = newval;

	    if ( GSorJacobi == 1 ) Solution[r] = newval;  // Gauss-Seidel, update Solution as we go
	      
	  }

      // OPTIMIZATION HERE
	// rLOOP Solution[r] = SolutionNew[r];
    // instead of vector to vector copy, do swap or something
    Solution.swap(SolutionNew);

	// ----------------------------------------------
	// (4) Make note of the convergence state
	// ----------------------------------------------
	
	converged = it_converged;

	// ----------------------------------------------
	// (5) Gather convergence information from PEs
	// ----------------------------------------------

	int root = 0;
    // OPTIMIZATION HERE
    // using one MPI all reduce call instead of reduce and bcast
	err = MPI_Allreduce( &converged       , &global_converged, one , MPI_INT , MPI_MIN , MPI_COMM_WORLD );
	converged = global_converged;

	if ( converged == 1 )
	  {
	    finalIterCount = iter;
	    return;
	  }
	
      }

  }

