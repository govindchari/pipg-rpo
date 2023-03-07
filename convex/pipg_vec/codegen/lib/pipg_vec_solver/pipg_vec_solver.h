/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver.h
 *
 * Code generation for function 'pipg_vec_solver'
 *
 */

#ifndef PIPG_VEC_SOLVER_H
#define PIPG_VEC_SOLVER_H

/* Include files */
#include "pipg_vec_solver_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void pipg_vec_solver(const struct0_T *par, struct1_T *p,
                            const struct2_T *opts, double Z[189],
                            double *solve_time);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (pipg_vec_solver.h) */
