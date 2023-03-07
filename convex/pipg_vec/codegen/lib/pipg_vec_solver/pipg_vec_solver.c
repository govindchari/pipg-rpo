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
#include "minOrMax.h"
#include "mtimes.h"
#include "pipg_vec_solver_data.h"
#include "pipg_vec_solver_emxutil.h"
#include "pipg_vec_solver_initialize.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include "tic.h"
#include "toc.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void b_binary_expand_op(double in1[189], const emxArray_real_T *in2,
                               const struct1_T *in3);

static void binary_expand_op(double in1[120], const emxArray_real_T *in2,
                             const struct1_T *in3);

/* Function Definitions */
static void b_binary_expand_op(double in1[189], const emxArray_real_T *in2,
                               const struct1_T *in3)
{
  const double *in2_data;
  int i;
  int stride_0_0;
  in2_data = in2->data;
  stride_0_0 = (in2->size[0] != 1);
  for (i = 0; i < 189; i++) {
    in1[i] = in2_data[i * stride_0_0] - in3->xi[i];
  }
}

static void binary_expand_op(double in1[120], const emxArray_real_T *in2,
                             const struct1_T *in3)
{
  const double *in2_data;
  int i;
  int stride_0_0;
  in2_data = in2->data;
  stride_0_0 = (in2->size[0] != 1);
  for (i = 0; i < 120; i++) {
    in1[i] = in2_data[i * stride_0_0] - in3->eta[i];
  }
}

void pipg_vec_solver(const struct0_T *par, struct1_T *p, const struct2_T *opts,
                     double Z[189], double *solve_time)
{
  emxArray_int32_T *expl_temp;
  emxArray_int32_T *t2_colidx;
  emxArray_int32_T *t2_rowidx;
  emxArray_real_T *etaold;
  emxArray_real_T *idx;
  emxArray_real_T *maxval_d;
  emxArray_real_T *t2_d;
  emxArray_real_T *xiold;
  emxArray_uint8_T *r;
  double b_z[189];
  double z[189];
  double c[120];
  double absxk;
  double alpha;
  double beta;
  double d;
  double d1;
  double iter;
  double k;
  double norm2H;
  double normP;
  double scale;
  double sig_old;
  double t;
  double *etaold_data;
  double *idx_data;
  double *t2_d_data;
  double *xiold_data;
  int acol;
  int ap;
  int b_i;
  int cend;
  int i;
  int i1;
  int i2;
  int i3;
  int loop_ub;
  int nap;
  int *t2_rowidx_data;
  unsigned char *r1;
  boolean_T stop;
  if (!isInitialized_pipg_vec_solver) {
    pipg_vec_solver_initialize();
  }
  tic();
  stop = false;
  /*      fprintf("iter     objv     |Gx-g|\n") */
  /*      fprintf("-----------------------------\n") */
  emxInit_real_T(&xiold, 1);
  loop_ub = (int)(par->N * (par->nx + par->nu));
  i = xiold->size[0];
  xiold->size[0] = loop_ub;
  emxEnsureCapacity_real_T(xiold, i);
  xiold_data = xiold->data;
  for (i = 0; i < loop_ub; i++) {
    xiold_data[i] = 1.0;
  }
  loop_ub = xiold->size[0];
  for (i = 0; i < loop_ub; i++) {
    xiold_data[i] *= 1.0E+6;
  }
  emxInit_real_T(&etaold, 1);
  d = (par->N - 1.0) * par->nx;
  cend = (int)d;
  i = etaold->size[0];
  etaold->size[0] = (int)d;
  emxEnsureCapacity_real_T(etaold, i);
  etaold_data = etaold->data;
  for (i = 0; i < cend; i++) {
    etaold_data[i] = 1.0;
  }
  loop_ub = etaold->size[0];
  for (i = 0; i < loop_ub; i++) {
    etaold_data[i] *= 1.0E+6;
  }
  k = 1.0;
  /*  Assumes P is diagonal */
  emxInit_real_T(&t2_d, 1);
  emxInit_int32_T(&t2_colidx, 1);
  emxInit_int32_T(&t2_rowidx, 1);
  sparse_diag(p->P.d, p->P.colidx, p->P.rowidx, t2_d, t2_colidx, t2_rowidx);
  emxInit_real_T(&maxval_d, 1);
  emxInit_int32_T(&expl_temp, 1);
  maximum(t2_d, t2_colidx, maxval_d, t2_rowidx, expl_temp);
  t2_rowidx_data = t2_rowidx->data;
  idx_data = maxval_d->data;
  emxFree_int32_T(&expl_temp);
  normP = 0.0;
  cend = t2_rowidx_data[1] - 1;
  i = t2_rowidx_data[0];
  for (nap = i; nap <= cend; nap++) {
    normP = idx_data[0];
  }
  emxFree_real_T(&maxval_d);
  for (b_i = 0; b_i < 189; b_i++) {
    z[b_i] = 0.072739296745330792;
  }
  norm2H = 0.0;
  sig_old = 1.0E+6;
  iter = 1.0;
  while ((fabs(norm2H - sig_old) >=
          opts->eps_abs_pow + opts->eps_rel_pow * fmax(norm2H, sig_old)) &&
         (iter < opts->max_iter_pow)) {
    sig_old = norm2H;
    sparse_mtimes(p->Ht.d, p->Ht.colidx, p->Ht.rowidx, p->H.d, p->H.colidx,
                  p->H.rowidx, t2_d, t2_colidx, t2_rowidx);
    memcpy(&b_z[0], &z[0], 189U * sizeof(double));
    b_sparse_mtimes(t2_d, t2_colidx, t2_rowidx, b_z, z);
    norm2H = 0.0;
    scale = 3.3121686421112381E-170;
    for (nap = 0; nap < 189; nap++) {
      absxk = fabs(z[nap]);
      if (absxk > scale) {
        t = scale / absxk;
        norm2H = norm2H * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        norm2H += t * t;
      }
    }
    norm2H = scale * sqrt(norm2H);
    for (i = 0; i < 189; i++) {
      z[i] /= norm2H;
    }
    iter++;
  }
  emxFree_int32_T(&t2_rowidx);
  emxFree_int32_T(&t2_colidx);
  norm2H *= opts->eps_buff + 1.0;
  alpha = 2.0 / (sqrt(normP * normP + 4.0 * opts->omega * norm2H) + normP);
  beta = opts->omega * alpha;
  if (par->nx < 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = (int)par->nx;
  }
  d1 = par->N * par->nx;
  if (d + 1.0 > d1) {
    i = 0;
    i1 = 0;
  } else {
    i = (int)(d + 1.0) - 1;
    i1 = (int)d1;
  }
  i2 = (int)par->N;
  emxInit_real_T(&idx, 2);
  idx_data = idx->data;
  emxInit_uint8_T(&r);
  while (!stop) {
    /*  Primal Update */
    memset(&z[0], 0, 189U * sizeof(double));
    if (p->Ht.colidx->data[p->Ht.colidx->size[0] - 1] - 1 != 0) {
      for (acol = 0; acol < 120; acol++) {
        normP = p->eta[acol];
        i3 = p->Ht.colidx->data[acol];
        cend = p->Ht.colidx->data[acol + 1];
        nap = cend - p->Ht.colidx->data[acol];
        if (nap >= 4) {
          b_i = (cend - nap) + ((nap / 4) << 2);
          for (ap = i3; ap <= b_i - 1; ap += 4) {
            nap = p->Ht.rowidx->data[ap - 1] - 1;
            z[nap] += p->Ht.d->data[ap - 1] * normP;
            z[p->Ht.rowidx->data[ap] - 1] += p->Ht.d->data[ap] * normP;
            nap = p->Ht.rowidx->data[ap + 1] - 1;
            z[nap] += p->Ht.d->data[ap + 1] * normP;
            nap = p->Ht.rowidx->data[ap + 2] - 1;
            z[nap] += p->Ht.d->data[ap + 2] * normP;
          }
          cend = p->Ht.colidx->data[acol + 1] - 1;
          for (ap = b_i; ap <= cend; ap++) {
            nap = p->Ht.rowidx->data[ap - 1] - 1;
            z[nap] += p->Ht.d->data[ap - 1] * normP;
          }
        } else {
          cend--;
          for (ap = i3; ap <= cend; ap++) {
            nap = p->Ht.rowidx->data[ap - 1] - 1;
            z[nap] += p->Ht.d->data[ap - 1] * normP;
          }
        }
      }
    }
    sig_old = p->umax;
    b_sparse_mtimes(p->P.d, p->P.colidx, p->P.rowidx, p->xi, b_z);
    for (i3 = 0; i3 < 189; i3++) {
      p->z[i3] = p->xi[i3] - alpha * (b_z[i3] + z[i3]);
    }
    if (loop_ub - 1 >= 0) {
      memcpy(&p->z[0], &par->x0s[0], (unsigned int)loop_ub * sizeof(double));
    }
    cend = i1 - i;
    for (i3 = 0; i3 < cend; i3++) {
      p->z[i + i3] = par->xNs[i3];
    }
    /*  Input Norm Constraint */
    for (b_i = 0; b_i < i2; b_i++) {
      normP = (d1 + (((double)b_i + 1.0) - 1.0) * par->nu) + 1.0;
      norm2H = d1 + ((double)b_i + 1.0) * par->nu;
      if (rtIsNaN(normP) || rtIsNaN(norm2H)) {
        i3 = idx->size[0] * idx->size[1];
        idx->size[0] = 1;
        idx->size[1] = 1;
        emxEnsureCapacity_real_T(idx, i3);
        idx_data = idx->data;
        idx_data[0] = rtNaN;
      } else if (norm2H < normP) {
        idx->size[0] = 1;
        idx->size[1] = 0;
      } else if ((rtIsInf(normP) || rtIsInf(norm2H)) && (normP == norm2H)) {
        i3 = idx->size[0] * idx->size[1];
        idx->size[0] = 1;
        idx->size[1] = 1;
        emxEnsureCapacity_real_T(idx, i3);
        idx_data = idx->data;
        idx_data[0] = rtNaN;
      } else if (floor(normP) == normP) {
        i3 = idx->size[0] * idx->size[1];
        idx->size[0] = 1;
        cend = (int)(norm2H - normP);
        idx->size[1] = cend + 1;
        emxEnsureCapacity_real_T(idx, i3);
        idx_data = idx->data;
        for (i3 = 0; i3 <= cend; i3++) {
          idx_data[i3] = normP + (double)i3;
        }
      } else {
        eml_float_colon(normP, norm2H, idx);
        idx_data = idx->data;
      }
      i3 = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = idx->size[1];
      emxEnsureCapacity_uint8_T(r, i3);
      r1 = r->data;
      cend = idx->size[1];
      for (i3 = 0; i3 < cend; i3++) {
        r1[i3] = (unsigned char)idx_data[i3];
      }
      i3 = t2_d->size[0];
      t2_d->size[0] = idx->size[1];
      emxEnsureCapacity_real_T(t2_d, i3);
      t2_d_data = t2_d->data;
      cend = idx->size[1];
      for (i3 = 0; i3 < cend; i3++) {
        t2_d_data[i3] = p->z[(int)idx_data[i3] - 1];
      }
      if (idx->size[1] == 0) {
        d = 0.0;
      } else {
        d = 0.0;
        if (idx->size[1] == 1) {
          d = fabs(p->z[(int)idx_data[0] - 1]);
        } else {
          scale = 3.3121686421112381E-170;
          cend = idx->size[1];
          for (nap = 0; nap < cend; nap++) {
            absxk = fabs(p->z[(int)idx_data[nap] - 1]);
            if (absxk > scale) {
              t = scale / absxk;
              d = d * t * t + 1.0;
              scale = absxk;
            } else {
              t = absxk / scale;
              d += t * t;
            }
          }
          d = scale * sqrt(d);
        }
      }
      if (d > sig_old) {
        normP = sig_old / d;
        cend = t2_d->size[0];
        for (i3 = 0; i3 < cend; i3++) {
          t2_d_data[i3] *= normP;
        }
      }
      cend = r->size[1];
      for (i3 = 0; i3 < cend; i3++) {
        p->z[r1[i3] - 1] = t2_d_data[i3];
      }
    }
    /*  Dual Update */
    for (b_i = 0; b_i < 189; b_i++) {
      z[b_i] = 2.0 * p->z[b_i] - p->xi[b_i];
    }
    memset(&c[0], 0, 120U * sizeof(double));
    if (p->H.colidx->data[p->H.colidx->size[0] - 1] - 1 != 0) {
      for (acol = 0; acol < 189; acol++) {
        normP = z[acol];
        i3 = p->H.colidx->data[acol];
        cend = p->H.colidx->data[acol + 1];
        nap = cend - p->H.colidx->data[acol];
        if (nap >= 4) {
          b_i = (cend - nap) + ((nap / 4) << 2);
          for (ap = i3; ap <= b_i - 1; ap += 4) {
            nap = p->H.rowidx->data[ap - 1] - 1;
            c[nap] += p->H.d->data[ap - 1] * normP;
            c[p->H.rowidx->data[ap] - 1] += p->H.d->data[ap] * normP;
            nap = p->H.rowidx->data[ap + 1] - 1;
            c[nap] += p->H.d->data[ap + 1] * normP;
            nap = p->H.rowidx->data[ap + 2] - 1;
            c[nap] += p->H.d->data[ap + 2] * normP;
          }
          cend = p->H.colidx->data[acol + 1] - 1;
          for (ap = b_i; ap <= cend; ap++) {
            nap = p->H.rowidx->data[ap - 1] - 1;
            c[nap] += p->H.d->data[ap - 1] * normP;
          }
        } else {
          cend--;
          for (ap = i3; ap <= cend; ap++) {
            nap = p->H.rowidx->data[ap - 1] - 1;
            c[nap] += p->H.d->data[ap - 1] * normP;
          }
        }
      }
    }
    for (i3 = 0; i3 < 120; i3++) {
      p->w[i3] = p->eta[i3] + beta * c[i3];
    }
    /*  Extrapolation */
    for (i3 = 0; i3 < 189; i3++) {
      p->xi[i3] = (1.0 - opts->rho) * p->xi[i3] + opts->rho * p->z[i3];
    }
    for (i3 = 0; i3 < 120; i3++) {
      p->eta[i3] = (1.0 - opts->rho) * p->eta[i3] + opts->rho * p->w[i3];
    }
    d = k;
    if (!(opts->check_iter == 0.0)) {
      if (rtIsNaN(opts->check_iter) || rtIsInf(k)) {
        d = rtNaN;
      } else if (rtIsInf(opts->check_iter)) {
        if (opts->check_iter < 0.0) {
          d = opts->check_iter;
        }
      } else {
        boolean_T rEQ0;
        d = fmod(k, opts->check_iter);
        rEQ0 = (d == 0.0);
        if ((!rEQ0) && (opts->check_iter > floor(opts->check_iter))) {
          normP = fabs(k / opts->check_iter);
          rEQ0 = !(fabs(normP - floor(normP + 0.5)) >
                   2.2204460492503131E-16 * normP);
        }
        if (rEQ0) {
          d = opts->check_iter * 0.0;
        } else if (opts->check_iter < 0.0) {
          d += opts->check_iter;
        }
      }
    }
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
      normP = 0.0;
      for (nap = 0; nap < 189; nap++) {
        norm2H = fabs(p->xi[nap]);
        if (rtIsNaN(norm2H) || (norm2H > normP)) {
          normP = norm2H;
        }
      }
      if (xiold->size[0] == 0) {
        sig_old = 0.0;
      } else {
        sig_old = 0.0;
        i3 = xiold->size[0];
        for (nap = 0; nap < i3; nap++) {
          norm2H = fabs(xiold_data[nap]);
          if (rtIsNaN(norm2H) || (norm2H > sig_old)) {
            sig_old = norm2H;
          }
        }
      }
      if (xiold->size[0] == 189) {
        for (i3 = 0; i3 < 189; i3++) {
          z[i3] = xiold_data[i3] - p->xi[i3];
        }
      } else {
        b_binary_expand_op(z, xiold, p);
      }
      iter = 0.0;
      for (nap = 0; nap < 189; nap++) {
        norm2H = fabs(z[nap]);
        if (rtIsNaN(norm2H) || (norm2H > iter)) {
          iter = norm2H;
        }
      }
      guard1 = false;
      if (iter <= opts->eps_abs + opts->eps_rel * fmax(normP, sig_old)) {
        normP = 0.0;
        for (nap = 0; nap < 120; nap++) {
          norm2H = fabs(p->eta[nap]);
          if (rtIsNaN(norm2H) || (norm2H > normP)) {
            normP = norm2H;
          }
        }
        if (etaold->size[0] == 0) {
          sig_old = 0.0;
        } else {
          sig_old = 0.0;
          i3 = etaold->size[0];
          for (nap = 0; nap < i3; nap++) {
            norm2H = fabs(etaold_data[nap]);
            if (rtIsNaN(norm2H) || (norm2H > sig_old)) {
              sig_old = norm2H;
            }
          }
        }
        if (etaold->size[0] == 120) {
          for (i3 = 0; i3 < 120; i3++) {
            c[i3] = etaold_data[i3] - p->eta[i3];
          }
        } else {
          binary_expand_op(c, etaold, p);
        }
        iter = 0.0;
        for (nap = 0; nap < 120; nap++) {
          norm2H = fabs(c[nap]);
          if (rtIsNaN(norm2H) || (norm2H > iter)) {
            iter = norm2H;
          }
        }
        if (iter <= opts->eps_abs + opts->eps_rel * fmax(normP, sig_old)) {
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
  emxFree_real_T(&t2_d);
  emxFree_uint8_T(&r);
  emxFree_real_T(&idx);
  emxFree_real_T(&etaold);
  emxFree_real_T(&xiold);
  memcpy(&Z[0], &p->xi[0], 189U * sizeof(double));
  *solve_time = toc() * 1000.0;
}

/* End of code generation (pipg_vec_solver.c) */
