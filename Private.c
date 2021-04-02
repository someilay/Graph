#include <malloc.h>
#include "Private.h"

Private *createPrivate(int n) {
    Private* out = malloc(sizeof(Private));

    out->privateField = malloc(sizeof(void*) * n);

    return out;
}