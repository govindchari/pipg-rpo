/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver_emxutil.h
 *
 * Code generation for function 'pipg_vec_solver_emxutil'
 *
 */

#ifndef PIPG_VEC_SOLVER_EMXUTIL_H
#define PIPG_VEC_SOLVER_EMXUTIL_H

/* Include files */
#include "pipg_vec_solver_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int oldNumel);

extern void emxFreeStruct_sparse(sparse *pStruct);

extern void emxFreeStruct_struct1_T(struct1_T *pStruct);

extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);

extern void emxInitStruct_sparse(sparse *pStruct);

extern void emxInitStruct_struct1_T(struct1_T *pStruct);

extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (pipg_vec_solver_emxutil.h) */
