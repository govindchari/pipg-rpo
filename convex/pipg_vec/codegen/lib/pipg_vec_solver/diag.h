/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * diag.h
 *
 * Code generation for function 'diag'
 *
 */

#ifndef DIAG_H
#define DIAG_H

/* Include files */
#include "pipg_vec_solver_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void sparse_diag(const emxArray_real_T *this_d,
                 const emxArray_int32_T *this_colidx,
                 const emxArray_int32_T *this_rowidx, emxArray_real_T *y_d,
                 emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (diag.h) */
