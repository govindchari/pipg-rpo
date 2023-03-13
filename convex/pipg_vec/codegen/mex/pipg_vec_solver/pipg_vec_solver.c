/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver.c
 *
 * Code generation for function 'pipg_vec_solver'
 *
 */

/* Include files */
#include "pipg_vec_solver.h"
#include "colon.h"
#include "diag.h"
#include "dot.h"
#include "mod.h"
#include "mtimes.h"
#include "norm.h"
#include "pipg_vec_solver_data.h"
#include "pipg_vec_solver_emxutil.h"
#include "pipg_vec_solver_types.h"
#include "proj_cone.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "tic.h"
#include "toc.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Declarations */
static void b_binary_expand_op(real_T in1[120], const emxArray_real_T *in2,
                               const struct1_T *in3);

static void c_binary_expand_op(real_T in1[189], const emxArray_real_T *in2,
                               const struct1_T *in3);

/* Function Definitions */
static void b_binary_expand_op(real_T in1[120], const emxArray_real_T *in2,
                               const struct1_T *in3)
{
  const real_T *in2_data;
  int32_T i;
  int32_T stride_0_0;
  in2_data = in2->data;
  stride_0_0 = (in2->size[0] != 1);
  for (i = 0; i < 120; i++) {
    in1[i] = in2_data[i * stride_0_0] - in3->eta[i];
  }
}

static void c_binary_expand_op(real_T in1[189], const emxArray_real_T *in2,
                               const struct1_T *in3)
{
  const real_T *in2_data;
  int32_T i;
  int32_T stride_0_0;
  in2_data = in2->data;
  stride_0_0 = (in2->size[0] != 1);
  for (i = 0; i < 189; i++) {
    in1[i] = in2_data[i * stride_0_0] - in3->xi[i];
  }
}

void pipg_vec_solver(const struct0_T *par, struct1_T *p, const struct2_T *opts,
                     real_T Z[189], real_T W[120], real_T *solve_time)
{
  static const int8_T b[3] = {0, 1, 0};
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  emxArray_int32_T *varargin_1_colidx;
  emxArray_int32_T *varargin_1_rowidx;
  emxArray_real_T *etaold;
  emxArray_real_T *idx_r;
  emxArray_real_T *idx_u;
  emxArray_real_T *idx_v;
  emxArray_real_T *varargin_1_d;
  emxArray_real_T *xiold;
  emxArray_uint8_T *r;
  real_T b_z[189];
  real_T z[189];
  real_T b_data[3];
  real_T alpha;
  real_T beta;
  real_T d;
  real_T d1;
  real_T fullEx;
  real_T iter;
  real_T k;
  real_T norm2H;
  real_T sig_old;
  real_T *etaold_data;
  real_T *idx_r_data;
  real_T *idx_u_data;
  real_T *idx_v_data;
  real_T *varargin_1_d_data;
  real_T *xiold_data;
  int32_T b_i;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T loop_ub_tmp;
  int32_T ncol;
  int32_T *varargin_1_colidx_data;
  uint8_T *r1;
  boolean_T stop;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  tic();
  stop = false;
  /*      fprintf("iter     objv     |Gx-g|\n") */
  /*      fprintf("-----------------------------\n") */
  emxInit_real_T(&xiold, 1);
  ncol = (int32_T)(par->N * (par->nx + par->nu));
  i = xiold->size[0];
  xiold->size[0] = ncol;
  emxEnsureCapacity_real_T(xiold, i);
  xiold_data = xiold->data;
  for (i = 0; i < ncol; i++) {
    xiold_data[i] = 1.0;
  }
  ncol = xiold->size[0];
  for (i = 0; i < ncol; i++) {
    xiold_data[i] *= 1.0E+6;
  }
  emxInit_real_T(&etaold, 1);
  d = (par->N - 1.0) * par->nx;
  loop_ub_tmp = (int32_T)d;
  i = etaold->size[0];
  etaold->size[0] = (int32_T)d;
  emxEnsureCapacity_real_T(etaold, i);
  etaold_data = etaold->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    etaold_data[i] = 1.0;
  }
  ncol = etaold->size[0];
  for (i = 0; i < ncol; i++) {
    etaold_data[i] *= 1.0E+6;
  }
  k = 1.0;
  /*  Assumes P is diagonal */
  emxInit_real_T(&varargin_1_d, 1);
  emxInit_int32_T(&varargin_1_colidx);
  emxInit_int32_T(&varargin_1_rowidx);
  sparse_diag(p->P.d, p->P.colidx, p->P.rowidx, varargin_1_d, varargin_1_colidx,
              varargin_1_rowidx);
  varargin_1_colidx_data = varargin_1_colidx->data;
  varargin_1_d_data = varargin_1_d->data;
  fullEx = 0.0;
  loop_ub_tmp = varargin_1_colidx_data[1] - 1;
  ncol = varargin_1_colidx_data[1] - varargin_1_colidx_data[0];
  if (ncol != 0) {
    norm2H = 0.0;
    if (varargin_1_colidx_data[1] - 1 >= varargin_1_colidx_data[0]) {
      norm2H = varargin_1_d_data[varargin_1_colidx_data[0] - 1];
      i = varargin_1_colidx_data[0] + 1;
      for (b_i = i; b_i <= loop_ub_tmp; b_i++) {
        boolean_T b_p;
        d1 = varargin_1_d_data[b_i - 1];
        if (muDoubleScalarIsNaN(d1)) {
          b_p = false;
        } else if (muDoubleScalarIsNaN(norm2H)) {
          b_p = true;
        } else {
          b_p = (norm2H < d1);
        }
        if (b_p) {
          norm2H = d1;
        }
      }
    }
    if (ncol < 1) {
      if ((!muDoubleScalarIsNaN(norm2H)) && (norm2H > 0.0)) {
        fullEx = norm2H;
      }
    } else {
      fullEx = norm2H;
    }
  }
  sparse(fullEx, varargin_1_d, varargin_1_colidx, varargin_1_rowidx);
  varargin_1_colidx_data = varargin_1_colidx->data;
  varargin_1_d_data = varargin_1_d->data;
  fullEx = 0.0;
  i = varargin_1_colidx_data[1] - 1;
  i1 = varargin_1_colidx_data[0];
  for (loop_ub_tmp = i1; loop_ub_tmp <= i; loop_ub_tmp++) {
    fullEx = varargin_1_d_data[0];
  }
  for (b_i = 0; b_i < 189; b_i++) {
    z[b_i] = 0.072739296745330792;
  }
  norm2H = 0.0;
  sig_old = 1.0E+6;
  iter = 1.0;
  while ((muDoubleScalarAbs(norm2H - sig_old) >=
          opts->eps_abs_pow +
              opts->eps_rel_pow * muDoubleScalarMax(norm2H, sig_old)) &&
         (iter < opts->max_iter_pow)) {
    sig_old = norm2H;
    sparse_mtimes(p->Ht.d, p->Ht.colidx, p->Ht.rowidx, p->H.d, p->H.colidx,
                  p->H.rowidx, varargin_1_d, varargin_1_colidx,
                  varargin_1_rowidx);
    memcpy(&b_z[0], &z[0], 189U * sizeof(real_T));
    b_sparse_mtimes(varargin_1_d, varargin_1_colidx, varargin_1_rowidx, b_z, z);
    norm2H = b_norm(z);
    for (i = 0; i < 189; i++) {
      z[i] /= norm2H;
    }
    iter++;
  }
  emxFree_int32_T(&varargin_1_rowidx);
  emxFree_int32_T(&varargin_1_colidx);
  norm2H *= opts->eps_buff + 1.0;
  alpha =
      2.0 / (muDoubleScalarSqrt(fullEx * fullEx + 4.0 * opts->omega * norm2H) +
             fullEx);
  beta = opts->omega * alpha;
  if (par->nx < 1.0) {
    ncol = 0;
  } else {
    ncol = (int32_T)par->nx;
  }
  d1 = par->N * par->nx;
  if (d + 1.0 > d1) {
    i = 0;
    i1 = 0;
  } else {
    i = (int32_T)(d + 1.0) - 1;
    i1 = (int32_T)d1;
  }
  i2 = (int32_T)par->N;
  emxInit_real_T(&idx_u, 2);
  idx_u_data = idx_u->data;
  emxInit_real_T(&idx_r, 2);
  idx_r_data = idx_r->data;
  emxInit_real_T(&idx_v, 2);
  idx_v_data = idx_v->data;
  emxInit_uint8_T(&r);
  while (!stop) {
    real_T x[120];
    /*  Primal Update */
    norm2H = p->umax;
    sig_old = p->vmax;
    b_sparse_mtimes(p->P.d, p->P.colidx, p->P.rowidx, p->xi, z);
    c_sparse_mtimes(p->Ht.d, p->Ht.colidx, p->Ht.rowidx, p->eta, b_z);
    for (i3 = 0; i3 < 189; i3++) {
      p->z[i3] = p->xi[i3] - alpha * (z[i3] + b_z[i3]);
    }
    if (ncol - 1 >= 0) {
      memcpy(&p->z[0], &par->x0s[0], (uint32_T)ncol * sizeof(real_T));
    }
    loop_ub_tmp = i1 - i;
    for (i3 = 0; i3 < loop_ub_tmp; i3++) {
      p->z[i + i3] = par->xNs[i3];
    }
    /*  State and Control Constraints */
    for (b_i = 0; b_i < i2; b_i++) {
      real_T a_tmp;
      iter = (d1 + (((real_T)b_i + 1.0) - 1.0) * par->nu) + 1.0;
      fullEx = d1 + ((real_T)b_i + 1.0) * par->nu;
      if (muDoubleScalarIsNaN(iter) || muDoubleScalarIsNaN(fullEx)) {
        i3 = idx_u->size[0] * idx_u->size[1];
        idx_u->size[0] = 1;
        idx_u->size[1] = 1;
        emxEnsureCapacity_real_T(idx_u, i3);
        idx_u_data = idx_u->data;
        idx_u_data[0] = rtNaN;
      } else if (fullEx < iter) {
        idx_u->size[0] = 1;
        idx_u->size[1] = 0;
      } else if ((muDoubleScalarIsInf(iter) || muDoubleScalarIsInf(fullEx)) &&
                 (iter == fullEx)) {
        i3 = idx_u->size[0] * idx_u->size[1];
        idx_u->size[0] = 1;
        idx_u->size[1] = 1;
        emxEnsureCapacity_real_T(idx_u, i3);
        idx_u_data = idx_u->data;
        idx_u_data[0] = rtNaN;
      } else if (muDoubleScalarFloor(iter) == iter) {
        i3 = idx_u->size[0] * idx_u->size[1];
        idx_u->size[0] = 1;
        loop_ub_tmp = (int32_T)(fullEx - iter);
        idx_u->size[1] = loop_ub_tmp + 1;
        emxEnsureCapacity_real_T(idx_u, i3);
        idx_u_data = idx_u->data;
        for (i3 = 0; i3 <= loop_ub_tmp; i3++) {
          idx_u_data[i3] = iter + (real_T)i3;
        }
      } else {
        eml_float_colon(iter, fullEx, idx_u);
        idx_u_data = idx_u->data;
      }
      a_tmp = (((real_T)b_i + 1.0) - 1.0) * par->nx;
      if (muDoubleScalarIsNaN(a_tmp + 1.0) ||
          muDoubleScalarIsNaN(a_tmp + 3.0)) {
        i3 = idx_r->size[0] * idx_r->size[1];
        idx_r->size[0] = 1;
        idx_r->size[1] = 1;
        emxEnsureCapacity_real_T(idx_r, i3);
        idx_r_data = idx_r->data;
        idx_r_data[0] = rtNaN;
      } else if (a_tmp + 3.0 < a_tmp + 1.0) {
        idx_r->size[0] = 1;
        idx_r->size[1] = 0;
      } else if ((muDoubleScalarIsInf(a_tmp + 1.0) ||
                  muDoubleScalarIsInf(a_tmp + 3.0)) &&
                 (a_tmp + 1.0 == a_tmp + 3.0)) {
        i3 = idx_r->size[0] * idx_r->size[1];
        idx_r->size[0] = 1;
        idx_r->size[1] = 1;
        emxEnsureCapacity_real_T(idx_r, i3);
        idx_r_data = idx_r->data;
        idx_r_data[0] = rtNaN;
      } else if (muDoubleScalarFloor(a_tmp + 1.0) == a_tmp + 1.0) {
        i3 = idx_r->size[0] * idx_r->size[1];
        idx_r->size[0] = 1;
        loop_ub_tmp = (int32_T)((a_tmp + 3.0) - (a_tmp + 1.0));
        idx_r->size[1] = loop_ub_tmp + 1;
        emxEnsureCapacity_real_T(idx_r, i3);
        idx_r_data = idx_r->data;
        for (i3 = 0; i3 <= loop_ub_tmp; i3++) {
          idx_r_data[i3] = (a_tmp + 1.0) + (real_T)i3;
        }
      } else {
        eml_float_colon(a_tmp + 1.0, a_tmp + 3.0, idx_r);
        idx_r_data = idx_r->data;
      }
      fullEx = ((real_T)b_i + 1.0) * par->nx;
      if (muDoubleScalarIsNaN(a_tmp + 4.0) || muDoubleScalarIsNaN(fullEx)) {
        i3 = idx_v->size[0] * idx_v->size[1];
        idx_v->size[0] = 1;
        idx_v->size[1] = 1;
        emxEnsureCapacity_real_T(idx_v, i3);
        idx_v_data = idx_v->data;
        idx_v_data[0] = rtNaN;
      } else if (fullEx < a_tmp + 4.0) {
        idx_v->size[0] = 1;
        idx_v->size[1] = 0;
      } else if ((muDoubleScalarIsInf(a_tmp + 4.0) ||
                  muDoubleScalarIsInf(fullEx)) &&
                 (a_tmp + 4.0 == fullEx)) {
        i3 = idx_v->size[0] * idx_v->size[1];
        idx_v->size[0] = 1;
        idx_v->size[1] = 1;
        emxEnsureCapacity_real_T(idx_v, i3);
        idx_v_data = idx_v->data;
        idx_v_data[0] = rtNaN;
      } else if (muDoubleScalarFloor(a_tmp + 4.0) == a_tmp + 4.0) {
        i3 = idx_v->size[0] * idx_v->size[1];
        idx_v->size[0] = 1;
        loop_ub_tmp = (int32_T)(fullEx - (a_tmp + 4.0));
        idx_v->size[1] = loop_ub_tmp + 1;
        emxEnsureCapacity_real_T(idx_v, i3);
        idx_v_data = idx_v->data;
        for (i3 = 0; i3 <= loop_ub_tmp; i3++) {
          idx_v_data[i3] = (a_tmp + 4.0) + (real_T)i3;
        }
      } else {
        eml_float_colon(a_tmp + 4.0, fullEx, idx_v);
        idx_v_data = idx_v->data;
      }
      i3 = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = idx_u->size[1];
      emxEnsureCapacity_uint8_T(r, i3);
      r1 = r->data;
      loop_ub_tmp = idx_u->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        r1[i3] = (uint8_T)idx_u_data[i3];
      }
      i3 = varargin_1_d->size[0];
      varargin_1_d->size[0] = idx_u->size[1];
      emxEnsureCapacity_real_T(varargin_1_d, i3);
      varargin_1_d_data = varargin_1_d->data;
      loop_ub_tmp = idx_u->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        varargin_1_d_data[i3] = p->z[(int32_T)idx_u_data[i3] - 1];
      }
      if (idx_u->size[1] == 0) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)idx_u->size[1];
        incx_t = (ptrdiff_t)1;
        d = dnrm2(&n_t, &varargin_1_d_data[0], &incx_t);
      }
      if (d > norm2H) {
        iter = norm2H / d;
        loop_ub_tmp = varargin_1_d->size[0];
        for (i3 = 0; i3 < loop_ub_tmp; i3++) {
          varargin_1_d_data[i3] *= iter;
        }
      }
      loop_ub_tmp = r->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        p->z[r1[i3] - 1] = varargin_1_d_data[i3];
      }
      i3 = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = idx_r->size[1];
      emxEnsureCapacity_uint8_T(r, i3);
      r1 = r->data;
      loop_ub_tmp = idx_r->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        r1[i3] = (uint8_T)idx_r_data[i3];
      }
      i3 = varargin_1_d->size[0];
      varargin_1_d->size[0] = idx_r->size[1];
      emxEnsureCapacity_real_T(varargin_1_d, i3);
      varargin_1_d_data = varargin_1_d->data;
      loop_ub_tmp = idx_r->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        varargin_1_d_data[i3] = p->z[(int32_T)idx_r_data[i3] - 1];
      }
      fullEx = muDoubleScalarCos(par->th_ac);
      if (idx_r->size[1] == 0) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)idx_r->size[1];
        incx_t = (ptrdiff_t)1;
        d = dnrm2(&n_t, &varargin_1_d_data[0], &incx_t);
      }
      a_tmp = dot(varargin_1_d);
      if (!(fullEx * d <= a_tmp)) {
        iter = muDoubleScalarSqrt(1.0 - fullEx * fullEx);
        if (iter * d <= -a_tmp) {
          i3 = varargin_1_d->size[0];
          varargin_1_d->size[0] = 3;
          emxEnsureCapacity_real_T(varargin_1_d, i3);
          varargin_1_d_data = varargin_1_d->data;
          varargin_1_d_data[0] = 0.0;
          varargin_1_d_data[1] = 0.0;
          varargin_1_d_data[2] = 0.0;
        } else {
          real_T y[3];
          y[0] = a_tmp * 0.0;
          y[1] = a_tmp;
          y[2] = a_tmp * 0.0;
          if (varargin_1_d->size[0] == 3) {
            for (i3 = 0; i3 < 3; i3++) {
              y[i3] = varargin_1_d_data[i3] - y[i3];
            }
            d = c_norm(y);
            y[0] =
                fullEx * 0.0 + iter * (varargin_1_d_data[0] - a_tmp * 0.0) / d;
            y[1] = fullEx + iter * (varargin_1_d_data[1] - a_tmp) / d;
            y[2] =
                fullEx * 0.0 + iter * (varargin_1_d_data[2] - a_tmp * 0.0) / d;
          } else {
            binary_expand_op(y, fullEx, b, iter, varargin_1_d, a_tmp);
          }
          b_data[0] = y[0];
          b_data[1] = y[1];
          b_data[2] = y[2];
          if (idx_r->size[1] < 1) {
            iter = 0.0;
          } else {
            n_t = (ptrdiff_t)idx_r->size[1];
            incx_t = (ptrdiff_t)1;
            incy_t = (ptrdiff_t)1;
            iter =
                ddot(&n_t, &varargin_1_d_data[0], &incx_t, &b_data[0], &incy_t);
          }
          i3 = varargin_1_d->size[0];
          varargin_1_d->size[0] = 3;
          emxEnsureCapacity_real_T(varargin_1_d, i3);
          varargin_1_d_data = varargin_1_d->data;
          varargin_1_d_data[0] = iter * y[0];
          varargin_1_d_data[1] = iter * y[1];
          varargin_1_d_data[2] = iter * y[2];
        }
      }
      loop_ub_tmp = r->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        p->z[r1[i3] - 1] = varargin_1_d_data[i3];
      }
      i3 = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = idx_v->size[1];
      emxEnsureCapacity_uint8_T(r, i3);
      r1 = r->data;
      loop_ub_tmp = idx_v->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        r1[i3] = (uint8_T)idx_v_data[i3];
      }
      i3 = varargin_1_d->size[0];
      varargin_1_d->size[0] = idx_v->size[1];
      emxEnsureCapacity_real_T(varargin_1_d, i3);
      varargin_1_d_data = varargin_1_d->data;
      loop_ub_tmp = idx_v->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        varargin_1_d_data[i3] = p->z[(int32_T)idx_v_data[i3] - 1];
      }
      if (idx_v->size[1] == 0) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)idx_v->size[1];
        incx_t = (ptrdiff_t)1;
        d = dnrm2(&n_t, &varargin_1_d_data[0], &incx_t);
      }
      if (d > sig_old) {
        iter = sig_old / d;
        loop_ub_tmp = varargin_1_d->size[0];
        for (i3 = 0; i3 < loop_ub_tmp; i3++) {
          varargin_1_d_data[i3] *= iter;
        }
      }
      loop_ub_tmp = r->size[1];
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        p->z[r1[i3] - 1] = varargin_1_d_data[i3];
      }
    }
    /*  Dual Update */
    for (i3 = 0; i3 < 189; i3++) {
      b_z[i3] = 2.0 * p->z[i3] - p->xi[i3];
    }
    d_sparse_mtimes(p->H.d, p->H.colidx, p->H.rowidx, b_z, x);
    for (i3 = 0; i3 < 120; i3++) {
      p->w[i3] = p->eta[i3] + beta * x[i3];
    }
    /*  Extrapolation */
    for (i3 = 0; i3 < 189; i3++) {
      p->xi[i3] = (1.0 - opts->rho) * p->xi[i3] + opts->rho * p->z[i3];
    }
    for (i3 = 0; i3 < 120; i3++) {
      p->eta[i3] = (1.0 - opts->rho) * p->eta[i3] + opts->rho * p->w[i3];
    }
    d = b_mod(k, opts->check_iter);
    if (d == 0.0) {
      boolean_T guard1 = false;
      /*              fprintf("%d   %.3e  %.2e\n", k, 0.5 * p.xi' * p.P * p.xi,
       * norm(p.H * p.xi)); */
      /*              primal_conv(end+1) = abs(norm((xiold-p.xi), Inf) -
       * last_primal); */
      /*              dual_conv(end+1) = abs(norm((etaold-p.eta), Inf) -
       * last_dual); */
      /*              last_primal = norm((xiold-p.xi), Inf); */
      /*              last_dual = norm((etaold-p.eta), Inf); */
      /*              beta = alpha * 0.1 * ((norm((xiold-p.xi), Inf) /
       * norm((etaold-p.eta), Inf))); */
      fullEx = 0.0;
      for (b_i = 0; b_i < 189; b_i++) {
        norm2H = muDoubleScalarAbs(p->xi[b_i]);
        if (muDoubleScalarIsNaN(norm2H) || (norm2H > fullEx)) {
          fullEx = norm2H;
        }
      }
      if (xiold->size[0] == 189) {
        for (i3 = 0; i3 < 189; i3++) {
          z[i3] = xiold_data[i3] - p->xi[i3];
        }
      } else {
        c_binary_expand_op(z, xiold, p);
      }
      sig_old = 0.0;
      for (b_i = 0; b_i < 189; b_i++) {
        norm2H = muDoubleScalarAbs(z[b_i]);
        if (muDoubleScalarIsNaN(norm2H) || (norm2H > sig_old)) {
          sig_old = norm2H;
        }
      }
      guard1 = false;
      if (sig_old <=
          opts->eps_abs +
              opts->eps_rel * muDoubleScalarMax(fullEx, d_norm(xiold))) {
        fullEx = 0.0;
        for (b_i = 0; b_i < 120; b_i++) {
          norm2H = muDoubleScalarAbs(p->eta[b_i]);
          if (muDoubleScalarIsNaN(norm2H) || (norm2H > fullEx)) {
            fullEx = norm2H;
          }
        }
        if (etaold->size[0] == 120) {
          for (i3 = 0; i3 < 120; i3++) {
            x[i3] = etaold_data[i3] - p->eta[i3];
          }
        } else {
          b_binary_expand_op(x, etaold, p);
        }
        sig_old = 0.0;
        for (b_i = 0; b_i < 120; b_i++) {
          norm2H = muDoubleScalarAbs(x[b_i]);
          if (muDoubleScalarIsNaN(norm2H) || (norm2H > sig_old)) {
            sig_old = norm2H;
          }
        }
        if (sig_old <=
            opts->eps_abs +
                opts->eps_rel * muDoubleScalarMax(fullEx, d_norm(etaold))) {
          stop = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1 && (k >= opts->max_iter)) {
        stop = true;
      }
    }
    if (d == opts->check_iter - 1.0) {
      i3 = xiold->size[0];
      xiold->size[0] = 189;
      emxEnsureCapacity_real_T(xiold, i3);
      xiold_data = xiold->data;
      for (i3 = 0; i3 < 189; i3++) {
        xiold_data[i3] = p->xi[i3];
      }
      i3 = etaold->size[0];
      etaold->size[0] = 120;
      emxEnsureCapacity_real_T(etaold, i3);
      etaold_data = etaold->data;
      for (i3 = 0; i3 < 120; i3++) {
        etaold_data[i3] = p->eta[i3];
      }
    }
    k++;
  }
  emxFree_uint8_T(&r);
  emxFree_real_T(&idx_v);
  emxFree_real_T(&idx_r);
  emxFree_real_T(&idx_u);
  emxFree_real_T(&varargin_1_d);
  emxFree_real_T(&etaold);
  emxFree_real_T(&xiold);
  memcpy(&Z[0], &p->xi[0], 189U * sizeof(real_T));
  memcpy(&W[0], &p->eta[0], 120U * sizeof(real_T));
  *solve_time = toc() * 1000.0;
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (pipg_vec_solver.c) */
