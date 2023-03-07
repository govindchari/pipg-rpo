/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertionsort.c
 *
 * Code generation for function 'insertionsort'
 *
 */

/* Include files */
#include "insertionsort.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertionsort(emxArray_int32_T *x, int xstart, int xend)
{
  int i;
  int k;
  int *x_data;
  x_data = x->data;
  i = xstart + 1;
  for (k = i; k <= xend; k++) {
    int idx;
    int xc;
    xc = x_data[k - 1];
    idx = k - 1;
    while ((idx >= xstart) && (xc < x_data[idx - 1])) {
      x_data[idx] = x_data[idx - 1];
      idx--;
    }
    x_data[idx] = xc;
  }
}

/* End of code generation (insertionsort.c) */
