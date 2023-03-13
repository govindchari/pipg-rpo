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

#pragma once

/* Include files */
#include "pipg_vec_solver_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int32_T oldNumel);

void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel);

void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int32_T oldNumel);

void emxFreeStruct_sparse(b_sparse *pStruct);

void emxFreeStruct_struct1_T(struct1_T *pStruct);

void emxFree_int32_T(emxArray_int32_T **pEmxArray);

void emxFree_real_T(emxArray_real_T **pEmxArray);

void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);

void emxInitStruct_sparse(b_sparse *pStruct);

void emxInitStruct_struct1_T(struct1_T *pStruct);

void emxInit_int32_T(emxArray_int32_T **pEmxArray);

void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);

void emxInit_uint8_T(emxArray_uint8_T **pEmxArray);

/* End of code generation (pipg_vec_solver_emxutil.h) */
