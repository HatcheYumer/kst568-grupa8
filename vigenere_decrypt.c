#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1024

char *vigenereDecrypt(char *cipher, char *key)
{
    int text_length = strlen(cipher);
    int key_length = strlen(key);

    char *plaintext = (char *)malloc(sizeof(char) * (text_length + 1));
    memset(plaintext, '\0', sizeof(char) * (text_length + 1));

    for (int i = 0; i < text_length; i++)

    {
        if (isalpha(cipher[i]))
        {

            int shift = tolower(key[i % key_length]) - 'a';
            if (islower(cipher[i]))
            {
                plaintext[i] = (cipher[i] - 'a' - shift+26) % 26 + 'a';
            }
            else
            {
                plaintext[i] = (cipher[i] - 'A' - shift+26) % 26 + 'a';
            }
        }
        else
        {
            plaintext[i] = cipher[i];
        }
    }
    plaintext[text_length] = '\0';
    return plaintext;
}

int read_data(char *filename, char *data)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("The file does not exits.");
        return EXIT_FAILURE;
    }

    if (fgets(data, MAXN, fp) == NULL)
    {
        printf("Error reading from file.");
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

void write_text(char* filename, char* text)
{
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "%s", text);
    fclose(fp);
}

int main()
{

    char cipher_filename[MAXN];
    printf("Enter cipher file: ");
    scanf("%s", cipher_filename);

    char cipher[MAXN];
    read_data(cipher_filename, cipher);

    char key_file[MAXN];
    printf("Enter key file: ");
    scanf("%s", key_file);
    char key[MAXN];
    read_data(key_file, key);

    char output_file[MAXN];
    printf("Enter output file: ");
    scanf("%s", output_file);

    char *result = vigenereDecrypt(cipher, key);
    
    write_text(output_file, result);
    printf("%s", result);
    free(result);
    return EXIT_SUCCESS;
}
