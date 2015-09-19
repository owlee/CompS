// Reads the input file in plainTextFile.txt,
// character by character and then ex-ors them
// with the previous character.  To start things off,
// we ex-or the initial character with a given input.
// The output is then written to an output file.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// void encrypt(char *);
// void decrypt(char *);
char generateKeyByte();
void swap(int *, int *);

//int main(int argc, char **argv) {
int main() {
    // Constants
    FILE *keyFile;
    FILE *textFile;
    FILE *encryptedFile;

    char S[256];
    char T[256];
    char key[256];
    int kLength; //key length
    char inputChar;
    char outputChar;

    keyFile = fopen("./keyFile.txt", "r");
    textFile = fopen("./textFile.txt", "r");
    encryptedFile = fopen("./encryptedFile.txt", "w");

    assert(keyFile != NULL)
    assert(textFile != NULL)
    assert(encryptedFile != NULL)

    // store keys into the key array
    kLength=0;
    while (kLength<256 && (inputChar = fgetc(keyFile))!=EOF) {
      key[kLength] = inputChar;
      kLength++;
    }

    kLength = 256;
    for(int i=0; i<kLength; i++) {
        S[i] = i;
        T[i] = key[i % kLength];
    }

    //swap 2. initial permutation
    char temp;
    int j;

    for(int i=0; i<kLength; i++) {
        j = (j+S[i]+T[i]) % kLength;
        // temp = S[i];
        // S[i] = T[i];
        // T[i] = temp;
        swap(&S[i],&S[j]);
    }

    // do the generation and XOR
    while ((inputChar = fgetc(textFile))!=EOF) {
        outputChar = inputChar ^ generateKeyByte(S);
        fputc(outputChar, encryptedFile);
        // prevChar = outputChar;
    }

     //clean up
    fclose(keyFile);
    fclose(textFile);
    fclose(encryptedFile);

    printf("I have reached the end");
}

char generateKeyByte(char s[]) {
    static int i=0;
    static int j=0;
    char keyByte;
    i = (i+1) % 256;
    j = (j+S[i]) % 256;

    swap(&S[i],&S[j]);

    t = (S[i]+S[j]) % 256;
    return keyByte = S[t];
}

void swap(int *a, int *b) {
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;

   printf("Within swap function: a=%d; b=%d\n", *a, *b);

}
