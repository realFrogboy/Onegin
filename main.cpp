#include "oneggin.h"

int main ()
{
    FILE *input = NULL;
    FILE *output = NULL;

    if ((input = fopen ("Gamlet.txt", "rb")) == NULL)
    {
        printf ("Error openning file Gamlet.txt");
        return FAIL;
    }

    if ((output = fopen ("oGamlet.txt", "wb")) == NULL)
    {
        printf ("Error openning file oGamlet.txt");
        return FAIL;
    }
                                                               //rename len
    int numSymbol = countSymbol (input);
    printf ("%d\n", numSymbol);

    char* str_in = (char*) calloc (numSymbol, sizeof (char));
    if (str_in == NULL)
    {
        printf ("Can't alloc memory\n");
        return FAIL;
    }

    if ((read_f (str_in, numSymbol, input)) == FAIL)
        return FAIL;

    int numStrings = countStrings (numSymbol, str_in); //rename
    printf ("%d\n", numStrings);

    struct line* string = (line*) calloc (numStrings, sizeof (line)); //calloc
    if (string == NULL)
    {
        printf ("Can't alloc memory\n");
        return FAIL;
    }

    scanFile (numSymbol, string, str_in);

    qsort (string, numStrings, sizeof (struct line), compare_f);
    put_res (string, numStrings, output);

    splitFileFirst (output);

    qsort (string, numStrings, sizeof (struct line), compare_l);
    put_res (string, numStrings, output);

    splitFileLast (output);

    if (fwrite (str_in, sizeof (char), numSymbol, output) < numSymbol)
    {
        printf ("Can't write file\n");
        return FAIL;
    }

    free (str_in);
    free (string);

    return SUCCESS;
}
