#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
    const char* data;
    size_t length;
} StringView;

float to_number(StringView sv) {
    if (sv.data == NULL || sv.length == 0) return 0;
    float result = 0;
    float fraction = 0;
    int f = -1;
    bool is_fraction = false;
    bool is_negative = false;
    for (size_t i=0;i<sv.length;++i) {
        char c = sv.data[i];
        if (c==0) break;
        switch(c) {
            case '-':
                if (i>0) return 0;
                is_negative = true;
                break;
            case ' ':
            case ',':
                //ignore
                break;
            case '.':
                if (is_fraction) return 0;
                is_fraction = true;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (is_fraction) {
                    fraction = 10*fraction + (c-'0');
                } else {
                    result = 10*result + (c-'0');
                }
                break;
            default:
                return 0;
        }
        if (is_fraction) f++;
    }
    return (is_negative? -1 : 1) * result + fraction/pow(10,f);
}

void swap(float* fs, size_t i, size_t j) {
    float t = fs[i];
    fs[i] = fs[j];
    fs[j] = t;
}

size_t partition(float* fs, size_t start, size_t end) {
    float pivot = fs[end];
    size_t j = start - 1;
    for (size_t i = start; i <= end - 1; ++i) {
        if (fs[i] < pivot) {
            swap(fs,i,++j);
        }
    }
    swap(fs,end,++j);
    return j;
}

void q_sort(float* fs, size_t start, size_t end) {
    if (start>=end) {
       return;
    }
    // printf("\t\tqsort start=%2zu end=%2zu\n",start,end);

    size_t pivot = partition(fs,start,end);
    q_sort(fs,start,pivot - 1);
    q_sort(fs,pivot + 1,end);    
}


// void q_sort(float* fs, size_t start, size_t end) {
//     if (start>=end) return;
//     size_t pivot = fs[end];
//     size_t j = start-1;
//     for(size_t i=start;i<end-1;++i){
//         if (fs[i]>pivot) {
//             swap(fs,i,++j);
//         }
//     }
//     swap(fs,start,++j);
//     q_sort(fs,j+1,end);
//     q_sort(fs,start,j-1);
// }

/*



0,9                [][][][][][][][][]
0,4/4,9            [][][][]            [][][][][]
0,1/2,3/4,5/6,9    [][]    [][]            [][]   [][][]

*/

int main(int argc, char** argv) {
    if (argc == 0) {
        fprintf(stderr, "USAGE: QuickSort [n1 n2 n3 n4 n5 n6] where n is a number.\n");
        return 1;
    }
    float fs[argc-1];
    memset(fs,0,sizeof(float)*(argc-1));
    for(int i=1;i<argc;++i) {
        StringView sv = {.data = argv[i], .length = strlen(argv[i])};
        float f = to_number(sv);
        printf("s='%-14s' f=%14f\n",sv.data,f);
        fs[i-1] = f;
    }
    
    printf("=======================\n");
    q_sort(fs,0,argc-2);
    for(int i=0;i<argc-1;++i) {
        printf("f=%14f\n",fs[i]);
    }

    return 0;
}