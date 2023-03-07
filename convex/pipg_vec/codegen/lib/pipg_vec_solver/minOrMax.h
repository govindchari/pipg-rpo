/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * minOrMax.h
 *
 * Code generation for function 'minOrMax'
 *
 */

#ifndef MINORMAX_H
#define MINORMAX_H

/* Include files */
#include "pipg_vec_solver_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void maximum(const emxArray_real_T *x_d, const emxArray_int32_T *x_colidx,
             emxArray_real_T *ex_d, emxArray_int32_T *ex_colidx,
             emxArray_int32_T *ex_rowidx);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (minOrMax.h) */
