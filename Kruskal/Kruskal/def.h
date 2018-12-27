#ifndef _DEF_H_
#define _DEF_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define USING_DEBUG

typedef enum{
    RET_OK,
    RET_ERROR,
    RET_NOMEM,
    RET_INVALID_ARGUMENT
}Ret;

#define return_if_fail(p)  if(!(p))                   \
        {printf("%s->line%d Warning: "#p" failed.\n",    \
        __func__, __LINE__); return;}

#define return_val_if_fail(p, ret)  if(!(p))          \
        {printf("%s->line %d Warning: "#p" failed.\n",    \
        __func__, __LINE__); return (ret);}

#define max(a, b)  \
        (a > b ? a : b)

typedef void (*VisitFunc)(void *data, void *user_data);
typedef int32_t (*CompareFunc)(void *data1, void *data2, void *user_data);
typedef void (*SwapFunc)(void *data1, void *data2, void *UserData);

#endif // _DEF_H_

