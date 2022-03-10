#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <complex.h>
#include "error-handle.c"
#include "fourier.c"
#include "misc.c"
#include "convolve.c"

int main(
  int argc,
  const char *const *argv
) {
  int errorcode = setjmp(EC_env.jmpEnv);

  if (errorcode != 0) {
    char *errstr = EC_toString(errorcode);
    fprintf(stderr, "%s\n", errstr);
    free(errstr);

    goto error;
  }

  complex double x[] = {
    1.0, 2.0, 3.0, 4.0, 5.0
  };
  complex double y[] = {
    1.0, 2.0, 3.0, 4.0, 5.0
  };

  complex double *outConv = convolve(x, 5, y, 5);

  for (size_t i = 0; i < 9; ++i)
    printf(
      "%f%+fi\n",
      creal(outConv[i]),
      cimag(outConv[i])
    );

error:
  if (outConv)
    free(outConv);

  exit(errorcode);
}

