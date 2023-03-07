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
#include "CoderTimeAPI.h"
#include "pipg_vec_solver_data.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"

/* Function Definitions */
void pipg_vec_solver_initialize(void)
{
  savedTime_not_empty_init();
  freq_not_empty_init();
  isInitialized_pipg_vec_solver = true;
}

/* End of code generation (pipg_vec_solver_initialize.c) */
