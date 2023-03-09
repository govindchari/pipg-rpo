/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sparse.c
 *
 * Code generation for function 'sparse'
 *
 */

/* Include files */
#include "sparse.h"
#include "pipg_vec_solver_emxutil.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo ab_emlrtRSI = {
    13,       /* lineNo */
    "sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/sparfun/sparse.m" /* pathName
                                                                        */
};

static emlrtRTEInfo y_emlrtRTEI = {
    13,       /* lineNo */
    1,        /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/sparfun/sparse.m" /* pName
                                                                        */
};

/* Function Definitions */
void sparse(const emlrtStack *sp, real_T varargin_1, emxArray_real_T *y_d,
            emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx)
{
  emlrtStack st;
  real_T *y_d_data;
  int32_T i;
  int32_T *y_colidx_data;
  int32_T *y_rowidx_data;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &ab_emlrtRSI;
  i = y_d->size[0];
  y_d->size[0] = 1;
  emxEnsureCapacity_real_T(&st, y_d, i, &y_emlrtRTEI);
  y_d_data = y_d->data;
  y_d_data[0] = 0.0;
  i = y_colidx->size[0];
  y_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(&st, y_colidx, i, &y_emlrtRTEI);
  y_colidx_data = y_colidx->data;
  y_colidx_data[0] = 1;
  i = y_rowidx->size[0];
  y_rowidx->size[0] = 1;
  emxEnsureCapacity_int32_T(&st, y_rowidx, i, &y_emlrtRTEI);
  y_rowidx_data = y_rowidx->data;
  y_rowidx_data[0] = 1;
  y_colidx_data[1] = 1;
  if (varargin_1 != 0.0) {
    y_rowidx_data[0] = 1;
    y_d_data[0] = varargin_1;
    y_colidx_data[1] = 2;
  }
}

/* End of code generation (sparse.c) */
