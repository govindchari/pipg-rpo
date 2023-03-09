/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver_types.h
 *
 * Code generation for function 'pipg_vec_solver'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"

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
  real_T th_ac;
  real_T umax;
  real_T vmax;
  real_T A[36];
  real_T B[18];
  real_T Q[36];
  real_T R[9];
  real_T Px[36];
  real_T Pu[9];
  real_T x0s[6];
  real_T xNs[6];
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

#ifndef typedef_b_sparse
#define typedef_b_sparse
typedef struct {
  emxArray_real_T *d;
  emxArray_int32_T *colidx;
  emxArray_int32_T *rowidx;
} b_sparse;
#endif /* typedef_b_sparse */

#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct {
  real_T umax;
  real_T vmax;
  b_sparse P;
  b_sparse H;
  b_sparse Ht;
  real_T z[189];
  real_T w[120];
  real_T xi[189];
  real_T eta[120];
} struct1_T;
#endif /* typedef_struct1_T */

#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T
struct emxArray_uint8_T {
  uint8_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_uint8_T */
#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T
typedef struct emxArray_uint8_T emxArray_uint8_T;
#endif /* typedef_emxArray_uint8_T */

/* End of code generation (pipg_vec_solver_types.h) */
