/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.c
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "mtimes.h"
#include "introsort.h"
#include "pipg_vec_solver_emxutil.h"
#include "pipg_vec_solver_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void b_sparse_mtimes(const emxArray_real_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, const real_T b[189],
                     real_T c[189])
{
  const real_T *a_d_data;
  const int32_T *a_colidx_data;
  const int32_T *a_rowidx_data;
  int32_T acol;
  int32_T ap;
  a_rowidx_data = a_rowidx->data;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  memset(&c[0], 0, 189U * sizeof(real_T));
  if (a_colidx_data[a_colidx->size[0] - 1] - 1 != 0) {
    for (acol = 0; acol < 189; acol++) {
      real_T bc;
      int32_T apend;
      int32_T i;
      int32_T nap;
      bc = b[acol];
      i = a_colidx_data[acol];
      apend = a_colidx_data[acol + 1];
      nap = apend - a_colidx_data[acol];
      if (nap >= 4) {
        int32_T c_tmp;
        apend = (apend - nap) + ((nap / 4) << 2);
        for (ap = i; ap <= apend - 1; ap += 4) {
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
          c[a_rowidx_data[ap] - 1] += a_d_data[ap] * bc;
          c_tmp = a_rowidx_data[ap + 1] - 1;
          c[c_tmp] += a_d_data[ap + 1] * bc;
          c_tmp = a_rowidx_data[ap + 2] - 1;
          c[c_tmp] += a_d_data[ap + 2] * bc;
        }
        nap = a_colidx_data[acol + 1] - 1;
        for (ap = apend; ap <= nap; ap++) {
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
        }
      } else {
        apend--;
        for (ap = i; ap <= apend; ap++) {
          int32_T c_tmp;
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
        }
      }
    }
  }
}

void c_sparse_mtimes(const emxArray_real_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, const real_T b[120],
                     real_T c[189])
{
  const real_T *a_d_data;
  const int32_T *a_colidx_data;
  const int32_T *a_rowidx_data;
  int32_T acol;
  int32_T ap;
  a_rowidx_data = a_rowidx->data;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  memset(&c[0], 0, 189U * sizeof(real_T));
  if (a_colidx_data[a_colidx->size[0] - 1] - 1 != 0) {
    for (acol = 0; acol < 120; acol++) {
      real_T bc;
      int32_T apend;
      int32_T i;
      int32_T nap;
      bc = b[acol];
      i = a_colidx_data[acol];
      apend = a_colidx_data[acol + 1];
      nap = apend - a_colidx_data[acol];
      if (nap >= 4) {
        int32_T c_tmp;
        apend = (apend - nap) + ((nap / 4) << 2);
        for (ap = i; ap <= apend - 1; ap += 4) {
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
          c[a_rowidx_data[ap] - 1] += a_d_data[ap] * bc;
          c_tmp = a_rowidx_data[ap + 1] - 1;
          c[c_tmp] += a_d_data[ap + 1] * bc;
          c_tmp = a_rowidx_data[ap + 2] - 1;
          c[c_tmp] += a_d_data[ap + 2] * bc;
        }
        nap = a_colidx_data[acol + 1] - 1;
        for (ap = apend; ap <= nap; ap++) {
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
        }
      } else {
        apend--;
        for (ap = i; ap <= apend; ap++) {
          int32_T c_tmp;
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
        }
      }
    }
  }
}

void d_sparse_mtimes(const emxArray_real_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, const real_T b[189],
                     real_T c[120])
{
  const real_T *a_d_data;
  const int32_T *a_colidx_data;
  const int32_T *a_rowidx_data;
  int32_T acol;
  int32_T ap;
  a_rowidx_data = a_rowidx->data;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  memset(&c[0], 0, 120U * sizeof(real_T));
  if (a_colidx_data[a_colidx->size[0] - 1] - 1 != 0) {
    for (acol = 0; acol < 189; acol++) {
      real_T bc;
      int32_T apend;
      int32_T i;
      int32_T nap;
      bc = b[acol];
      i = a_colidx_data[acol];
      apend = a_colidx_data[acol + 1];
      nap = apend - a_colidx_data[acol];
      if (nap >= 4) {
        int32_T c_tmp;
        apend = (apend - nap) + ((nap / 4) << 2);
        for (ap = i; ap <= apend - 1; ap += 4) {
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
          c[a_rowidx_data[ap] - 1] += a_d_data[ap] * bc;
          c_tmp = a_rowidx_data[ap + 1] - 1;
          c[c_tmp] += a_d_data[ap + 1] * bc;
          c_tmp = a_rowidx_data[ap + 2] - 1;
          c[c_tmp] += a_d_data[ap + 2] * bc;
        }
        nap = a_colidx_data[acol + 1] - 1;
        for (ap = apend; ap <= nap; ap++) {
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
        }
      } else {
        apend--;
        for (ap = i; ap <= apend; ap++) {
          int32_T c_tmp;
          c_tmp = a_rowidx_data[ap - 1] - 1;
          c[c_tmp] += a_d_data[ap - 1] * bc;
        }
      }
    }
  }
}

void sparse_mtimes(const emxArray_real_T *a_d, const emxArray_int32_T *a_colidx,
                   const emxArray_int32_T *a_rowidx, const emxArray_real_T *b_d,
                   const emxArray_int32_T *b_colidx,
                   const emxArray_int32_T *b_rowidx, emxArray_real_T *c_d,
                   emxArray_int32_T *c_colidx, emxArray_int32_T *c_rowidx)
{
  real_T wd[189];
  const real_T *a_d_data;
  const real_T *b_d_data;
  real_T bd;
  real_T *c_d_data;
  int32_T flag[189];
  const int32_T *a_colidx_data;
  const int32_T *a_rowidx_data;
  const int32_T *b_colidx_data;
  const int32_T *b_rowidx_data;
  int32_T aend;
  int32_T bcidx;
  int32_T cmax;
  int32_T cnnz;
  int32_T cstart;
  int32_T currRowIdx;
  int32_T i;
  int32_T j;
  int32_T pa;
  int32_T paend;
  int32_T pb;
  int32_T *c_colidx_data;
  int32_T *c_rowidx_data;
  b_rowidx_data = b_rowidx->data;
  b_colidx_data = b_colidx->data;
  b_d_data = b_d->data;
  a_rowidx_data = a_rowidx->data;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  i = c_colidx->size[0];
  c_colidx->size[0] = b_colidx->size[0];
  emxEnsureCapacity_int32_T(c_colidx, i);
  c_colidx_data = c_colidx->data;
  bcidx = b_colidx->size[0];
  for (i = 0; i < bcidx; i++) {
    c_colidx_data[i] = 0;
  }
  memset(&flag[0], 0, 189U * sizeof(int32_T));
  cnnz = 0;
  j = 0;
  int32_T exitg1;
  do {
    exitg1 = 0;
    if (j < 189) {
      bcidx = b_colidx_data[j];
      cstart = cnnz;
      cmax = cnnz + 189;
      c_colidx_data[j] = cnnz + 1;
      while ((bcidx < b_colidx_data[j + 1]) && (cnnz <= cmax)) {
        currRowIdx = b_rowidx_data[bcidx - 1];
        aend = a_colidx_data[currRowIdx] - 1;
        i = a_colidx_data[currRowIdx - 1];
        for (paend = i; paend <= aend; paend++) {
          currRowIdx = a_rowidx_data[paend - 1] - 1;
          if (flag[currRowIdx] != j + 1) {
            flag[currRowIdx] = j + 1;
            cnnz++;
          }
        }
        bcidx++;
      }
      if (cnnz < cstart) {
        exitg1 = 1;
      } else {
        j++;
      }
    } else {
      c_colidx_data[189] = cnnz + 1;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (cnnz < 1) {
    cnnz = 1;
  }
  i = c_d->size[0];
  c_d->size[0] = cnnz;
  emxEnsureCapacity_real_T(c_d, i);
  c_d_data = c_d->data;
  i = c_rowidx->size[0];
  c_rowidx->size[0] = cnnz;
  emxEnsureCapacity_int32_T(c_rowidx, i);
  c_rowidx_data = c_rowidx->data;
  memset(&flag[0], 0, 189U * sizeof(int32_T));
  pb = 0;
  cnnz = -1;
  for (j = 0; j < 189; j++) {
    boolean_T needSort;
    needSort = false;
    cmax = cnnz + 2;
    aend = b_colidx_data[j + 1];
    bcidx = (aend - pb) - 1;
    if (bcidx != 0) {
      if (bcidx == 1) {
        paend = a_colidx_data[b_rowidx_data[pb]] - 1;
        i = a_colidx_data[b_rowidx_data[pb] - 1];
        for (pa = i; pa <= paend; pa++) {
          currRowIdx = a_rowidx_data[pa - 1];
          c_rowidx_data[((cnnz + pa) - i) + 1] = currRowIdx;
          wd[currRowIdx - 1] = a_d_data[pa - 1] * b_d_data[pb];
        }
        cnnz = (cnnz + a_colidx_data[b_rowidx_data[pb]]) -
               a_colidx_data[b_rowidx_data[pb] - 1];
        pb++;
      } else {
        currRowIdx = a_colidx_data[b_rowidx_data[pb]];
        paend = currRowIdx - 1;
        i = a_colidx_data[b_rowidx_data[pb] - 1];
        for (pa = i; pa <= paend; pa++) {
          bcidx = a_rowidx_data[pa - 1];
          cstart = (cnnz + pa) - i;
          flag[bcidx - 1] = cstart + 2;
          c_rowidx_data[cstart + 1] = bcidx;
          wd[bcidx - 1] = a_d_data[pa - 1] * b_d_data[pb];
        }
        cnnz = (cnnz + currRowIdx) - i;
        for (pb++; pb + 1 < aend; pb++) {
          bd = b_d_data[pb];
          paend = a_colidx_data[b_rowidx_data[pb]] - 1;
          i = a_colidx_data[b_rowidx_data[pb] - 1];
          for (pa = i; pa <= paend; pa++) {
            currRowIdx = a_rowidx_data[pa - 1];
            if (flag[currRowIdx - 1] < cmax) {
              cnnz++;
              flag[currRowIdx - 1] = cnnz + 1;
              c_rowidx_data[cnnz] = currRowIdx;
              wd[currRowIdx - 1] = a_d_data[pa - 1] * bd;
              needSort = true;
            } else {
              wd[currRowIdx - 1] += a_d_data[pa - 1] * bd;
            }
          }
        }
      }
    }
    cstart = c_colidx_data[j + 1] - 1;
    i = c_colidx_data[j];
    if (needSort) {
      introsort(c_rowidx, c_colidx_data[j], c_colidx_data[j + 1] - 1);
      c_rowidx_data = c_rowidx->data;
    }
    for (currRowIdx = i; currRowIdx <= cstart; currRowIdx++) {
      c_d_data[currRowIdx - 1] = wd[c_rowidx_data[currRowIdx - 1] - 1];
    }
  }
  bcidx = 1;
  i = c_colidx->size[0];
  for (cmax = 0; cmax <= i - 2; cmax++) {
    cstart = c_colidx_data[cmax];
    c_colidx_data[cmax] = bcidx;
    while (cstart < c_colidx_data[cmax + 1]) {
      currRowIdx = c_rowidx_data[cstart - 1];
      bd = c_d_data[cstart - 1];
      cstart++;
      if (bd != 0.0) {
        c_d_data[bcidx - 1] = bd;
        c_rowidx_data[bcidx - 1] = currRowIdx;
        bcidx++;
      }
    }
  }
  c_colidx_data[c_colidx->size[0] - 1] = bcidx;
}

/* End of code generation (mtimes.c) */
