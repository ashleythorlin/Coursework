#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char* bytesToHex(unsigned char* bytes, int numBytes)
{
  int numHex = 2 * numBytes; //number of hex characters

  //hex string that will be returned
  char *hex = malloc(sizeof(char) * (numHex + 1));
  hex[numHex] = '\0'; //make sure string is null-terminated

  int j = 0;
  //Go thru byte array 4 bits at a time
  for(int i = 0; i < numHex; i++)
  {
    if(i % 2 == 0)
      hex[i] = (bytes[j] & 240) >> 4;
    else
    {
      hex[i] = (bytes[j] & 15);
      j++;
    }
  }

  //map int values to hex characters
  for(int i = 0; i < numHex; i++)
  {
    switch(hex[i])
    {
      case 0 ... 9:
        hex[i] += '0';
        break;

      case 10 ... 15:
        hex[i] += 'a' - 10;
        break;
    }
  }
  return hex;
}

int main()
{
  char *text = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  char *answer = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  char *key = "ICE";
  unsigned char bytesXOR[strlen(text)];

  //Encrypt text using repeating-key XOR (ICE)
  for(int i = 0; i < strlen(text); i++)
  {
    bytesXOR[i] = text[i] ^ key[i % 3];
  }

  char *hex = bytesToHex(bytesXOR, strlen(text)); //hex string of bytes array

  if(strcmp(answer, hex) == 0)
    printf("Success!\n");

  else
    printf("Failure!\n");

  free(hex);

}