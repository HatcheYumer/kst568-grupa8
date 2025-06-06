
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXN 1000
#define ALPHA_LENGTH 26
#define COMMON_LETTERS 10

char *cezar_decipher(char *cipher, int key)
{
    int length = strlen(cipher);
    char *plaintext = (char *)malloc(sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++)
    {
        if (cipher[i] >= 'a' && cipher[i] <= 'z')
        {
            plaintext[i] = (cipher[i] - 'a' - key + 26) % 26 + 'a';
        }
        else if (cipher[i] >= 'A' && cipher[i] <= 'Z')
        {
            plaintext[i] = (cipher[i] - 'A' - key + 26) % 26 + 'A';
        }
        else if (cipher[i] >= '0' && cipher[i] <= '9')
        {
            plaintext[i] = (cipher[i] - '0' - key + 10) % 10 + '0';
        }
        else{
            plaintext[i] = cipher[i];
        }
    }
    plaintext[length] = '\0';

    return plaintext;
}
int *count_frequencies(char *cipher)
{
    int *frequencies = (int *)malloc(sizeof(int) * ALPHA_LENGTH);
    memset(frequencies, 0, sizeof(int) * ALPHA_LENGTH);

    int length = strlen(cipher);
    for (int i = 0; i < length; i++)
    {
        char letter = tolower(cipher[i]);
        if (letter >= 'a' && letter <= 'Z')
        {
            int position = letter - 'a';
            frequencies[position]++;
        }
    }
    return frequencies;
}

int read_cipher(char *filename, char *cipher)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("The file does not exits.");
        return EXIT_FAILURE;
    }

    if (fgets(cipher, MAXN, fp) == NULL)
    {
        printf("Error reading from file.");
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}


int get_max_index(int* frequencies)
{
    int max_index = 0;
    for(int i = 0; i < ALPHA_LENGTH; i++)
    {
        if(frequencies[i] > frequencies[max_index])
        {
            max_index = i;
        }
    }
    return max_index;
}


int main()
{
    char cipher[MAXN];
    char filename[MAXN];
    scanf("%s", filename);
    read_cipher(filename, cipher);
    int *frequencies = count_frequencies(cipher);
    char most_common_letter = get_max_index(frequencies) + 'a';

    char commons[COMMON_LETTERS] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd'};
    for (int i = 0; i < COMMON_LETTERS; i++)
    {

        int key = abs(most_common_letter - commons[i]);
        char *plaintext = cezar_decipher(cipher, key);
        printf("%s key = %d -> %s\n", cipher, key, plaintext);
        free(plaintext);
    }
    return EXIT_SUCCESS;
}
