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

#ifndef PIPG_VEC_SOLVER_TYPES_H
#define PIPG_VEC_SOLVER_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct2_T
#define typedef_struct2_T
typedef struct {
  double omega;
  double rho;
  double check_iter;
  double eps_rel;
  double eps_abs;
  double max_iter;
  double eps_rel_pow;
  double eps_abs_pow;
  double eps_buff;
  double max_iter_pow;
} struct2_T;
#endif /* typedef_struct2_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  double nx;
  double nu;
  double dt;
  double T;
  double N;
  double n;
  double x0[6];
  double xN[6];
  double leading;
  double Px[36];
  double Pu[9];
  double x0s[6];
  double xNs[6];
  double th_ac;
  double umax;
  double A[36];
  double B[18];
  double Q[36];
  double R[9];
} struct0_T;
#endif /* typedef_struct0_T */

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
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
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
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
  double umax;
  sparse P;
  sparse H;
  sparse Ht;
  double z[189];
  double w[120];
  double xi[189];
  double eta[120];
} struct1_T;
#endif /* typedef_struct1_T */

#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T
struct emxArray_uint8_T {
  unsigned char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_uint8_T */
#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T
typedef struct emxArray_uint8_T emxArray_uint8_T;
#endif /* typedef_emxArray_uint8_T */

#endif
/* End of code generation (pipg_vec_solver_types.h) */
