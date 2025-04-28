#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXN 1024
#define FILENAME_MAXN 1024

char * vigenere_encrypt(const char*plaintext, const char *key){
    int text_length = strlen(plaintext);
    int key_length=strlen(key);
    char*cipher=(char*)malloc(text_length+1);
    if(!cipher) return NULL;

   int j=0;

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(plaintext[i]))
        {

            int shift = tolower(key[j% key_length]) - 'a';
            if (islower(plaintext[i]))
            {
                cipher[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
            else
            {
                cipher[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            }
            
            j++;
        }
        else
        {
            cipher[i] = plaintext[i];
        }
    }
    cipher[text_length] = '\0';
    return cipher;
}

int main(){
    FILE *f_input=fopen("test1.txt","r");
    FILE *f_key =fopen("test2key.txt","r");
    FILE *f_output =fopen("test3.txt","w");

    if(!f_input || !f_key || !f_output){
        fprintf(stderr,"Greshka pri otv. na failovate.\n");
        return 1;
    }
    char plaintext[MAXN];
    char key[MAXN];
    
    fread(plaintext,1,MAXN,f_input);
    fread(key,1,MAXN,f_key);

    plaintext[strcspn(plaintext, "\r\n")]=0;
    key[strcspn(key, "\r\n")]=0;

    char*cipher=vigenere_encrypt(plaintext,key);
    if (cipher) {
        fprintf(f_output,"%s",cipher);
        free(cipher);
    }

    fclose(f_input);
    fclose(f_key);
    fclose(f_output);


    printf("zapisan e v test3.txt\n");
    return 0;
}
