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
#include "mod.h"
#include "mtimes.h"
#include "norm.h"
#include "pipg_vec_solver_data.h"
#include "pipg_vec_solver_emxutil.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "tic.h"
#include "toc.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = {
    17,                /* lineNo */
    "pipg_vec_solver", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo b_emlrtRSI = {
    28,                /* lineNo */
    "pipg_vec_solver", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo c_emlrtRSI = {
    33,                /* lineNo */
    "pipg_vec_solver", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo d_emlrtRSI = {
    36,                /* lineNo */
    "pipg_vec_solver", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo e_emlrtRSI = {
    62,                /* lineNo */
    "pipg_vec_solver", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo
    k_emlrtRSI =
        {
            3,                   /* lineNo */
            "compute_stepsizes", /* fcnName */
            "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/"
            "compute_stepsizes.m" /* pathName */
};

static emlrtRSInfo
    l_emlrtRSI =
        {
            4,                   /* lineNo */
            "compute_stepsizes", /* fcnName */
            "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/"
            "compute_stepsizes.m" /* pathName */
};

static emlrtRSInfo
    m_emlrtRSI =
        {
            5,                   /* lineNo */
            "compute_stepsizes", /* fcnName */
            "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/"
            "compute_stepsizes.m" /* pathName */
};

static emlrtRSInfo s_emlrtRSI = {
    15,    /* lineNo */
    "max", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/max.m" /* pathName
                                                                     */
};

static emlrtRSInfo t_emlrtRSI = {
    44,         /* lineNo */
    "minOrMax", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo u_emlrtRSI = {
    79,        /* lineNo */
    "maximum", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo v_emlrtRSI =
    {
        225,             /* lineNo */
        "unaryMinOrMax", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo w_emlrtRSI =
    {
        289,                     /* lineNo */
        "unaryMinOrMaxDispatch", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo x_emlrtRSI =
    {
        693,              /* lineNo */
        "minOrMaxSparse", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo y_emlrtRSI =
    {
        756,                          /* lineNo */
        "minOrMaxSparseColumnReduce", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo db_emlrtRSI = {
    9,                 /* lineNo */
    "power_iteration", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/power_iteration.m" /* pathName
                                                                           */
};

static emlrtRSInfo bc_emlrtRSI = {
    44,       /* lineNo */
    "mpower", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/matfun/mpower.m" /* pathName
                                                                       */
};

static emlrtRSInfo cc_emlrtRSI = {
    71,                                                           /* lineNo */
    "power",                                                      /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/ops/power.m" /* pathName */
};

static emlrtRSInfo dc_emlrtRSI = {
    9,                           /* lineNo */
    "pipg_vec_solver/project_D", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo ec_emlrtRSI = {
    10,                          /* lineNo */
    "pipg_vec_solver/project_D", /* fcnName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pathName
                                                                           */
};

static emlrtRSInfo fc_emlrtRSI = {
    28,                                                           /* lineNo */
    "colon",                                                      /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/ops/colon.m" /* pathName */
};

static emlrtRSInfo gc_emlrtRSI = {
    125,                                                          /* lineNo */
    "colon",                                                      /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/ops/colon.m" /* pathName */
};

static emlrtBCInfo emlrtBCI = {
    1,                           /* iFirst */
    189,                         /* iLast */
    13,                          /* lineNo */
    15,                          /* colNo */
    "z",                         /* aName */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    3 /* checkKind */
};

static emlrtDCInfo emlrtDCI = {
    13,                          /* lineNo */
    15,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = {
    1,                           /* iFirst */
    189,                         /* iLast */
    12,                          /* lineNo */
    15,                          /* colNo */
    "z",                         /* aName */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    3 /* checkKind */
};

static emlrtDCInfo b_emlrtDCI = {
    12,                          /* lineNo */
    15,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtDCInfo c_emlrtDCI = {
    22,                /* lineNo */
    20,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    4 /* checkKind */
};

static emlrtDCInfo d_emlrtDCI = {
    22,                /* lineNo */
    20,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtDCInfo e_emlrtDCI = {
    21,                /* lineNo */
    19,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    4 /* checkKind */
};

static emlrtDCInfo f_emlrtDCI = {
    21,                /* lineNo */
    19,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtECInfo emlrtECI = {
    -1,                          /* nDims */
    13,                          /* lineNo */
    13,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtECInfo b_emlrtECI = {
    -1,                          /* nDims */
    12,                          /* lineNo */
    13,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtECInfo c_emlrtECI = {
    -1,                          /* nDims */
    4,                           /* lineNo */
    9,                           /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtBCInfo c_emlrtBCI = {
    1,                           /* iFirst */
    189,                         /* iLast */
    4,                           /* lineNo */
    41,                          /* colNo */
    "z",                         /* aName */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    0 /* checkKind */
};

static emlrtDCInfo g_emlrtDCI = {
    4,                           /* lineNo */
    41,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtBCInfo d_emlrtBCI = {
    1,                           /* iFirst */
    189,                         /* iLast */
    4,                           /* lineNo */
    11,                          /* colNo */
    "z",                         /* aName */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    0 /* checkKind */
};

static emlrtDCInfo h_emlrtDCI = {
    4,                           /* lineNo */
    11,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtECInfo d_emlrtECI = {
    -1,                          /* nDims */
    3,                           /* lineNo */
    9,                           /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtBCInfo e_emlrtBCI = {
    1,                           /* iFirst */
    189,                         /* iLast */
    3,                           /* lineNo */
    13,                          /* colNo */
    "z",                         /* aName */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    0 /* checkKind */
};

static emlrtDCInfo i_emlrtDCI = {
    3,                           /* lineNo */
    13,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m", /* pName
                                                                            */
    1 /* checkKind */
};

static emlrtRTEInfo emlrtRTEI = {
    8,                           /* lineNo */
    17,                          /* colNo */
    "pipg_vec_solver/project_D", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtECInfo e_emlrtECI = {
    1,                 /* nDims */
    52,                /* lineNo */
    19,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtECInfo f_emlrtECI = {
    1,                 /* nDims */
    51,                /* lineNo */
    27,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo h_emlrtRTEI = {
    13,                                                            /* lineNo */
    9,                                                             /* colNo */
    "sqrt",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elfun/sqrt.m" /* pName */
};

static emlrtRTEInfo j_emlrtRTEI = {
    21,                /* lineNo */
    19,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo k_emlrtRTEI = {
    22,                /* lineNo */
    20,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo l_emlrtRTEI = {
    9,                 /* lineNo */
    13,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo m_emlrtRTEI = {
    56,                /* lineNo */
    13,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo n_emlrtRTEI = {
    10,                /* lineNo */
    13,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo o_emlrtRTEI = {
    57,                /* lineNo */
    13,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo p_emlrtRTEI = {
    12,                /* lineNo */
    15,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo q_emlrtRTEI = {
    12,                /* lineNo */
    34,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo r_emlrtRTEI = {
    13,                /* lineNo */
    15,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo s_emlrtRTEI = {
    13,                /* lineNo */
    34,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo t_emlrtRTEI = {
    21,                /* lineNo */
    5,                 /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo u_emlrtRTEI = {
    22,                /* lineNo */
    5,                 /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

static emlrtRTEInfo
    v_emlrtRTEI =
        {
            3,                   /* lineNo */
            22,                  /* colNo */
            "compute_stepsizes", /* fName */
            "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/"
            "compute_stepsizes.m" /* pName */
};

static emlrtRTEInfo w_emlrtRTEI = {
    1,                 /* lineNo */
    49,                /* colNo */
    "pipg_vec_solver", /* fName */
    "/home/govind/Desktop/git/pipg-rpo/convex/pipg_vec/pipg_vec_solver.m" /* pName
                                                                           */
};

/* Function Declarations */
static void b_binary_expand_op(real_T in1[189], const emxArray_real_T *in2,
                               const struct1_T *in3);

static void binary_expand_op(real_T in1[120], const emxArray_real_T *in2,
                             const struct1_T *in3);

/* Function Definitions */
static void b_binary_expand_op(real_T in1[189], const emxArray_real_T *in2,
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

static void binary_expand_op(real_T in1[120], const emxArray_real_T *in2,
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

void pipg_vec_solver(const emlrtStack *sp, const struct0_T *par, struct1_T *p,
                     const struct2_T *opts, real_T Z[189], real_T *solve_time)
{
  ptrdiff_t incx_t;
  ptrdiff_t n_t;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack st;
  emxArray_int32_T *varargin_1_colidx;
  emxArray_int32_T *varargin_1_rowidx;
  emxArray_real_T *etaold;
  emxArray_real_T *idx_u;
  emxArray_real_T *idx_v;
  emxArray_real_T *varargin_1_d;
  emxArray_real_T *xiold;
  emxArray_uint8_T *r;
  real_T b[189];
  real_T z[189];
  real_T alpha;
  real_T beta;
  real_T d;
  real_T d1;
  real_T fullEx;
  real_T iter;
  real_T k;
  real_T normP;
  real_T sig_old;
  real_T *etaold_data;
  real_T *idx_u_data;
  real_T *idx_v_data;
  real_T *varargin_1_d_data;
  real_T *xiold_data;
  int32_T b_i;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T ncol;
  int32_T xend;
  int32_T *varargin_1_colidx_data;
  uint8_T *r1;
  boolean_T stop;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  st.site = &emlrtRSI;
  tic(&st);
  stop = false;
  /*      fprintf("iter     objv     |Gx-g|\n") */
  /*      fprintf("-----------------------------\n") */
  emxInit_real_T(sp, &xiold, 1, &t_emlrtRTEI);
  d = par->N * (par->nx + par->nu);
  if (!(d >= 0.0)) {
    emlrtNonNegativeCheckR2012b(d, &e_emlrtDCI, (emlrtConstCTX)sp);
  }
  d1 = (int32_T)muDoubleScalarFloor(d);
  if (d != d1) {
    emlrtIntegerCheckR2012b(d, &f_emlrtDCI, (emlrtConstCTX)sp);
  }
  i = xiold->size[0];
  xend = (int32_T)d;
  xiold->size[0] = (int32_T)d;
  emxEnsureCapacity_real_T(sp, xiold, i, &j_emlrtRTEI);
  xiold_data = xiold->data;
  if (d != d1) {
    emlrtIntegerCheckR2012b(d, &f_emlrtDCI, (emlrtConstCTX)sp);
  }
  for (i = 0; i < xend; i++) {
    xiold_data[i] = 1.0;
  }
  xend = xiold->size[0];
  for (i = 0; i < xend; i++) {
    xiold_data[i] *= 1.0E+6;
  }
  emxInit_real_T(sp, &etaold, 1, &u_emlrtRTEI);
  d = (par->N - 1.0) * par->nx;
  if (!(d >= 0.0)) {
    emlrtNonNegativeCheckR2012b(d, &c_emlrtDCI, (emlrtConstCTX)sp);
  }
  d1 = (int32_T)muDoubleScalarFloor(d);
  if (d != d1) {
    emlrtIntegerCheckR2012b(d, &d_emlrtDCI, (emlrtConstCTX)sp);
  }
  i = etaold->size[0];
  xend = (int32_T)d;
  etaold->size[0] = (int32_T)d;
  emxEnsureCapacity_real_T(sp, etaold, i, &k_emlrtRTEI);
  etaold_data = etaold->data;
  if (d != d1) {
    emlrtIntegerCheckR2012b(d, &d_emlrtDCI, (emlrtConstCTX)sp);
  }
  for (i = 0; i < xend; i++) {
    etaold_data[i] = 1.0;
  }
  xend = etaold->size[0];
  for (i = 0; i < xend; i++) {
    etaold_data[i] *= 1.0E+6;
  }
  k = 1.0;
  st.site = &b_emlrtRSI;
  /*  Assumes P is diagonal */
  b_st.site = &k_emlrtRSI;
  emxInit_real_T(&b_st, &varargin_1_d, 1, &v_emlrtRTEI);
  emxInit_int32_T(&b_st, &varargin_1_colidx, &v_emlrtRTEI);
  emxInit_int32_T(&b_st, &varargin_1_rowidx, &v_emlrtRTEI);
  c_st.site = &k_emlrtRSI;
  sparse_diag(&c_st, p->P.d, p->P.colidx, p->P.rowidx, varargin_1_d,
              varargin_1_colidx, varargin_1_rowidx);
  varargin_1_colidx_data = varargin_1_colidx->data;
  varargin_1_d_data = varargin_1_d->data;
  c_st.site = &s_emlrtRSI;
  d_st.site = &t_emlrtRSI;
  e_st.site = &u_emlrtRSI;
  f_st.site = &v_emlrtRSI;
  g_st.site = &w_emlrtRSI;
  h_st.site = &x_emlrtRSI;
  fullEx = 0.0;
  xend = varargin_1_colidx_data[1] - 1;
  ncol = varargin_1_colidx_data[1] - varargin_1_colidx_data[0];
  if (ncol != 0) {
    sig_old = 0.0;
    if (varargin_1_colidx_data[1] - 1 >= varargin_1_colidx_data[0]) {
      sig_old = varargin_1_d_data[varargin_1_colidx_data[0] - 1];
      i = varargin_1_colidx_data[0] + 1;
      for (b_i = i; b_i <= xend; b_i++) {
        boolean_T b_p;
        d1 = varargin_1_d_data[b_i - 1];
        if (muDoubleScalarIsNaN(d1)) {
          b_p = false;
        } else if (muDoubleScalarIsNaN(sig_old)) {
          b_p = true;
        } else {
          b_p = (sig_old < d1);
        }
        if (b_p) {
          sig_old = d1;
        }
      }
    }
    if (ncol < 1) {
      if ((!muDoubleScalarIsNaN(sig_old)) && (sig_old > 0.0)) {
        fullEx = sig_old;
      }
    } else {
      fullEx = sig_old;
    }
  }
  i_st.site = &y_emlrtRSI;
  sparse(&i_st, fullEx, varargin_1_d, varargin_1_colidx, varargin_1_rowidx);
  b_st.site = &k_emlrtRSI;
  normP = sparse_full(&b_st, varargin_1_d, varargin_1_colidx);
  b_st.site = &l_emlrtRSI;
  for (b_i = 0; b_i < 189; b_i++) {
    z[b_i] = 0.072739296745330792;
  }
  fullEx = 0.0;
  sig_old = 1.0E+6;
  iter = 1.0;
  while ((muDoubleScalarAbs(fullEx - sig_old) >=
          opts->eps_abs_pow +
              opts->eps_rel_pow * muDoubleScalarMax(fullEx, sig_old)) &&
         (iter < opts->max_iter_pow)) {
    sig_old = fullEx;
    c_st.site = &db_emlrtRSI;
    sparse_mtimes(&c_st, p->Ht.d, p->Ht.colidx, p->Ht.rowidx, p->H.d,
                  p->H.colidx, p->H.rowidx, varargin_1_d, varargin_1_colidx,
                  varargin_1_rowidx);
    memcpy(&b[0], &z[0], 189U * sizeof(real_T));
    c_st.site = &db_emlrtRSI;
    b_sparse_mtimes(&c_st, varargin_1_d, varargin_1_colidx, varargin_1_rowidx,
                    b, z);
    fullEx = b_norm(z);
    for (i = 0; i < 189; i++) {
      z[i] /= fullEx;
    }
    iter++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(&b_st);
    }
  }
  emxFree_int32_T(&b_st, &varargin_1_rowidx);
  emxFree_int32_T(&b_st, &varargin_1_colidx);
  fullEx *= opts->eps_buff + 1.0;
  b_st.site = &m_emlrtRSI;
  c_st.site = &bc_emlrtRSI;
  d_st.site = &cc_emlrtRSI;
  d1 = normP * normP + 4.0 * opts->omega * fullEx;
  b_st.site = &m_emlrtRSI;
  if (d1 < 0.0) {
    emlrtErrorWithMessageIdR2018a(
        &b_st, &h_emlrtRTEI, "Coder:toolbox:ElFunDomainError",
        "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
  }
  d1 = muDoubleScalarSqrt(d1);
  alpha = 2.0 / (d1 + normP);
  beta = opts->omega * alpha;
  if (par->nx < 1.0) {
    i = 0;
  } else {
    if (par->nx != (int32_T)muDoubleScalarFloor(par->nx)) {
      emlrtIntegerCheckR2012b(par->nx, &i_emlrtDCI, (emlrtConstCTX)sp);
    }
    if (((int32_T)par->nx < 1) || ((int32_T)par->nx > 189)) {
      emlrtDynamicBoundsCheckR2012b((int32_T)par->nx, 1, 189, &e_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    i = (int32_T)par->nx;
  }
  d1 = par->N * par->nx;
  if (d + 1.0 > d1) {
    i1 = 0;
    i2 = 0;
  } else {
    if (d + 1.0 != (int32_T)muDoubleScalarFloor(d + 1.0)) {
      emlrtIntegerCheckR2012b(d + 1.0, &h_emlrtDCI, (emlrtConstCTX)sp);
    }
    if (((int32_T)(d + 1.0) < 1) || ((int32_T)(d + 1.0) > 189)) {
      emlrtDynamicBoundsCheckR2012b((int32_T)(d + 1.0), 1, 189, &d_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    i1 = (int32_T)(d + 1.0) - 1;
    if (d1 != (int32_T)muDoubleScalarFloor(d1)) {
      emlrtIntegerCheckR2012b(d1, &g_emlrtDCI, (emlrtConstCTX)sp);
    }
    if (((int32_T)d1 < 1) || ((int32_T)d1 > 189)) {
      emlrtDynamicBoundsCheckR2012b((int32_T)d1, 1, 189, &c_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    i2 = (int32_T)d1;
  }
  i3 = (int32_T)par->N;
  emxInit_real_T(sp, &idx_u, 2, &l_emlrtRTEI);
  idx_u_data = idx_u->data;
  emxInit_real_T(sp, &idx_v, 2, &n_emlrtRTEI);
  idx_v_data = idx_v->data;
  emxInit_uint8_T(sp, &r, &w_emlrtRTEI);
  while (!stop) {
    real_T b_b[120];
    /*  Primal Update */
    st.site = &c_emlrtRSI;
    b_sparse_mtimes(&st, p->P.d, p->P.colidx, p->P.rowidx, p->xi, b);
    st.site = &c_emlrtRSI;
    c_sparse_mtimes(&st, p->Ht.d, p->Ht.colidx, p->Ht.rowidx, p->eta, z);
    for (i4 = 0; i4 < 189; i4++) {
      b[i4] += z[i4];
    }
    st.site = &c_emlrtRSI;
    iter = p->umax;
    normP = p->vmax;
    for (i4 = 0; i4 < 189; i4++) {
      p->z[i4] = p->xi[i4] - alpha * b[i4];
    }
    if (i != 6) {
      emlrtSubAssignSizeCheck1dR2017a(i, 6, &d_emlrtECI, &st);
    }
    for (i4 = 0; i4 < 6; i4++) {
      p->z[i4] = par->x0s[i4];
    }
    xend = i2 - i1;
    if (xend != 6) {
      emlrtSubAssignSizeCheck1dR2017a(xend, 6, &c_emlrtECI, &st);
    }
    for (i4 = 0; i4 < 6; i4++) {
      p->z[i1 + i4] = par->xNs[i4];
    }
    /*  State and Control Constraints */
    emlrtForLoopVectorCheckR2021a(1.0, 1.0, par->N, mxDOUBLE_CLASS,
                                  (int32_T)par->N, &emlrtRTEI, &st);
    for (b_i = 0; b_i < i3; b_i++) {
      b_st.site = &dc_emlrtRSI;
      fullEx = (d1 + (((real_T)b_i + 1.0) - 1.0) * par->nu) + 1.0;
      sig_old = d1 + ((real_T)b_i + 1.0) * par->nu;
      c_st.site = &fc_emlrtRSI;
      if (muDoubleScalarIsNaN(fullEx) || muDoubleScalarIsNaN(sig_old)) {
        i4 = idx_u->size[0] * idx_u->size[1];
        idx_u->size[0] = 1;
        idx_u->size[1] = 1;
        emxEnsureCapacity_real_T(&c_st, idx_u, i4, &l_emlrtRTEI);
        idx_u_data = idx_u->data;
        idx_u_data[0] = rtNaN;
      } else if (sig_old < fullEx) {
        idx_u->size[0] = 1;
        idx_u->size[1] = 0;
      } else if ((muDoubleScalarIsInf(fullEx) ||
                  muDoubleScalarIsInf(sig_old)) &&
                 (fullEx == sig_old)) {
        i4 = idx_u->size[0] * idx_u->size[1];
        idx_u->size[0] = 1;
        idx_u->size[1] = 1;
        emxEnsureCapacity_real_T(&c_st, idx_u, i4, &l_emlrtRTEI);
        idx_u_data = idx_u->data;
        idx_u_data[0] = rtNaN;
      } else if (muDoubleScalarFloor(fullEx) == fullEx) {
        i4 = idx_u->size[0] * idx_u->size[1];
        idx_u->size[0] = 1;
        xend = (int32_T)(sig_old - fullEx);
        idx_u->size[1] = xend + 1;
        emxEnsureCapacity_real_T(&c_st, idx_u, i4, &l_emlrtRTEI);
        idx_u_data = idx_u->data;
        for (i4 = 0; i4 <= xend; i4++) {
          idx_u_data[i4] = fullEx + (real_T)i4;
        }
      } else {
        d_st.site = &gc_emlrtRSI;
        eml_float_colon(&d_st, fullEx, sig_old, idx_u);
        idx_u_data = idx_u->data;
      }
      b_st.site = &ec_emlrtRSI;
      fullEx = (((real_T)b_i + 1.0) - 1.0) * par->nx + 4.0;
      sig_old = ((real_T)b_i + 1.0) * par->nx;
      c_st.site = &fc_emlrtRSI;
      if (muDoubleScalarIsNaN(fullEx) || muDoubleScalarIsNaN(sig_old)) {
        i4 = idx_v->size[0] * idx_v->size[1];
        idx_v->size[0] = 1;
        idx_v->size[1] = 1;
        emxEnsureCapacity_real_T(&c_st, idx_v, i4, &n_emlrtRTEI);
        idx_v_data = idx_v->data;
        idx_v_data[0] = rtNaN;
      } else if (sig_old < fullEx) {
        idx_v->size[0] = 1;
        idx_v->size[1] = 0;
      } else if ((muDoubleScalarIsInf(fullEx) ||
                  muDoubleScalarIsInf(sig_old)) &&
                 (fullEx == sig_old)) {
        i4 = idx_v->size[0] * idx_v->size[1];
        idx_v->size[0] = 1;
        idx_v->size[1] = 1;
        emxEnsureCapacity_real_T(&c_st, idx_v, i4, &n_emlrtRTEI);
        idx_v_data = idx_v->data;
        idx_v_data[0] = rtNaN;
      } else if (muDoubleScalarFloor(fullEx) == fullEx) {
        i4 = idx_v->size[0] * idx_v->size[1];
        idx_v->size[0] = 1;
        xend = (int32_T)(sig_old - fullEx);
        idx_v->size[1] = xend + 1;
        emxEnsureCapacity_real_T(&c_st, idx_v, i4, &n_emlrtRTEI);
        idx_v_data = idx_v->data;
        for (i4 = 0; i4 <= xend; i4++) {
          idx_v_data[i4] = fullEx + (real_T)i4;
        }
      } else {
        d_st.site = &gc_emlrtRSI;
        eml_float_colon(&d_st, fullEx, sig_old, idx_v);
        idx_v_data = idx_v->data;
      }
      i4 = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = idx_u->size[1];
      emxEnsureCapacity_uint8_T(&st, r, i4, &p_emlrtRTEI);
      r1 = r->data;
      xend = idx_u->size[1];
      for (i4 = 0; i4 < xend; i4++) {
        if (idx_u_data[i4] != (int32_T)muDoubleScalarFloor(idx_u_data[i4])) {
          emlrtIntegerCheckR2012b(idx_u_data[i4], &b_emlrtDCI, &st);
        }
        ncol = (uint8_T)idx_u_data[i4];
        if ((ncol < 1) || (ncol > 189)) {
          emlrtDynamicBoundsCheckR2012b(ncol, 1, 189, &b_emlrtBCI, &st);
        }
        r1[i4] = (uint8_T)ncol;
      }
      i4 = varargin_1_d->size[0];
      varargin_1_d->size[0] = idx_u->size[1];
      emxEnsureCapacity_real_T(&st, varargin_1_d, i4, &q_emlrtRTEI);
      varargin_1_d_data = varargin_1_d->data;
      xend = idx_u->size[1];
      for (i4 = 0; i4 < xend; i4++) {
        varargin_1_d_data[i4] = p->z[(int32_T)idx_u_data[i4] - 1];
      }
      if (idx_u->size[1] == 0) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)idx_u->size[1];
        incx_t = (ptrdiff_t)1;
        d = dnrm2(&n_t, &varargin_1_d_data[0], &incx_t);
      }
      if (d > iter) {
        fullEx = iter / d;
        xend = varargin_1_d->size[0];
        for (i4 = 0; i4 < xend; i4++) {
          varargin_1_d_data[i4] *= fullEx;
        }
      }
      if (varargin_1_d->size[0] != r->size[1]) {
        emlrtSubAssignSizeCheck1dR2017a(r->size[1], varargin_1_d->size[0],
                                        &b_emlrtECI, &st);
      }
      xend = r->size[1];
      for (i4 = 0; i4 < xend; i4++) {
        p->z[r1[i4] - 1] = varargin_1_d_data[i4];
      }
      i4 = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = idx_v->size[1];
      emxEnsureCapacity_uint8_T(&st, r, i4, &r_emlrtRTEI);
      r1 = r->data;
      xend = idx_v->size[1];
      for (i4 = 0; i4 < xend; i4++) {
        if (idx_v_data[i4] != (int32_T)muDoubleScalarFloor(idx_v_data[i4])) {
          emlrtIntegerCheckR2012b(idx_v_data[i4], &emlrtDCI, &st);
        }
        ncol = (uint8_T)idx_v_data[i4];
        if ((ncol < 1) || (ncol > 189)) {
          emlrtDynamicBoundsCheckR2012b(ncol, 1, 189, &emlrtBCI, &st);
        }
        r1[i4] = (uint8_T)ncol;
      }
      i4 = varargin_1_d->size[0];
      varargin_1_d->size[0] = idx_v->size[1];
      emxEnsureCapacity_real_T(&st, varargin_1_d, i4, &s_emlrtRTEI);
      varargin_1_d_data = varargin_1_d->data;
      xend = idx_v->size[1];
      for (i4 = 0; i4 < xend; i4++) {
        varargin_1_d_data[i4] = p->z[(int32_T)idx_v_data[i4] - 1];
      }
      if (idx_v->size[1] == 0) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)idx_v->size[1];
        incx_t = (ptrdiff_t)1;
        d = dnrm2(&n_t, &varargin_1_d_data[0], &incx_t);
      }
      if (d > normP) {
        fullEx = normP / d;
        xend = varargin_1_d->size[0];
        for (i4 = 0; i4 < xend; i4++) {
          varargin_1_d_data[i4] *= fullEx;
        }
      }
      if (varargin_1_d->size[0] != r->size[1]) {
        emlrtSubAssignSizeCheck1dR2017a(r->size[1], varargin_1_d->size[0],
                                        &emlrtECI, &st);
      }
      xend = r->size[1];
      for (i4 = 0; i4 < xend; i4++) {
        p->z[r1[i4] - 1] = varargin_1_d_data[i4];
      }
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(&st);
      }
    }
    /*  Dual Update */
    for (i4 = 0; i4 < 189; i4++) {
      b[i4] = 2.0 * p->z[i4] - p->xi[i4];
    }
    st.site = &d_emlrtRSI;
    d_sparse_mtimes(&st, p->H.d, p->H.colidx, p->H.rowidx, b, b_b);
    for (i4 = 0; i4 < 120; i4++) {
      p->w[i4] = p->eta[i4] + beta * b_b[i4];
    }
    /*  Extrapolation */
    for (i4 = 0; i4 < 189; i4++) {
      p->xi[i4] = (1.0 - opts->rho) * p->xi[i4] + opts->rho * p->z[i4];
    }
    for (i4 = 0; i4 < 120; i4++) {
      p->eta[i4] = (1.0 - opts->rho) * p->eta[i4] + opts->rho * p->w[i4];
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
      if ((xiold->size[0] != 189) && (xiold->size[0] != 1)) {
        emlrtDimSizeImpxCheckR2021b(xiold->size[0], 189, &f_emlrtECI,
                                    (emlrtConstCTX)sp);
      }
      fullEx = 0.0;
      for (b_i = 0; b_i < 189; b_i++) {
        sig_old = muDoubleScalarAbs(p->xi[b_i]);
        if (muDoubleScalarIsNaN(sig_old) || (sig_old > fullEx)) {
          fullEx = sig_old;
        }
      }
      if (xiold->size[0] == 0) {
        iter = 0.0;
      } else {
        iter = 0.0;
        i4 = xiold->size[0];
        for (b_i = 0; b_i < i4; b_i++) {
          sig_old = muDoubleScalarAbs(xiold_data[b_i]);
          if (muDoubleScalarIsNaN(sig_old) || (sig_old > iter)) {
            iter = sig_old;
          }
        }
      }
      if (xiold->size[0] == 189) {
        for (i4 = 0; i4 < 189; i4++) {
          z[i4] = xiold_data[i4] - p->xi[i4];
        }
      } else {
        b_binary_expand_op(z, xiold, p);
      }
      normP = 0.0;
      for (b_i = 0; b_i < 189; b_i++) {
        sig_old = muDoubleScalarAbs(z[b_i]);
        if (muDoubleScalarIsNaN(sig_old) || (sig_old > normP)) {
          normP = sig_old;
        }
      }
      guard1 = false;
      if (normP <=
          opts->eps_abs + opts->eps_rel * muDoubleScalarMax(fullEx, iter)) {
        if ((etaold->size[0] != 120) && (etaold->size[0] != 1)) {
          emlrtDimSizeImpxCheckR2021b(etaold->size[0], 120, &e_emlrtECI,
                                      (emlrtConstCTX)sp);
        }
        fullEx = 0.0;
        for (b_i = 0; b_i < 120; b_i++) {
          sig_old = muDoubleScalarAbs(p->eta[b_i]);
          if (muDoubleScalarIsNaN(sig_old) || (sig_old > fullEx)) {
            fullEx = sig_old;
          }
        }
        if (etaold->size[0] == 0) {
          iter = 0.0;
        } else {
          iter = 0.0;
          i4 = etaold->size[0];
          for (b_i = 0; b_i < i4; b_i++) {
            sig_old = muDoubleScalarAbs(etaold_data[b_i]);
            if (muDoubleScalarIsNaN(sig_old) || (sig_old > iter)) {
              iter = sig_old;
            }
          }
        }
        if (etaold->size[0] == 120) {
          for (i4 = 0; i4 < 120; i4++) {
            b_b[i4] = etaold_data[i4] - p->eta[i4];
          }
        } else {
          binary_expand_op(b_b, etaold, p);
        }
        normP = 0.0;
        for (b_i = 0; b_i < 120; b_i++) {
          sig_old = muDoubleScalarAbs(b_b[b_i]);
          if (muDoubleScalarIsNaN(sig_old) || (sig_old > normP)) {
            normP = sig_old;
          }
        }
        if (normP <=
            opts->eps_abs + opts->eps_rel * muDoubleScalarMax(fullEx, iter)) {
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
      i4 = xiold->size[0];
      xiold->size[0] = 189;
      emxEnsureCapacity_real_T(sp, xiold, i4, &m_emlrtRTEI);
      xiold_data = xiold->data;
      for (i4 = 0; i4 < 189; i4++) {
        xiold_data[i4] = p->xi[i4];
      }
      i4 = etaold->size[0];
      etaold->size[0] = 120;
      emxEnsureCapacity_real_T(sp, etaold, i4, &o_emlrtRTEI);
      etaold_data = etaold->data;
      for (i4 = 0; i4 < 120; i4++) {
        etaold_data[i4] = p->eta[i4];
      }
    }
    k++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  emxFree_uint8_T(sp, &r);
  emxFree_real_T(sp, &idx_v);
  emxFree_real_T(sp, &idx_u);
  emxFree_real_T(sp, &varargin_1_d);
  emxFree_real_T(sp, &etaold);
  emxFree_real_T(sp, &xiold);
  memcpy(&Z[0], &p->xi[0], 189U * sizeof(real_T));
  st.site = &e_emlrtRSI;
  *solve_time = toc(&st) * 1000.0;
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

/* End of code generation (pipg_vec_solver.c) */
