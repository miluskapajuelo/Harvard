#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
const int N = 26;
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    // Check validity of key content 226 letters, no more 2 arguments, exist the key in argument
    int letters[N];
    if (!argv[1] || strlen(argv[1]) != 26 || argv[2])
    {
        printf("You need to enter a key with 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {

            // Check only letters are used
            if (!((argv[1][i] >= 'a' && argv[1][i] <= 'z') ||
                  (argv[1][i] >= 'A' && argv[1][i] <= 'Z')))
            {
                printf("Key must contain only letters.\n");
                return 1;
            }
            else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
            {
                argv[1][i] = toupper(argv[1][i]);
            }

            // Check for repeated letters
            for (int j = 0; j < N; j++)
            {
                if (argv[1][i] == letters[j])
                {
                    printf("Key must not contain repeated     letters.\n");
                    return 1;
                }
            }

            letters[i] = argv[1][i];
        }

        // Ask for plaintext
        string plaintext = get_string("plaintext: ");
        int l = strlen(plaintext);
        char ciphertext[l + 1];

        // Convert to ciphertext
        // Loop through each char in plaintext
        for (int t = 0; t < l; t++)
        {
            // Check if uppercase and if so use standard  alphabet/key
            if (isupper(plaintext[t]) != 0)
            {
                for (int j = 0; j < N; j++)
                {
                    if (plaintext[t] == alphabet[j])
                    {
                        ciphertext[t] = argv[1][j];
                        break;
                    }
                }
            }

            // If lowercase use lowercase alphabet and key
            else if (islower(plaintext[t]) != 0)
            {
                for (int j = 0; j < strlen(alphabet); j++)
                {
                    if (plaintext[t] == tolower(alphabet[j]))
                    {
                        ciphertext[t] = tolower(argv[1][j]);
                        break;
                    }
                }
            }

            // Finally replace non letters
            else
            {
                ciphertext[t] = plaintext[t];
            }
        }

        // Add null char to make it a string
        ciphertext[l] = '\0';
        // Print result and exit
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}
