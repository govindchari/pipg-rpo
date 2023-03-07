/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_pipg_vec_solver_mex.c
 *
 * Code generation for function 'pipg_vec_solver'
 *
 */

/* Include files */
#include "_coder_pipg_vec_solver_mex.h"
#include "_coder_pipg_vec_solver_api.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&pipg_vec_solver_atexit);
  /* Module initialization. */
  pipg_vec_solver_initialize();
  /* Dispatch the entry-point. */
  unsafe_pipg_vec_solver_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  pipg_vec_solver_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

void unsafe_pipg_vec_solver_mexFunction(int32_T nlhs, mxArray *plhs[4],
                                        int32_T nrhs, const mxArray *prhs[3])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs[4];
  int32_T i;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        15, "pipg_vec_solver");
  }
  if (nlhs > 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "pipg_vec_solver");
  }
  /* Call the function. */
  pipg_vec_solver_api(prhs, nlhs, outputs);
  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    i = 1;
  } else {
    i = nlhs;
  }
  emlrtReturnArrays(i, &plhs[0], &outputs[0]);
}

/* End of code generation (_coder_pipg_vec_solver_mex.c) */
