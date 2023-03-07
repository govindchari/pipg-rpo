/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver_emxAPI.h
 *
 * Code generation for function 'pipg_vec_solver_emxAPI'
 *
 */

#ifndef PIPG_VEC_SOLVER_EMXAPI_H
#define PIPG_VEC_SOLVER_EMXAPI_H

/* Include files */
#include "pipg_vec_solver_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern emxArray_int32_T *emxCreateND_int32_T(int numDimensions,
                                             const int *size);

extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);

extern emxArray_int32_T *
emxCreateWrapperND_int32_T(int *data, int numDimensions, const int *size);

extern emxArray_real_T *
emxCreateWrapperND_real_T(double *data, int numDimensions, const int *size);

extern emxArray_int32_T *emxCreateWrapper_int32_T(int *data, int rows,
                                                  int cols);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows,
                                                int cols);

extern emxArray_int32_T *emxCreate_int32_T(int rows, int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_int32_T(emxArray_int32_T *emxArray);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxDestroy_struct1_T(struct1_T emxArray);

extern void emxInit_struct1_T(struct1_T *pStruct);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (pipg_vec_solver_emxAPI.h) */
