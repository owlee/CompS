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

int main(void) {

    // Constants
    FILE *ifp;
    FILE *ofp;
    FILE *key_stream;

    // char inputChar;
    // char outputChar;
    // char prevChar;
    // int i;

    key_stream = fopen("./keyFile.txt", "r");
     
    // 2. 
    count length of key_stream
        with conditions

    // 3.
    ifp = fopen("./plaintText.txt", "r");
    read ofp char by char
    For each char read generate the next element of key stream
    XOR key byte with the byte that was read^
    Write the resulting byte (char) into a file
    ofp = fopen("./encryptedText.txt")



    // assert(ifp != NULL);
    // assert(ofp != NULL);

    // prevChar = 'i';

    //  while ((inputChar = fgetc(ifp))!=EOF) {
    //    outputChar = inputChar ^ prevChar;
    //    fputc(outputChar, ofp);
    //    prevChar = outputChar;
    //  }
    fclose(ifp);
    fclose(ofp);
}

// Generates a keystream into a folder called keyFile.txt
int generateStream(void) {
    
    FILE *key_stream;

    key_stream = fopen("./keyFile.txt", "w");

    S[i]=i;
    T[i] = key[i mod klength];

    j=0;
    
    // initial permutation
    for (i=0; i<256; i++) {
        j = (j+S[i]+T[i]) mod 256
        swap S[i] and S[j]
    }

    char generateKeyByte(char s[]) {
        static int i=0
        static int j=0
        i = (i+1) mod 256
        j = (j+S[i]) mod 256
        Swap S[i] and S[j]
        t = (S[i]+S[j]) mod 256
        return keyByte = S[t]
    }

    fclose(key_stream);


}
