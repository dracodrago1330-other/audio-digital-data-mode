#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

struct {
  jmp_buf     jmpEnv;
  const char *message;
  int         line;
  const char *file;
  const char *func;
} EC_env = { 0 };

enum {
  EC_Ok,
  EC_GeneralError,
  EC_AllocationError,
  EC_FileIOError,
  EC_FileSizeError
};

const char *const EC_LIST[] = {
  "",
  "general error",
  "memory allocation",
  "file I/O error",
  "filesize error"
};



void EC_throwFull(
  int ec,
  const char *message,
  int line,
  const char *file,
  const char *func
) {
  EC_env.message = message;
  EC_env.line    = line;
  EC_env.file    = file;
  EC_env.func    = func;

  longjmp(EC_env.jmpEnv, ec);
}

#define EC_throw($ec, $message) \
  (EC_throwFull(($ec), ($message), __LINE__, __FILE__, __func__))

#define errmalloc($name, $size) {       \
  $name = malloc(($size));              \
  if (!$name)                           \
    EC_throw(                           \
      EC_AllocationError,               \
      ": failed to malloc `" #$name "`" \
    );                                  \
}

#define errcalloc($name, $count, $size) { \
  $name = calloc(($count), ($size));      \
  if (!$name)                             \
    EC_throw(                             \
      EC_AllocationError,                 \
      ": failed to calloc `" #$name "`"   \
    );                                    \
}

char * EC_toString(
  int ec
) {
  size_t listStrLen    = strlen(EC_LIST[ec]),
         messageStrLen = strlen(EC_env.message),
         lineStrLen    = snprintf(NULL, 0, "%d", EC_env.line),
         fileStrLen    = strlen(EC_env.file),
         funcStrLen    = strlen(EC_env.func);

  char *conc;
  errmalloc(conc,
    sizeof(char) * (
      listStrLen
      + messageStrLen
      + lineStrLen
      + fileStrLen
      + funcStrLen
      + 19 // added characters
      + 1  // null terminator
    )
  );

  sprintf(
    conc,
    "Error (%s)%s in `%s` (%s, %d)",
    EC_LIST[ec],
    EC_env.message,
    EC_env.func,
    EC_env.file,
    EC_env.line
  );

  return conc;
}

