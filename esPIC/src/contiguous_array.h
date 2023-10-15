//
// Created by dran on 10/14/23.
//

#ifndef HPSC_OPTIMIZATION_LAB_CONTIGUOUS_ARRAY_H
#define HPSC_OPTIMIZATION_LAB_CONTIGUOUS_ARRAY_H


// -------------------------------------------
// Double 2D Array
// -------------------------------------------

double  * * arrayDouble(int nRows,int nCols)
{
    double *myArray;
    myArray = new double [ nRows * nCols ];

    // Create a pointer that points to the beginning of each new row

    double * * myArray_ptr;
    myArray_ptr = new double * [nRows];

    int count = 0;

    for ( int row = 0 ; row < nRows ; ++ row )
    {
        myArray_ptr[row] = &myArray[ count*nCols ];
        ++count;
    }

    for ( int i = 0 ; i < nRows ; ++i )  for ( int j = 0 ; j < nCols ; ++j ) myArray_ptr[i][j] = 10.;

    // Return that pointer

    return myArray_ptr;

}

// -------------------------------------------
// Integer 2D Array
// -------------------------------------------

int  * * arrayInt(int nRows,int nCols)
{
    int *myArray;
    myArray = new int [ nRows * nCols ];

    // Create a pointer that points to the beginning of each new row

    int * * myArray_ptr;
    myArray_ptr = new int * [nRows];

    int count = 0;

    for ( int row = 0 ; row < nRows ; ++ row )
    {
        myArray_ptr[row] = &myArray[ count*nCols ];
        ++count;
    }

    for ( int i = 0 ; i < nRows ; ++i )  for ( int j = 0 ; j < nCols ; ++j ) myArray_ptr[i][j] = 10.;

    // Return that pointer

    return myArray_ptr;

}


#endif //HPSC_OPTIMIZATION_LAB_CONTIGUOUS_ARRAY_H
