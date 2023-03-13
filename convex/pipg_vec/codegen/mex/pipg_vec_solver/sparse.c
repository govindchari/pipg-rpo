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

/* Function Definitions */
void sparse(real_T varargin_1, emxArray_real_T *y_d, emxArray_int32_T *y_colidx,
            emxArray_int32_T *y_rowidx)
{
  real_T *y_d_data;
  int32_T i;
  int32_T *y_colidx_data;
  int32_T *y_rowidx_data;
  i = y_d->size[0];
  y_d->size[0] = 1;
  emxEnsureCapacity_real_T(y_d, i);
  y_d_data = y_d->data;
  y_d_data[0] = 0.0;
  i = y_colidx->size[0];
  y_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(y_colidx, i);
  y_colidx_data = y_colidx->data;
  y_colidx_data[0] = 1;
  i = y_rowidx->size[0];
  y_rowidx->size[0] = 1;
  emxEnsureCapacity_int32_T(y_rowidx, i);
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
