#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "misc.c"

complex double * convolve(
  complex double *x,
  long xLen,
  complex double *y,
  long yLen
) {
  long items = xLen + yLen - 1, i = 0;
  complex double *out = calloc(items, sizeof(complex double));

  do {
    long xStart = min(i, xLen - 1),
         yStart = max(0, i - xLen + 1),
         j      = yStart,
         yEnd   = min(i + 1, yLen);

    while (j < yEnd)
      out[i] += x[xStart--] * y[j++];
  } while (++i < items);

  return out;
}
