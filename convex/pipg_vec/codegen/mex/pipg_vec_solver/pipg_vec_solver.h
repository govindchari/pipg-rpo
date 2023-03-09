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
void pipg_vec_solver(const emlrtStack *sp, const struct0_T *par, struct1_T *p,
                     const struct2_T *opts, real_T Z[189], real_T *solve_time);

/* End of code generation (pipg_vec_solver.h) */
