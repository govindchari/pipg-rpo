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
  int xstart;
  int xend;
  int depth;
} struct_T;
#endif /* typedef_struct_T */

/* Function Definitions */
void introsort(emxArray_int32_T *x, int xstart, int xend)
{
  struct_T frame;
  int nsort;
  int pmax;
  int *x_data;
  x_data = x->data;
  if (xstart < xend) {
    nsort = (xend - xstart) + 1;
    if (nsort <= 32) {
      insertionsort(x, xstart, xend);
    } else {
      struct_T st_d_data[120];
      int MAXDEPTH;
      int pivot;
      int pmin;
      int pow2p;
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
      MAXDEPTH = (pmax - 1) << 1;
      frame.xstart = xstart;
      frame.xend = xend;
      frame.depth = 0;
      nsort = MAXDEPTH << 1;
      for (pmax = 0; pmax < nsort; pmax++) {
        st_d_data[pmax] = frame;
      }
      st_d_data[0] = frame;
      pow2p = 1;
      while (pow2p > 0) {
        frame = st_d_data[pow2p - 1];
        pow2p--;
        pmax = frame.xend - frame.xstart;
        if (pmax + 1 <= 32) {
          insertionsort(x, frame.xstart, frame.xend);
          x_data = x->data;
        } else if (frame.depth == MAXDEPTH) {
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
          int exitg2;
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
            st_d_data[pow2p].xstart = nsort + 2;
            st_d_data[pow2p].xend = frame.xend;
            st_d_data[pow2p].depth = frame.depth + 1;
            pow2p++;
          }
          if (frame.xstart < nsort + 1) {
            st_d_data[pow2p].xstart = frame.xstart;
            st_d_data[pow2p].xend = nsort + 1;
            st_d_data[pow2p].depth = frame.depth + 1;
            pow2p++;
          }
        }
      }
    }
  }
}

/* End of code generation (introsort.c) */
