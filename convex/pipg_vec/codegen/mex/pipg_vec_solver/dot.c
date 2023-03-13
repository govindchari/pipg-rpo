/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dot.c
 *
 * Code generation for function 'dot'
 *
 */

/* Include files */
#include "dot.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>

/* Function Definitions */
real_T dot(const emxArray_real_T *a)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  real_T b_data[3];
  const real_T *a_data;
  real_T c;
  a_data = a->data;
  b_data[0] = 0.0;
  b_data[1] = 1.0;
  b_data[2] = 0.0;
  if (a->size[0] < 1) {
    c = 0.0;
  } else {
    n_t = (ptrdiff_t)a->size[0];
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    c = ddot(&n_t, (real_T *)&a_data[0], &incx_t, &b_data[0], &incy_t);
  }
  return c;
}

/* End of code generation (dot.c) */
