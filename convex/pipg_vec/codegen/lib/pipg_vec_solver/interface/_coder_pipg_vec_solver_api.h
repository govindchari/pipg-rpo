/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_pipg_vec_solver_api.h
 *
 * Code generation for function 'pipg_vec_solver'
 *
 */

#ifndef _CODER_PIPG_VEC_SOLVER_API_H
#define _CODER_PIPG_VEC_SOLVER_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_struct2_T
#define typedef_struct2_T
typedef struct {
  real_T omega;
  real_T rho;
  real_T check_iter;
  real_T eps_rel;
  real_T eps_abs;
  real_T max_iter;
  real_T eps_rel_pow;
  real_T eps_abs_pow;
  real_T eps_buff;
  real_T max_iter_pow;
} struct2_T;
#endif /* typedef_struct2_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  real_T nx;
  real_T nu;
  real_T dt;
  real_T T;
  real_T N;
  real_T n;
  real_T x0[6];
  real_T xN[6];
  real_T leading;
  real_T Px[36];
  real_T Pu[9];
  real_T x0s[6];
  real_T xNs[6];
  real_T th_ac;
  real_T umax;
  real_T A[36];
  real_T B[18];
  real_T Q[36];
  real_T R[9];
} struct0_T;
#endif /* typedef_struct0_T */

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T {
  int32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_int32_T */
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /* typedef_emxArray_int32_T */

#ifndef typedef_sparse
#define typedef_sparse
typedef struct {
  emxArray_real_T *d;
  emxArray_int32_T *colidx;
  emxArray_int32_T *rowidx;
} sparse;
#endif /* typedef_sparse */

#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct {
  real_T umax;
  sparse P;
  sparse H;
  sparse Ht;
  real_T z[189];
  real_T w[120];
  real_T xi[189];
  real_T eta[120];
} struct1_T;
#endif /* typedef_struct1_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void pipg_vec_solver(struct0_T *par, struct1_T *p, struct2_T *opts,
                     real_T Z[189], real_T *solve_time);

void pipg_vec_solver_api(const mxArray *const prhs[3], int32_T nlhs,
                         const mxArray *plhs[4]);

void pipg_vec_solver_atexit(void);

void pipg_vec_solver_initialize(void);

void pipg_vec_solver_terminate(void);

void pipg_vec_solver_xil_shutdown(void);

void pipg_vec_solver_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_pipg_vec_solver_api.h) */
