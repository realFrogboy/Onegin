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
    char* refonBegin;
    int lenStr;
};

int open_f (FILE** input, FILE** output);
int countSymbol (FILE* file);
int read_f (char* str, int len, FILE* input, char* nameofinput);
int compare_f (const void* p1, const void* p2);
void compare_l (struct line* string, int numStrings);
int scanFile (int len, struct line* string, char* str_in);
const int countStrings (int len, char* str_in);
int put_res (struct line* string, int numN, FILE* output);
void splitFileFirst (FILE* output);
void splitFileLast (FILE* output);
void returnStrings (char* str_in, int numSymbol);

