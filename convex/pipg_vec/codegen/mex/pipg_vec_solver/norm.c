/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * norm.c
 *
 * Code generation for function 'norm'
 *
 */

/* Include files */
#include "norm.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
real_T b_norm(const real_T x[189])
{
  real_T scale;
  real_T y;
  int32_T k;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < 189; k++) {
    real_T absxk;
    absxk = muDoubleScalarAbs(x[k]);
    if (absxk > scale) {
      real_T t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      real_T t;
      t = absxk / scale;
      y += t * t;
    }
  }
  return scale * muDoubleScalarSqrt(y);
}

real_T c_norm(const real_T x[3])
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  scale = 3.3121686421112381E-170;
  absxk = muDoubleScalarAbs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }
  absxk = muDoubleScalarAbs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  absxk = muDoubleScalarAbs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  return scale * muDoubleScalarSqrt(y);
}

real_T d_norm(const emxArray_real_T *x)
{
  const real_T *x_data;
  real_T y;
  int32_T k;
  x_data = x->data;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    int32_T i;
    y = 0.0;
    i = x->size[0];
    for (k = 0; k < i; k++) {
      real_T absx;
      absx = muDoubleScalarAbs(x_data[k]);
      if (muDoubleScalarIsNaN(absx) || (absx > y)) {
        y = absx;
      }
    }
  }
  return y;
}

/* End of code generation (norm.c) */
