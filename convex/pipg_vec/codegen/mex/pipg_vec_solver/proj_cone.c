/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * proj_cone.c
 *
 * Code generation for function 'proj_cone'
 *
 */

/* Include files */
#include "proj_cone.h"
#include "norm.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void binary_expand_op(real_T in1[3], real_T in2, const int8_T in3[3],
                      real_T in4, const emxArray_real_T *in5, real_T in6)
{
  real_T b_in5[3];
  const real_T *in5_data;
  real_T d;
  int32_T stride_0_0;
  int8_T i;
  in5_data = in5->data;
  stride_0_0 = (in5->size[0] != 1);
  b_in5[0] = in5_data[0] - in1[0];
  b_in5[1] = in5_data[stride_0_0] - in1[1];
  b_in5[2] = in5_data[stride_0_0 << 1] - in1[2];
  d = c_norm(b_in5);
  stride_0_0 = (in5->size[0] != 1);
  i = in3[0];
  in1[0] = in2 * (real_T)i + in4 * (in5_data[0] - in6 * (real_T)i) / d;
  i = in3[1];
  in1[1] = in2 * (real_T)i + in4 * (in5_data[stride_0_0] - in6 * (real_T)i) / d;
  i = in3[2];
  in1[2] =
      in2 * (real_T)i + in4 * (in5_data[stride_0_0 << 1] - in6 * (real_T)i) / d;
}

/* End of code generation (proj_cone.c) */
