#include <stdio.h>
#include <malloc.h>

void init(int *p){
    *p = 101;
}

int main() {
    int *r = malloc(sizeof(int) * 100);

    printf("%d\n", _msize(r));

    return 0;
}