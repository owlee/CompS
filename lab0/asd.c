// Reads the input file in plainTextFile.txt,
// character by character and then ex-ors them
// with the previous character.  To start things off,
// we ex-or the initial character with a given input.
// The output is then written to an output file.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

char generateKeyByte(char S[]);

int main(void) {

   FILE *keyF, *textF, *encryptF;

   char inputChar;
   char outputChar;
   char prevChar;
   char S[256];
   char T[256];
   char key[256];
   char tempC;
   int i, j, kLength;

   keyF = fopen("./keyFile.txt", "r");
   textF = fopen("./plainText.txt", "r");

   encryptF = fopen("./encryptedText.txt", "w");

   assert(textF != NULL);
   assert(keyF != NULL);
   assert(encryptF != NULL);

   kLength=0;
   while (kLength<256 && (inputChar = fgetc(keyF))!=EOF) {
      key[kLength]= inputChar;
      kLength++;
  //    printf("hi %i", kLength);
   }
   for (i=0; i<256; i++){
      S[i]= i;
      T[i]= key[i %kLength];
   }

   j=0;
   for (i=0; i<256; i++){
      j=(j+S[i]+T[i]) % 256;
      tempC= S[j];
      S[i] = S[j];
      S[j] = tempC;
   }

     while ((inputChar = fgetc(textF))!=EOF) {
       outputChar = inputChar ^ generateKeyByte(S);
       fputc(outputChar, encryptF);
     }
    assert(fclose(keyF) == 0);
    assert(fclose(textF) == 0);
    assert(fclose(encryptF) == 0);
}


char generateKeyByte(char S[]){
   static int i=0;
   static int j=0;
   char temp, keyByte;
   int t;

   i= (i+1) % 256;
   j= (j+S[i]) % 256;
   temp= S[j];
   S[j]= S[i];
   S[j]= temp;

   t= (S[i]+S[j]) % 256;
   return keyByte = S[t];
}