/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pipg_vec_solver_initialize.c
 *
 * Code generation for function 'pipg_vec_solver_initialize'
 *
 */

/* Include files */
#include "pipg_vec_solver_initialize.h"
#include "_coder_pipg_vec_solver_mex.h"
#include "pipg_vec_solver_data.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"

/* Function Declarations */
static void pipg_vec_solver_once(void);

/* Function Definitions */
static void pipg_vec_solver_once(void)
{
  mex_InitInfAndNan();
  savedTime_not_empty_init();
}

void pipg_vec_solver_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, NULL);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    pipg_vec_solver_once();
  }
}

/* End of code generation (pipg_vec_solver_initialize.c) */
