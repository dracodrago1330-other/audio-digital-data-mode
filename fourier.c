#pragma once
#include <string.h>
#include <complex.h>
#include <math.h>
#include "error-handle.c"
#include "misc.c"

complex double * dft(
  const complex double *restrict in,
  size_t len
) {
  complex double *list;
  if (len % 2 == 1) {
    errmalloc(list, sizeof(complex double) * (len + 1));
    list[len] = 0;
  } else {
    errmalloc(list, sizeof(complex double) * len);
  }

  for (size_t k = 0; k < len; ++k) {
    complex double sum = 0.0;
    for (size_t n = 0; n < len; ++n) {
      double angle = 2 * M_PI * k * n / len;
      sum += cexp(-angle * I) * in[n];
    }

    list[k] = sum;
  }

  return list;
}

complex double * idft(
  const complex double *restrict in,
  size_t len
) {
  complex double *list;
  errmalloc(list, sizeof(complex double) * len);

  for (size_t n = 0; n < len; ++n) {
    complex double sum = 0.0;
    for (size_t k = 0; k < len; ++k) {
      double angle = 2 * M_PI * k * n / len;
      sum += cexp(angle * I) * in[k];
    }

    list[n] = sum / len;
  }

  return list;
}



/*
typedef struct {
  size_t           count;
  complex decimal  head;
  complex decimal *middle;
  complex decimal  tail;
} DftList;

DftList * DftList_new(
  complex double elements,
  size_t len
) {

}

void DftList_destroy(
  DftList **self
) {
  if (!self)
    return;

  if ((*self)->middle)
    free((*self)->middle);

  free(*self);

  *self = NULL;
}

void DftList_fill(
  DftList         **self,
  complex decimal  *list,
  size_t            listLength
) {
  (*self)->head = list[0];
  (*self)->tail = list[listLength / 2];
  memcpy((*self)->middle, list + 1, listLength / 2 - 1);
}

complex decimal * DftList_fullDoubleList(
  DftList **self
) {
  complex decimal *fullList = malloc(sizeof(complex decimal) * (*self)->length);
  size_t index = 0, length = (*self)->length;

  fullList[0] = (*self)->head;
  fullList[length / 2 - 1] = (*self)->tail;

  for (; index < length / 2; ++index) {
    fullList[index] = (*self)->middle[index];
    fullList[length - 1 - index] = conj((*self)->middle[index]);
  }
}
*/

