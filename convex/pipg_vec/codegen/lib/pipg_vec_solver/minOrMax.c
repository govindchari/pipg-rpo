/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.c
 *
 * Code generation for function 'minOrMax'
 *
 */

/* Include files */
#include "minOrMax.h"
#include "pipg_vec_solver_emxutil.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void maximum(const emxArray_real_T *x_d, const emxArray_int32_T *x_colidx,
             emxArray_real_T *ex_d, emxArray_int32_T *ex_colidx,
             emxArray_int32_T *ex_rowidx)
{
  const double *x_d_data;
  double ridx;
  double *ex_d_data;
  const int *x_colidx_data;
  int i;
  int k;
  int ncol;
  int xend;
  int *ex_colidx_data;
  int *ex_rowidx_data;
  x_colidx_data = x_colidx->data;
  x_d_data = x_d->data;
  ridx = 0.0;
  xend = x_colidx_data[1] - 1;
  ncol = x_colidx_data[1] - x_colidx_data[0];
  if (ncol != 0) {
    double colEx;
    colEx = 0.0;
    if (x_colidx_data[1] - 1 >= x_colidx_data[0]) {
      colEx = x_d_data[x_colidx_data[0] - 1];
      i = x_colidx_data[0] + 1;
      for (k = i; k <= xend; k++) {
        double d;
        boolean_T p;
        d = x_d_data[k - 1];
        if (rtIsNaN(d)) {
          p = false;
        } else if (rtIsNaN(colEx)) {
          p = true;
        } else {
          p = (colEx < d);
        }
        if (p) {
          colEx = d;
        }
      }
    }
    if (ncol < 1) {
      if ((!rtIsNaN(colEx)) && (colEx > 0.0)) {
        ridx = colEx;
      }
    } else {
      ridx = colEx;
    }
  }
  i = ex_d->size[0];
  ex_d->size[0] = 1;
  emxEnsureCapacity_real_T(ex_d, i);
  ex_d_data = ex_d->data;
  ex_d_data[0] = 0.0;
  i = ex_colidx->size[0];
  ex_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(ex_colidx, i);
  ex_colidx_data = ex_colidx->data;
  ex_colidx_data[0] = 1;
  i = ex_rowidx->size[0];
  ex_rowidx->size[0] = 1;
  emxEnsureCapacity_int32_T(ex_rowidx, i);
  ex_rowidx_data = ex_rowidx->data;
  ex_rowidx_data[0] = 1;
  ex_colidx_data[1] = 1;
  if (ridx != 0.0) {
    ex_rowidx_data[0] = 1;
    ex_d_data[0] = ridx;
    ex_colidx_data[1] = 2;
  }
}

/* End of code generation (minOrMax.c) */
