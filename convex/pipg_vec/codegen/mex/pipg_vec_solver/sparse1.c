/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sparse1.c
 *
 * Code generation for function 'sparse1'
 *
 */

/* Include files */
#include "sparse1.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
real_T sparse_full(const emxArray_real_T *this_d,
                   const emxArray_int32_T *this_colidx)
{
  const real_T *this_d_data;
  real_T y;
  const int32_T *this_colidx_data;
  int32_T cend;
  int32_T i;
  int32_T idx;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  y = 0.0;
  cend = this_colidx_data[1] - 1;
  i = this_colidx_data[0];
  for (idx = i; idx <= cend; idx++) {
    y = this_d_data[0];
  }
  return y;
}

/* End of code generation (sparse1.c) */
