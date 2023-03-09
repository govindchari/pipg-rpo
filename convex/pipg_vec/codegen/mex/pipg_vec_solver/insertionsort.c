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
#include "eml_int_forloop_overflow_check.h"
#include "pipg_vec_solver_data.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo ub_emlrtRSI = {
    18,              /* lineNo */
    "insertionsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "insertionsort.m" /* pathName */
};

/* Function Definitions */
void insertionsort(const emlrtStack *sp, emxArray_int32_T *x, int32_T xstart,
                   int32_T xend)
{
  emlrtStack b_st;
  emlrtStack st;
  int32_T a;
  int32_T k;
  int32_T *x_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  x_data = x->data;
  a = xstart + 1;
  st.site = &ub_emlrtRSI;
  if ((xstart + 1 <= xend) && (xend > 2147483646)) {
    b_st.site = &cb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  for (k = a; k <= xend; k++) {
    int32_T idx;
    int32_T xc;
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
