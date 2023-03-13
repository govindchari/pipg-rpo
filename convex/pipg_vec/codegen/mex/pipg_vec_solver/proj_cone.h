/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * proj_cone.h
 *
 * Code generation for function 'proj_cone'
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
void binary_expand_op(real_T in1[3], real_T in2, const int8_T in3[3],
                      real_T in4, const emxArray_real_T *in5, real_T in6);

/* End of code generation (proj_cone.h) */
