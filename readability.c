#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int count_letters(string texto);
int count_word(string texto);
int count_sentences(string texto);


int main(void)
{
    string text = get_string("Text: \n");
    // calcular cuantes letras
    int letras = strlen(text);

    int l = count_letters(text);
    int w = count_word(text);
    int s = count_sentences(text);

    // formula to get L and S
    float L = 100 * ((float)l / (float)w);
    float S = 100 * ((float)s / (float)w);

    // getting index
    int clindex = round(0.0588 * L - 0.296 * S - 15.8);

    // Printf "Grade X" if X > 16, printf "Grade 16+".
    if (clindex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (clindex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", clindex);
    }
}

int count_letters(string texto)
{

    int counLetters = 0;
    for (int i = 0; i < strlen(texto); i++)
    {
        if (isalpha(texto[i]))
        {
            counLetters += 1;
        }

    }

    return counLetters;
}

int count_word(string texto)
{

    int counWord = 1;
    for (int i = 0; i < strlen(texto); i++)
    {
        if (texto[i] == 32)
        {
            counWord += 1;
        }

    }

    return counWord;
}


int count_sentences(string texto)
{

    int counSentence = 0;
    for (int i = 0; i < strlen(texto); i++)
    {
        if (texto[i] == 33 || texto[i] == 63 || texto[i] == 46)
        {
            counSentence += 1;
        }

    }

    return counSentence;
}

