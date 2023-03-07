/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_pipg_vec_solver_api.c
 *
 * Code generation for function 'pipg_vec_solver'
 *
 */

/* Include files */
#include "_coder_pipg_vec_solver_api.h"
#include "_coder_pipg_vec_solver_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131627U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "pipg_vec_solver",                                    /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

static const char_T *sv[4] = {"d", "colidx", "rowidx", "maxnz"};

static const char_T *sv1[4] = {"coder.internal.sparse", "coder.internal.sparse",
                               "coder.internal.sparse",
                               "coder.internal.sparse"};

/* Function Declarations */
static void ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                emxArray_int32_T *ret);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct0_T *y);

static const mxArray *b_emlrt_marshallOut(void);

static int32_T bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId);

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static const mxArray *c_emlrt_marshallOut(const real_T u);

static void cb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[189]);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[6]);

static void db_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[120]);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[36]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *par,
                             const char_T *identifier, struct0_T *y);

static const mxArray *emlrt_marshallOut(const real_T u[189]);

static void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray,
                                      int32_T oldNumel);

static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray,
                                     int32_T oldNumel);

static void emxFreeStruct_sparse(const emlrtStack *sp, sparse *pStruct);

static void emxFreeStruct_struct1_T(const emlrtStack *sp, struct1_T *pStruct);

static void emxFree_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray);

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static void emxInitStruct_sparse(const emlrtStack *sp, sparse *pStruct);

static void emxInitStruct_struct1_T(const emlrtStack *sp, struct1_T *pStruct);

static void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray);

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[9]);

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[18]);

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *p,
                               const char_T *identifier, struct1_T *y);

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct1_T *y);

static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, sparse *y);

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y);

static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_int32_T *y);

static int32_T m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId);

static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, sparse *y);

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, sparse *y);

static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[189]);

static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[120]);

static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *opts,
                               const char_T *identifier, struct2_T *y);

static void s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct2_T *y);

static real_T t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[6]);

static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[36]);

static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[9]);

static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[18]);

static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret);

/* Function Definitions */
static void ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                emxArray_int32_T *ret)
{
  static const int32_T dims = -1;
  int32_T i;
  int32_T i1;
  int32_T *ret_data;
  const boolean_T b = true;
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "int32", false, 1U,
                            (const void *)&dims, &b, &i);
  i1 = ret->size[0];
  ret->size[0] = i;
  emxEnsureCapacity_int32_T(ret, i1);
  ret_data = ret->data;
  emlrtImportArrayR2015b((emlrtConstCTX)sp, src, &ret_data[0], 4, false);
  emlrtDestroyArray(&src);
}

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct0_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[19] = {
      "nx", "nu",  "dt",  "T",     "N",    "n", "x0", "xN", "leading", "Px",
      "Pu", "x0s", "xNs", "th_ac", "umax", "A", "B",  "Q",  "R"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtConstCTX)sp, parentId, u, 19,
                         (const char_T **)&fieldNames[0], 0U,
                         (const void *)&dims);
  thisId.fIdentifier = "nx";
  y->nx = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 0, "nx")),
      &thisId);
  thisId.fIdentifier = "nu";
  y->nu = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 1, "nu")),
      &thisId);
  thisId.fIdentifier = "dt";
  y->dt = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 2, "dt")),
      &thisId);
  thisId.fIdentifier = "T";
  y->T = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 3, "T")),
      &thisId);
  thisId.fIdentifier = "N";
  y->N = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 4, "N")),
      &thisId);
  thisId.fIdentifier = "n";
  y->n = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 5, "n")),
      &thisId);
  thisId.fIdentifier = "x0";
  d_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 6, "x0")),
      &thisId, y->x0);
  thisId.fIdentifier = "xN";
  d_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 7, "xN")),
      &thisId, y->xN);
  thisId.fIdentifier = "leading";
  y->leading = c_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 8, "leading")),
      &thisId);
  thisId.fIdentifier = "Px";
  e_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 9, "Px")),
      &thisId, y->Px);
  thisId.fIdentifier = "Pu";
  f_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 10, "Pu")),
      &thisId, y->Pu);
  thisId.fIdentifier = "x0s";
  d_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 11, "x0s")),
      &thisId, y->x0s);
  thisId.fIdentifier = "xNs";
  d_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 12, "xNs")),
      &thisId, y->xNs);
  thisId.fIdentifier = "th_ac";
  y->th_ac = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 13, "th_ac")),
      &thisId);
  thisId.fIdentifier = "umax";
  y->umax = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 14, "umax")),
      &thisId);
  thisId.fIdentifier = "A";
  e_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 15, "A")),
      &thisId, y->A);
  thisId.fIdentifier = "B";
  g_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 16, "B")),
      &thisId, y->B);
  thisId.fIdentifier = "Q";
  e_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 17, "Q")),
      &thisId, y->Q);
  thisId.fIdentifier = "R";
  f_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 18, "R")),
      &thisId, y->R);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(void)
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {0, 0};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, NULL);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static int32_T bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  int32_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "int32", false, 0U,
                          (const void *)&dims);
  ret = *(int32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = t_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *c_emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

static void cb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[189])
{
  static const int32_T dims = 189;
  real_T(*r)[189];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 1U,
                          (const void *)&dims);
  r = (real_T(*)[189])emlrtMxGetData(src);
  for (i = 0; i < 189; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[6])
{
  u_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void db_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[120])
{
  static const int32_T dims = 120;
  real_T(*r)[120];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 1U,
                          (const void *)&dims);
  r = (real_T(*)[120])emlrtMxGetData(src);
  for (i = 0; i < 120; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[36])
{
  v_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *par,
                             const char_T *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(par), &thisId, y);
  emlrtDestroyArray(&par);
}

static const mxArray *emlrt_marshallOut(const real_T u[189])
{
  static const int32_T i = 0;
  static const int32_T i1 = 189;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

static void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray,
                                      int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(int32_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(int32_T) * (uint32_T)oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (int32_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray,
                                     int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(real_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real_T) * (uint32_T)oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxFreeStruct_sparse(const emlrtStack *sp, sparse *pStruct)
{
  emxFree_real_T(sp, &pStruct->d);
  emxFree_int32_T(sp, &pStruct->colidx);
  emxFree_int32_T(sp, &pStruct->rowidx);
}

static void emxFreeStruct_struct1_T(const emlrtStack *sp, struct1_T *pStruct)
{
  emxFreeStruct_sparse(sp, &pStruct->P);
  emxFreeStruct_sparse(sp, &pStruct->H);
  emxFreeStruct_sparse(sp, &pStruct->Ht);
}

static void emxFree_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int32_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxInitStruct_sparse(const emlrtStack *sp, sparse *pStruct)
{
  emxInit_real_T(sp, &pStruct->d);
  emxInit_int32_T(sp, &pStruct->colidx);
  emxInit_int32_T(sp, &pStruct->rowidx);
}

static void emxInitStruct_struct1_T(const emlrtStack *sp, struct1_T *pStruct)
{
  emxInitStruct_sparse(sp, &pStruct->P);
  emxInitStruct_sparse(sp, &pStruct->H);
  emxInitStruct_sparse(sp, &pStruct->Ht);
}

static void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray)
{
  emxArray_int32_T *emxArray;
  *pEmxArray =
      (emxArray_int32_T *)emlrtMallocEmxArray(sizeof(emxArray_int32_T));
  emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                      (void *)&emxFree_int32_T, NULL, NULL,
                                      NULL);
  emxArray = *pEmxArray;
  emxArray->data = (int32_T *)NULL;
  emxArray->numDimensions = 1;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  emxArray->size[0] = 0;
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  emxArray_real_T *emxArray;
  *pEmxArray = (emxArray_real_T *)emlrtMallocEmxArray(sizeof(emxArray_real_T));
  emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                      (void *)&emxFree_real_T, NULL, NULL,
                                      NULL);
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = 1;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  emxArray->size[0] = 0;
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[9])
{
  w_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[18])
{
  x_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *p,
                               const char_T *identifier, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  i_emlrt_marshallIn(sp, emlrtAlias(p), &thisId, y);
  emlrtDestroyArray(&p);
}

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct1_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[8] = {"umax", "P", "H",  "Ht",
                                        "z",    "w", "xi", "eta"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtConstCTX)sp, parentId, u, 8,
                         (const char_T **)&fieldNames[0], 0U,
                         (const void *)&dims);
  thisId.fIdentifier = "umax";
  y->umax = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 0, "umax")),
      &thisId);
  thisId.fIdentifier = "P";
  j_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 1, "P")),
      &thisId, &y->P);
  thisId.fIdentifier = "H";
  n_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 2, "H")),
      &thisId, &y->H);
  thisId.fIdentifier = "Ht";
  o_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 3, "Ht")),
      &thisId, &y->Ht);
  thisId.fIdentifier = "z";
  p_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 4, "z")),
      &thisId, y->z);
  thisId.fIdentifier = "w";
  q_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 5, "w")),
      &thisId, y->w);
  thisId.fIdentifier = "xi";
  p_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 6, "xi")),
      &thisId, y->xi);
  thisId.fIdentifier = "eta";
  q_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 7, "eta")),
      &thisId, y->eta);
  emlrtDestroyArray(&u);
}

static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, sparse *y)
{
  emlrtMsgIdentifier thisId;
  const mxArray *propValues[4];
  int32_T iv[2];
  boolean_T bv[2];
  propValues[0] = NULL;
  propValues[1] = NULL;
  propValues[2] = NULL;
  propValues[3] = NULL;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  bv[0] = false;
  iv[0] = 189;
  bv[1] = false;
  iv[1] = 189;
  emlrtCheckSparse((emlrtCTX)sp, parentId, u, &iv[0], &bv[0], mxDOUBLE_CLASS,
                   mxREAL);
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, "sparse");
  emlrtAssign(&u, emlrtConvertInstanceToRedirectTarget(
                      (emlrtCTX)sp, u, 0, "coder.internal.sparse"));
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, "coder.internal.sparse");
  emlrtGetAllProperties((emlrtCTX)sp, u, 0, 4, (const char_T **)&sv[0],
                        (const char_T **)&sv1[0], &propValues[0]);
  thisId.fIdentifier = "d";
  k_emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId, y->d);
  thisId.fIdentifier = "colidx";
  l_emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId, y->colidx);
  thisId.fIdentifier = "rowidx";
  l_emlrt_marshallIn(sp, emlrtAlias(propValues[2]), &thisId, y->rowidx);
  thisId.fIdentifier = "maxnz";
  m_emlrt_marshallIn(sp, emlrtAlias(propValues[3]), &thisId);
  emlrtDestroyArrays(4, &propValues[0]);
  emlrtDestroyArray(&u);
}

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y)
{
  y_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_int32_T *y)
{
  ab_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int32_T m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId)
{
  int32_T y;
  y = bb_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, sparse *y)
{
  emlrtMsgIdentifier thisId;
  const mxArray *propValues[4];
  int32_T iv[2];
  boolean_T bv[2];
  propValues[0] = NULL;
  propValues[1] = NULL;
  propValues[2] = NULL;
  propValues[3] = NULL;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  bv[0] = false;
  iv[0] = 120;
  bv[1] = false;
  iv[1] = 189;
  emlrtCheckSparse((emlrtCTX)sp, parentId, u, &iv[0], &bv[0], mxDOUBLE_CLASS,
                   mxREAL);
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, "sparse");
  emlrtAssign(&u, emlrtConvertInstanceToRedirectTarget(
                      (emlrtCTX)sp, u, 0, "coder.internal.sparse"));
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, "coder.internal.sparse");
  emlrtGetAllProperties((emlrtCTX)sp, u, 0, 4, (const char_T **)&sv[0],
                        (const char_T **)&sv1[0], &propValues[0]);
  thisId.fIdentifier = "d";
  k_emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId, y->d);
  thisId.fIdentifier = "colidx";
  l_emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId, y->colidx);
  thisId.fIdentifier = "rowidx";
  l_emlrt_marshallIn(sp, emlrtAlias(propValues[2]), &thisId, y->rowidx);
  thisId.fIdentifier = "maxnz";
  m_emlrt_marshallIn(sp, emlrtAlias(propValues[3]), &thisId);
  emlrtDestroyArrays(4, &propValues[0]);
  emlrtDestroyArray(&u);
}

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, sparse *y)
{
  emlrtMsgIdentifier thisId;
  const mxArray *propValues[4];
  int32_T iv[2];
  boolean_T bv[2];
  propValues[0] = NULL;
  propValues[1] = NULL;
  propValues[2] = NULL;
  propValues[3] = NULL;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  bv[0] = false;
  iv[0] = 189;
  bv[1] = false;
  iv[1] = 120;
  emlrtCheckSparse((emlrtCTX)sp, parentId, u, &iv[0], &bv[0], mxDOUBLE_CLASS,
                   mxREAL);
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, "sparse");
  emlrtAssign(&u, emlrtConvertInstanceToRedirectTarget(
                      (emlrtCTX)sp, u, 0, "coder.internal.sparse"));
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, "coder.internal.sparse");
  emlrtGetAllProperties((emlrtCTX)sp, u, 0, 4, (const char_T **)&sv[0],
                        (const char_T **)&sv1[0], &propValues[0]);
  thisId.fIdentifier = "d";
  k_emlrt_marshallIn(sp, emlrtAlias(propValues[0]), &thisId, y->d);
  thisId.fIdentifier = "colidx";
  l_emlrt_marshallIn(sp, emlrtAlias(propValues[1]), &thisId, y->colidx);
  thisId.fIdentifier = "rowidx";
  l_emlrt_marshallIn(sp, emlrtAlias(propValues[2]), &thisId, y->rowidx);
  thisId.fIdentifier = "maxnz";
  m_emlrt_marshallIn(sp, emlrtAlias(propValues[3]), &thisId);
  emlrtDestroyArrays(4, &propValues[0]);
  emlrtDestroyArray(&u);
}

static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[189])
{
  cb_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[120])
{
  db_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *opts,
                               const char_T *identifier, struct2_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  s_emlrt_marshallIn(sp, emlrtAlias(opts), &thisId, y);
  emlrtDestroyArray(&opts);
}

static void s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct2_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[10] = {
      "omega",    "rho",         "check_iter",  "eps_rel",  "eps_abs",
      "max_iter", "eps_rel_pow", "eps_abs_pow", "eps_buff", "max_iter_pow"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtConstCTX)sp, parentId, u, 10,
                         (const char_T **)&fieldNames[0], 0U,
                         (const void *)&dims);
  thisId.fIdentifier = "omega";
  y->omega = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 0, "omega")),
      &thisId);
  thisId.fIdentifier = "rho";
  y->rho = c_emlrt_marshallIn(
      sp, emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 1, "rho")),
      &thisId);
  thisId.fIdentifier = "check_iter";
  y->check_iter = c_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 2, "check_iter")),
      &thisId);
  thisId.fIdentifier = "eps_rel";
  y->eps_rel = c_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 3, "eps_rel")),
      &thisId);
  thisId.fIdentifier = "eps_abs";
  y->eps_abs = c_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 4, "eps_abs")),
      &thisId);
  thisId.fIdentifier = "max_iter";
  y->max_iter = c_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 5, "max_iter")),
      &thisId);
  thisId.fIdentifier = "eps_rel_pow";
  y->eps_rel_pow =
      c_emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0,
                                                        6, "eps_rel_pow")),
                         &thisId);
  thisId.fIdentifier = "eps_abs_pow";
  y->eps_abs_pow =
      c_emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0,
                                                        7, "eps_abs_pow")),
                         &thisId);
  thisId.fIdentifier = "eps_buff";
  y->eps_buff = c_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0, 8, "eps_buff")),
      &thisId);
  thisId.fIdentifier = "max_iter_pow";
  y->max_iter_pow =
      c_emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtConstCTX)sp, u, 0,
                                                        9, "max_iter_pow")),
                         &thisId);
  emlrtDestroyArray(&u);
}

static real_T t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[6])
{
  static const int32_T dims = 6;
  real_T(*r)[6];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 1U,
                          (const void *)&dims);
  r = (real_T(*)[6])emlrtMxGetData(src);
  for (i = 0; i < 6; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[36])
{
  static const int32_T dims[2] = {6, 6};
  real_T(*r)[36];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                          (const void *)&dims[0]);
  r = (real_T(*)[36])emlrtMxGetData(src);
  for (i = 0; i < 36; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[9])
{
  static const int32_T dims[2] = {3, 3};
  real_T(*r)[9];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                          (const void *)&dims[0]);
  r = (real_T(*)[9])emlrtMxGetData(src);
  for (i = 0; i < 9; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[18])
{
  static const int32_T dims[2] = {6, 3};
  real_T(*r)[18];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                          (const void *)&dims[0]);
  r = (real_T(*)[18])emlrtMxGetData(src);
  for (i = 0; i < 18; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret)
{
  static const int32_T dims = -1;
  real_T *ret_data;
  int32_T i;
  int32_T i1;
  const boolean_T b = true;
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 1U,
                            (const void *)&dims, &b, &i);
  i1 = ret->size[0];
  ret->size[0] = i;
  emxEnsureCapacity_real_T(ret, i1);
  ret_data = ret->data;
  emlrtImportArrayR2015b((emlrtConstCTX)sp, src, &ret_data[0], 8, false);
  emlrtDestroyArray(&src);
}

void pipg_vec_solver_api(const mxArray *const prhs[3], int32_T nlhs,
                         const mxArray *plhs[4])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  struct0_T par;
  struct1_T b_p;
  struct1_T p;
  struct2_T opts;
  real_T(*Z)[189];
  real_T solve_time;
  st.tls = emlrtRootTLSGlobal;
  Z = (real_T(*)[189])mxMalloc(sizeof(real_T[189]));
  mxMalloc(0U);
  mxMalloc(0U);
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "par", &par);
  emxInitStruct_struct1_T(&st, &p);
  h_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "p", &p);
  r_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "opts", &opts);
  /* Invoke the target function */
  b_p = p;
  pipg_vec_solver(&par, &b_p, &opts, *Z, &solve_time);
  emxFreeStruct_struct1_T(&st, &p);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*Z);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut();
  }
  if (nlhs > 2) {
    plhs[2] = b_emlrt_marshallOut();
  }
  if (nlhs > 3) {
    plhs[3] = c_emlrt_marshallOut(solve_time);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

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
  pipg_vec_solver_xil_terminate();
  pipg_vec_solver_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void pipg_vec_solver_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void pipg_vec_solver_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_pipg_vec_solver_api.c) */
