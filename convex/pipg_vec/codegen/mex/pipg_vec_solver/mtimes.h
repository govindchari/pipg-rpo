/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.h
 *
 * Code generation for function 'mtimes'
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
void b_sparse_mtimes(const emxArray_real_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, const real_T b[189],
                     real_T c[189]);

void c_sparse_mtimes(const emxArray_real_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, const real_T b[120],
                     real_T c[189]);

void d_sparse_mtimes(const emxArray_real_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, const real_T b[189],
                     real_T c[120]);

void sparse_mtimes(const emxArray_real_T *a_d, const emxArray_int32_T *a_colidx,
                   const emxArray_int32_T *a_rowidx, const emxArray_real_T *b_d,
                   const emxArray_int32_T *b_colidx,
                   const emxArray_int32_T *b_rowidx, emxArray_real_T *c_d,
                   emxArray_int32_T *c_colidx, emxArray_int32_T *c_rowidx);

/* End of code generation (mtimes.h) */
