/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "pipg_vec_solver.h"
#include "pipg_vec_solver_emxAPI.h"
#include "pipg_vec_solver_terminate.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static void argInit_120x1_real_T(double result[120]);

static void argInit_189x1_real_T(double result[189]);

static void argInit_3x3_real_T(double result[9]);

static void argInit_6x1_real_T(double result[6]);

static void argInit_6x3_real_T(double result[18]);

static void argInit_6x6_real_T(double result[36]);

static emxArray_int32_T *argInit_Unboundedx1_int32_T(void);

static emxArray_real_T *argInit_Unboundedx1_real_T(void);

static int argInit_int32_T(void);

static double argInit_real_T(void);

static sparse argInit_sparse(void);

static void argInit_struct0_T(struct0_T *result);

static void argInit_struct1_T(struct1_T *result);

static void argInit_struct2_T(struct2_T *result);

/* Function Definitions */
static void argInit_120x1_real_T(double result[120])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 120; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_189x1_real_T(double result[189])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 189; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_3x3_real_T(double result[9])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 9; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}

static void argInit_6x1_real_T(double result[6])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 6; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_6x3_real_T(double result[18])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 18; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}

static void argInit_6x6_real_T(double result[36])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 36; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}

static emxArray_int32_T *argInit_Unboundedx1_int32_T(void)
{
  emxArray_int32_T *result;
  const int i = 2;
  int idx0;
  int *result_data;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreateND_int32_T(1, &i);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result_data[idx0] = argInit_int32_T();
  }
  return result;
}

static emxArray_real_T *argInit_Unboundedx1_real_T(void)
{
  emxArray_real_T *result;
  double *result_data;
  const int i = 2;
  int idx0;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreateND_real_T(1, &i);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result_data[idx0] = argInit_real_T();
  }
  return result;
}

static int argInit_int32_T(void)
{
  return 0;
}

static double argInit_real_T(void)
{
  return 0.0;
}

static sparse argInit_sparse(void)
{
  sparse result;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result.d = argInit_Unboundedx1_real_T();
  result.colidx = argInit_Unboundedx1_int32_T();
  result.rowidx = argInit_Unboundedx1_int32_T();
  return result;
}

static void argInit_struct0_T(struct0_T *result)
{
  double result_tmp;
  int i;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result->nu = result_tmp;
  result->dt = result_tmp;
  result->T = result_tmp;
  result->N = result_tmp;
  result->n = result_tmp;
  argInit_6x1_real_T(result->x0);
  result->leading = result_tmp;
  result->th_ac = result_tmp;
  result->umax = result_tmp;
  argInit_6x6_real_T(result->Px);
  argInit_3x3_real_T(result->Pu);
  result->nx = result_tmp;
  argInit_6x3_real_T(result->B);
  for (i = 0; i < 6; i++) {
    result->xN[i] = result->x0[i];
    result->x0s[i] = result->x0[i];
    result->xNs[i] = result->x0[i];
  }
  for (i = 0; i < 36; i++) {
    result->A[i] = result->Px[i];
    result->Q[i] = result->Px[i];
  }
  memcpy(&result->R[0], &result->Pu[0], 9U * sizeof(double));
}

static void argInit_struct1_T(struct1_T *result)
{
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  argInit_189x1_real_T(result->z);
  argInit_120x1_real_T(result->w);
  result->umax = argInit_real_T();
  result->P = argInit_sparse();
  result->H = argInit_sparse();
  result->Ht = argInit_sparse();
  memcpy(&result->xi[0], &result->z[0], 189U * sizeof(double));
  memcpy(&result->eta[0], &result->w[0], 120U * sizeof(double));
}

static void argInit_struct2_T(struct2_T *result)
{
  double result_tmp;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result->rho = result_tmp;
  result->check_iter = result_tmp;
  result->eps_rel = result_tmp;
  result->eps_abs = result_tmp;
  result->max_iter = result_tmp;
  result->eps_rel_pow = result_tmp;
  result->eps_abs_pow = result_tmp;
  result->eps_buff = result_tmp;
  result->max_iter_pow = result_tmp;
  result->omega = result_tmp;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_pipg_vec_solver();
  /* Terminate the application.
You do not need to do this more than one time. */
  pipg_vec_solver_terminate();
  return 0;
}

void main_pipg_vec_solver(void)
{
  struct0_T r;
  struct1_T b_p;
  struct1_T p;
  struct2_T r1;
  double Z[189];
  double solve_time;
  /* Initialize function 'pipg_vec_solver' input arguments. */
  /* Initialize function input argument 'par'. */
  /* Initialize function input argument 'p'. */
  argInit_struct1_T(&p);
  /* Initialize function input argument 'opts'. */
  /* Call the entry-point 'pipg_vec_solver'. */
  argInit_struct0_T(&r);
  argInit_struct2_T(&r1);
  b_p = p;
  pipg_vec_solver(&r, &b_p, &r1, Z, &solve_time);
  emxDestroy_struct1_T(p);
}

/* End of code generation (main.c) */
