#include "oneggin.h"


int countSymbol (FILE* file)
{
    assert (file);

    fseek (file, 0L, SEEK_END);
    int numSymbol = ftell (file);
    fseek (file, 0L, SEEK_SET);

    return numSymbol;
}


int read_f (char* str, int numSymbol, FILE* input, char* nameofinput)
{
    assert (input);
    assert (str);

    int ret_code = fread (str, sizeof (char), numSymbol, input);
    if (ret_code != numSymbol)
    {
       printf ("Error reading %s\n", nameofinput);
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

    int res = strncmp (ps1->refonBegin, ps2->refonBegin, min);
    return res;
}

void compare_l (struct line* string, int numStrings)
{
    assert (string);

    int num_f = 0, num_s = 0;

    for (num_f = 0; num_f < numStrings - 1; num_f++)
    {
        for (num_s = num_f + 1; num_s < numStrings; num_s++)
        {
            int min = 0;


            if (string[num_f].lenStr > string[num_s].lenStr)
                min = string[num_s].lenStr;
            else
                min = string[num_f].lenStr;


            int ind = 0;
            for (ind = 1; ind <= min; ind++)
            {
                char* refonEnd_f = string[num_f].refonBegin + string[num_f].lenStr - ind;
                char* refonEnd_s = string[num_s].refonBegin + string[num_s].lenStr - ind;

                if (*(refonEnd_f) == *(refonEnd_s))
                {
                    printf ("\n\n\n%s --- %s --- ==\n\n", string[num_f].refonBegin, string[num_s].refonBegin);
                    printf ("%c --- %c\n\n", *(refonEnd_f), *(refonEnd_s));
                        for (int num = 0; num < numStrings; num++)
                        {
                        printf ("%s\n", string[num].refonBegin);
                        }
                    continue;
                }

                else if (*(refonEnd_f) > *(refonEnd_s))
                    {
                        printf ("\n\n\n%s --- %s --- >\n\n", string[num_f].refonBegin, string[num_s].refonBegin);
                        printf ("%c --- %c\n\n", *(refonEnd_f), *(refonEnd_s));
                        for (int num = 0; num < numStrings; num++)
                        {
                        printf ("%s\n", string[num].refonBegin);
                        }
                        char* c = string[num_f].refonBegin;
                        int len = string[num_f].lenStr;
                        string[num_f].refonBegin = string[num_s].refonBegin;
                        string[num_f].lenStr = string[num_s].lenStr;
                        string[num_s].refonBegin = c;
                        string[num_s].lenStr = len;
                        break;
                    }

                else if (*(refonEnd_f) < *(refonEnd_s))
                    {
                        printf ("\n\n\n%s --- %s --- <\n\n", string[num_f].refonBegin, string[num_s].refonBegin);
                        printf ("%c --- %c\n\n", *(refonEnd_f), *(refonEnd_s));;
                        for (int num = 0; num < numStrings; num++)
                        {
                        printf ("%s\n", string[num].refonBegin);
                        }
                        break;
                    }
            }
        }
    }
}


int scanFile (int numSymbol, struct line* string, char* str_in)
{
    assert (string);
    assert (str_in);

    int num = 0, numBeg = 0, ind = 0, fl = 0;

    for (num = 0; num <= numSymbol; num++)
    {
        if ((isalpha (str_in[num])) && (fl == 0))
        {
            string[ind].refonBegin = &str_in[num];
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
            printf ("%s\n", string[ind].refonBegin);

            ind++;
       }
    }
}


const int countStrings (int numSymbol, char* str_in)
{
    assert (isfinite (numSymbol));
    assert (str_in);

    int num, numStrings = 0;

    for (num = 0; num < numSymbol; num++)
        if (str_in[num] == '\n')
        {
            str_in[num] = '\0';
            numStrings++;
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
        printf ("%s\n", string[num].refonBegin);
        fputs (string[num].refonBegin, output);
        fputs ("\n", output);
    }
}

void splitFileFirst (FILE* output)
{
    assert (output);

    fputs ("\nBy the last letters\n\n", output);
}

void splitFileLast (FILE* output)
{
    assert (output);

    fputs ("\nUntouched text\n\n", output);
}

void returnStrings (char* str_in, int numSymbol)
{
    assert (isfinite (numSymbol));
    assert (str_in);

    int num, numStrings = 0;

    for (num = 0; num < numSymbol; num++)
        if (str_in[num] == '\0')
            str_in[num] = '\n';

    str_in[num] = '\n';
}
