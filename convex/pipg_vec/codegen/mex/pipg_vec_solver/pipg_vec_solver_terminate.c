/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver_terminate.c
 *
 * Code generation for function 'pipg_vec_solver_terminate'
 *
 */

/* Include files */
#include "pipg_vec_solver_terminate.h"
#include "_coder_pipg_vec_solver_mex.h"
#include "pipg_vec_solver_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void pipg_vec_solver_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void pipg_vec_solver_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (pipg_vec_solver_terminate.c) */
