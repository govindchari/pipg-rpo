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
#include "eml_int_forloop_overflow_check.h"
#include "pipg_vec_solver_data.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo bb_emlrtRSI = {
    275,           /* lineNo */
    "sparse/full", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

/* Function Definitions */
real_T sparse_full(const emlrtStack *sp, const emxArray_real_T *this_d,
                   const emxArray_int32_T *this_colidx)
{
  emlrtStack b_st;
  emlrtStack st;
  const real_T *this_d_data;
  real_T y;
  const int32_T *this_colidx_data;
  int32_T a;
  int32_T cend;
  int32_T idx;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  y = 0.0;
  cend = this_colidx_data[1] - 1;
  a = this_colidx_data[0];
  st.site = &bb_emlrtRSI;
  if ((this_colidx_data[0] <= this_colidx_data[1] - 1) &&
      (this_colidx_data[1] - 1 > 2147483646)) {
    b_st.site = &cb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  for (idx = a; idx <= cend; idx++) {
    y = this_d_data[0];
  }
  return y;
}

/* End of code generation (sparse1.c) */
