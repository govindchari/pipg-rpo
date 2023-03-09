/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * introsort.c
 *
 * Code generation for function 'introsort'
 *
 */

/* Include files */
#include "introsort.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  int32_T xstart;
  int32_T xend;
  int32_T depth;
} struct_T;
#endif /* typedef_struct_T */

/* Variable Definitions */
static emlrtRSInfo nb_emlrtRSI = {
    34,          /* lineNo */
    "introsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "introsort.m" /* pathName */
};

static emlrtRSInfo ob_emlrtRSI = {
    42,          /* lineNo */
    "introsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "introsort.m" /* pathName */
};

static emlrtRSInfo qb_emlrtRSI = {
    47,          /* lineNo */
    "introsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "introsort.m" /* pathName */
};

static emlrtRSInfo rb_emlrtRSI = {
    55,          /* lineNo */
    "introsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "introsort.m" /* pathName */
};

static emlrtRSInfo sb_emlrtRSI = {
    58,          /* lineNo */
    "introsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "introsort.m" /* pathName */
};

static emlrtRSInfo tb_emlrtRSI = {
    41,          /* lineNo */
    "introsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "introsort.m" /* pathName */
};

static emlrtRTEInfo i_emlrtRTEI = {
    62,           /* lineNo */
    39,           /* colNo */
    "stack/push", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "stack.m" /* pName */
};

static emlrtDCInfo j_emlrtDCI = {
    48,            /* lineNo */
    48,            /* colNo */
    "stack/stack", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "stack.m", /* pName */
    4          /* checkKind */
};

/* Function Definitions */
void introsort(const emlrtStack *sp, emxArray_int32_T *x, int32_T xstart,
               int32_T xend)
{
  emlrtStack st;
  struct_T frame;
  int32_T nsort;
  int32_T pmax;
  int32_T *x_data;
  st.prev = sp;
  st.tls = sp->tls;
  x_data = x->data;
  if (xstart < xend) {
    nsort = (xend - xstart) + 1;
    if (nsort <= 32) {
      st.site = &nb_emlrtRSI;
      insertionsort(&st, x, xstart, xend);
    } else {
      struct_T st_d_data[120];
      int32_T pivot;
      int32_T pmin;
      int32_T pow2p;
      int32_T st_n;
      int32_T unnamed_idx_0;
      boolean_T exitg1;
      pmax = 31;
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        pivot = (pmin + pmax) >> 1;
        pow2p = 1 << pivot;
        if (pow2p == nsort) {
          pmax = pivot;
          exitg1 = true;
        } else if (pow2p > nsort) {
          pmax = pivot;
        } else {
          pmin = pivot;
        }
      }
      pow2p = (pmax - 1) << 1;
      frame.xstart = xstart;
      frame.xend = xend;
      frame.depth = 0;
      st.site = &tb_emlrtRSI;
      unnamed_idx_0 = pow2p << 1;
      if (unnamed_idx_0 < 0) {
        emlrtNonNegativeCheckR2012b(unnamed_idx_0, &j_emlrtDCI, &st);
      }
      for (pmax = 0; pmax < unnamed_idx_0; pmax++) {
        st_d_data[pmax] = frame;
      }
      st.site = &ob_emlrtRSI;
      if (unnamed_idx_0 <= 0) {
        emlrtErrorWithMessageIdR2018a(&st, &i_emlrtRTEI,
                                      "Coder:toolbox:StackPushLimit",
                                      "Coder:toolbox:StackPushLimit", 0);
      }
      st_d_data[0] = frame;
      st_n = 1;
      while (st_n > 0) {
        frame = st_d_data[st_n - 1];
        st_n--;
        pmax = frame.xend - frame.xstart;
        if (pmax + 1 <= 32) {
          st.site = &qb_emlrtRSI;
          insertionsort(&st, x, frame.xstart, frame.xend);
          x_data = x->data;
        } else if (frame.depth == pow2p) {
          b_heapsort(x, frame.xstart, frame.xend);
          x_data = x->data;
        } else {
          nsort = (frame.xstart + pmax / 2) - 1;
          pmax = x_data[frame.xstart - 1];
          if (x_data[nsort] < pmax) {
            x_data[frame.xstart - 1] = x_data[nsort];
            x_data[nsort] = pmax;
          }
          if (x_data[frame.xend - 1] < x_data[frame.xstart - 1]) {
            pmin = x_data[frame.xstart - 1];
            x_data[frame.xstart - 1] = x_data[frame.xend - 1];
            x_data[frame.xend - 1] = pmin;
          }
          if (x_data[frame.xend - 1] < x_data[nsort]) {
            pmin = x_data[nsort];
            x_data[nsort] = x_data[frame.xend - 1];
            x_data[frame.xend - 1] = pmin;
          }
          pivot = x_data[nsort];
          x_data[nsort] = x_data[frame.xend - 2];
          x_data[frame.xend - 2] = pivot;
          nsort = frame.xstart - 1;
          pmax = frame.xend - 2;
          int32_T exitg2;
          do {
            exitg2 = 0;
            for (nsort++; x_data[nsort] < pivot; nsort++) {
            }
            for (pmax--; pivot < x_data[pmax]; pmax--) {
            }
            if (nsort + 1 >= pmax + 1) {
              exitg2 = 1;
            } else {
              pmin = x_data[nsort];
              x_data[nsort] = x_data[pmax];
              x_data[pmax] = pmin;
            }
          } while (exitg2 == 0);
          x_data[frame.xend - 2] = x_data[nsort];
          x_data[nsort] = pivot;
          if (nsort + 2 < frame.xend) {
            st.site = &rb_emlrtRSI;
            if (st_n >= unnamed_idx_0) {
              emlrtErrorWithMessageIdR2018a(&st, &i_emlrtRTEI,
                                            "Coder:toolbox:StackPushLimit",
                                            "Coder:toolbox:StackPushLimit", 0);
            }
            st_d_data[st_n].xstart = nsort + 2;
            st_d_data[st_n].xend = frame.xend;
            st_d_data[st_n].depth = frame.depth + 1;
            st_n++;
          }
          if (frame.xstart < nsort + 1) {
            st.site = &sb_emlrtRSI;
            if (st_n >= unnamed_idx_0) {
              emlrtErrorWithMessageIdR2018a(&st, &i_emlrtRTEI,
                                            "Coder:toolbox:StackPushLimit",
                                            "Coder:toolbox:StackPushLimit", 0);
            }
            st_d_data[st_n].xstart = frame.xstart;
            st_d_data[st_n].xend = nsort + 1;
            st_d_data[st_n].depth = frame.depth + 1;
            st_n++;
          }
        }
      }
    }
  }
}

/* End of code generation (introsort.c) */
