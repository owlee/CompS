// Reads the input file in plainTextFile.txt,
// character by character and then ex-ors them
// with the previous character.  To start things off,
// we ex-or the initial character with a given input.
// The output is then written to an output file.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// void encrypt(char *);
// void decrypt(char *);
char generateKeyByte();
void swap(char *, char *);
void generate(char*,char*, char*);

//int main(int argc, char **argv) {
int main(void){
    // Constants
    FILE *keyFile, *textFile, *encryptedFile;

    char* keyF = "./keyFile.txt";

    // Encryption --uncomment
    char* inputF = "./plainTextFile.txt";
    char* outputF = "./encryptedFile.txt";

    // Decryption --uncomment
   // char* inputF = "./encryptedFile.txt";
   // char* outputF = "./decyptedFile.txt";

    // swap keyFile and encryptedFile to do decryption
    generate(inputF, outputF, keyF);

    printf("Output file has been generated!");
}

void generate(char* inputF, char* outputF, char* keyF) {

    // Opening the files
    FILE* inf = fopen(inputF, "r");
    FILE* outf = fopen(outputF, "w");
    FILE* keyf = fopen(keyF, "r");

    char S[256], T[256], key[256];
    int kLength; //key length
    char inputChar, outputChar;

    assert(inf != NULL);
    assert(outf != NULL);
    assert(keyf != NULL);

    // store keys into the key array
    kLength=0;
    while (kLength<256 && (inputChar = fgetc(keyf))!=EOF) {
      key[kLength] = inputChar;
      kLength++;
    }

    kLength = 256;
    int i=0;
    while(i<kLength){
        S[i] = i;
        T[i] = key[i % kLength];
    }

    // initial permutation
    char temp;
    int j;
    i=0;
    while(i<kLength) {
        j = (j+S[i]+T[i]) % kLength;
        swap(&S[i],&S[j]);
    }

    // do the generation and XOR
    while ((inputChar = fgetc(inf))!=EOF) {
        outputChar = inputChar ^ generateKeyByte(S);
        fputc(outputChar, outf);
    }

     // clean up
    fclose(inf);
    fclose(outf);
    fclose(keyf);
}

char generateKeyByte(char S[]) {
    int i=0, j=0, t=0;
    char keyByte;

    i = (i+1) % 256;
    j = (j+S[i]) % 256;

    swap(&S[i],&S[j]);

    t = (S[i]+S[j]) % 256;
    return keyByte = S[t];
}

void swap(char *a, char *b ) {
   char temp;
   temp = *a;
   *a = *b;
   *b = temp;
}
