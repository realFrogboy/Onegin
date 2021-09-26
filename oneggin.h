#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

enum RESULTS
{
    FAIL = 1,
    SUCCESS = 0,
};

struct line
{
    char* index;
    int lenStr;
};

int open_f (FILE** input, FILE** output);
int countSymbol (FILE* file);
int read_f (char* str, int len, FILE* input);
int compare_f (const void* p1, const void* p2);
int compare_l (const void* p1, const void* p2);
int scanFile (int len, struct line* string, char* str_in);
int countStrings (int len, char* str_in);
int put_res (struct line* string, int numN, FILE* output);
void splitFileFirst (FILE* output);
void splitFileLast (FILE* output);

