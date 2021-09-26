#include "oneggin.h"


int countSymbol (FILE* file)
{
    assert (file);

    fseek (file, 0L, SEEK_END);
    int numSymbol = ftell (file);
    fseek (file, 0L, SEEK_SET);

    return numSymbol;
}


int read_f (char* str, int numSymbol, FILE* input)
{
    assert (input);
    assert (str);

    int ret_code = fread (str, sizeof (char), numSymbol, input);
    if (ret_code != numSymbol)
    {
       printf ("Error reading Gamlet.txt\n");
       return FAIL;
    }
    else
    {
        for (int n = 0; n < numSymbol; n++)
        {
            printf ("%c", str[n]);
        }
        return SUCCESS;
    }
}


int compare_f (const void* p1, const void* p2)
{
    assert (p1);
    assert (p2);
    assert (p1 != p2);

    const struct line* ps1 = (const struct line*) p1;
    const struct line* ps2 = (const struct line*) p2;

    int min = 0;
    if (ps1->lenStr > ps2->lenStr)
        min = ps2->lenStr;
    else
        min = ps1->lenStr;

    int res = strncmp (ps1->index, ps2->index, min); //length
    return res;
}

int compare_l (const void* p1, const void* p2)
{
    assert (p1);
    assert (p2);
    assert (p1 != p2);

    const struct line* ps1 = (const struct line*) p1;
    const struct line* ps2 = (const struct line*) p2;

    int min = 0;
    if (ps1->lenStr > ps2->lenStr)
        min = ps2->lenStr;
    else
        min = ps1->lenStr;

    int num;
    for (num = 0; num < min; num++)
    {
        if (*(ps1->index + ps1->lenStr - num) > *(ps2->index + ps2->lenStr - num))  ///convert
            return 1;
        else if (*(ps1->index + ps1->lenStr - num) < *(ps2->index + ps2->lenStr - num))
            return -1;
    }
}


int scanFile (int numSymbol, struct line* string, char* str_in)
{
    assert (string);
    assert (str_in);

    int num, numBeg = 0, ind = 0, fl = 0;

    for (num = 0; num <= numSymbol; num++)
    {

        if ((isalpha (str_in[num])) && (fl == 0))
        {
            string[ind].index = &str_in[num];
            numBeg = num;
            fl = 1;
            printf ("%c\n", str_in[num]);   ///useless
        }

        if (str_in[num] == '\0')
        {
            int num1 = num;

            string[ind].lenStr = num - numBeg;
            fl = 0;

            printf ("%d ", string[ind].lenStr);

            while (!isalpha (str_in[num1]))
            {
                string[ind].lenStr--;
                num1--;
            }

            string[ind].lenStr++;

            printf ("--- %d\n", string[ind].lenStr);
            printf ("%s\n", string[ind].index);

            ind++;
       }
    }
}


int countStrings (int numSymbol, char* str_in)
{
    assert (str_in);

    int num = 0, numStrings = 0;

    for (num = 0; num < numSymbol; num++) ///?
    {
        if (str_in[num] == '\n')
        {
            str_in[num] = '\0';
            numStrings++;
        }
    }

    str_in[num] = '\0';
    numStrings++;

    return numStrings;
}


int put_res (struct line* string, const int numStrings, FILE* output)
{
    assert (isfinite (numStrings));
    assert (string);
    assert (output);

    int num = 0;

    for (num = 0; num < numStrings; num++)
    {
        printf ("%s\n", string[num].index);     ///index
        fputs (string[num].index, output);
        fputs ("\n", output);
    }
}

void splitFileFirst (FILE* output)
{
    assert (output);

    fputs ("\n\nBy the last letters\n\n", output);
}

void splitFileLast (FILE* output)
{
    assert (output);

    fputs ("\n\nUntouched text\n\n", output);
}
