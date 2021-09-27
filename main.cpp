#include "oneggin.h"

int main ()
{
    FILE *input = NULL;
    FILE *output = NULL;

    char nameofinput[40], nameofoutput[40];


//-----------------------------------------------------------------------------


    printf ("Enter the name of input file\n");
    if (scanf ("%s", nameofinput) != 1)
    {
        printf ("Incorrect input\n");
        return FAIL;
    }

    if ((input = fopen (nameofinput, "rb")) == NULL)
    {
        printf ("Error openning file %s\n", nameofinput);
        return FAIL;
    }


//-----------------------------------------------------------------------------


    printf ("Enter the name of output file\n");
    if (scanf ("%s", nameofoutput) != 1)
    {
        printf ("Incorrect input\n");
        return FAIL;
    }

    if ((output = fopen (nameofoutput, "wb")) == NULL)
    {
        printf ("Error openning file %s\n", nameofoutput);
        return FAIL;
    }


//-----------------------------------------------------------------------------


    int numSymbol = countSymbol (input);
    printf ("%d\n", numSymbol);

    char* str_in = (char*) calloc (numSymbol, sizeof (char));
    if (str_in == NULL)
    {
        printf ("Can't alloc memory\n");
        return FAIL;
    }

    if ((read_f (str_in, numSymbol, input, nameofinput)) == FAIL)
        return FAIL;


    const int numStrings = countStrings (numSymbol, str_in);
    printf ("%d\n", numStrings);


    struct line* string = (line*) calloc (numStrings, sizeof (line));
    if (string == NULL)
    {
        printf ("Can't alloc memory\n");
        return FAIL;
    }

    scanFile (numSymbol, string, str_in);

    qsort (string, numStrings, sizeof (struct line), compare_f);
    put_res (string, numStrings, output);

    splitFileFirst (output);

    compare_l (string, numStrings);
    put_res (string, numStrings, output);

    splitFileLast (output);

    returnStrings (str_in, numSymbol);

    if (fwrite (str_in, sizeof (char), numSymbol, output) < numSymbol)
    {
        printf ("Can't write file\n");
        return FAIL;
    }

    free (str_in);
    free (string);

    return SUCCESS;
}
