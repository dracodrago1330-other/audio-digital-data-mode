#pragma once
#include <stdio.h>
#include "error-handle.c"

typedef struct {
  size_t   length;
  int16_t *data;
} Audio;

Audio * Audio_new(
  size_t len
) {
  Audio *a = malloc(sizeof(Audio));

  a->length = len;
  a->data = calloc(sizeof(int16_t), len);

  return a;
}

void Audio_readIn(
  Audio **self,
  FILE   *f
) {
  // assumes `f` contains only raw signed 16-bit audio

  fseek(file, 0, SEEK_END);
  int32_t filesize = ftell(file);

  if (filesize == 0)
    EXITMSG(Exit_InvalidFileSize, "File cannot be empty\n");
  if (filesize % 2 == 1)
    EXITMSG(Exit_InvalidFileSize, "Filesize is not a multiple of two bytes\n");

  rewind(file);

  input = create_collection(filesize / 2);

  fread(input->data, 2, input->len, file);

  if (ferror(file))
    EXITMSG(Exit_FileIOFailure, "Error while reading file\n");
}



int gcd(int x, int y) {
  if (x < 0) x = -x;
  if (y < 0) y = -y;
  if (y) while ((x %= y) && (y %= x));
  return x + y;
}

static inline int lcm(int x, int y) {
  return x / gcd(x, y) * y;
}

int main(void) {
  int v1 = 44100, v2 = -48000, g = gcd(v1, v2);

  printf("%d %d %d\n", g, v1 / g, v2 / g);

  return 0;
}

