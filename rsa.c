#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int
gcd(long long int e, long long int phi)
{
  while(phi != 0)
  {
    int temp = phi;
    phi = e % phi;
    e = temp;
  }

  return(e);
}

int
pick_e(long long int phi)
{
  if((65537 < phi) && (gcd(65537, phi)))
  {
    return(65537);
  }

  for(long long int e = 2; e < phi; e++)
  {
    if(gcd(e, phi) == 1)
    {
      return(e);
    }
  }
  return(-1);
}

int
pick_d(long long int e, long long int phi)
{
  for(long long int d = 1; 1; d++)
  {
    if(((d * e) % phi) == 1)
    {
      return(d);
    }
  }
}

void
encrypt(long long int e, long long int n, char* msg, long long int* encrypted)
{
  for(int i = 0; i < strlen(msg); i++)
  {
    long long int temp_e = e;
    for(encrypted[i] = 1; temp_e != 0; temp_e--)
    {
     encrypted[i] *= msg[i];
     encrypted[i] %= n;
    }
  }
}

void
decrypt(long long int d, long long int n, char* msg, long long int* encrypted, long long int* decrypted, char* msg_decrypted)
{
  for(int i = 0; i < strlen(msg); i++)
  { 
    long long int temp_d = d;
    for(decrypted[i] = 1; temp_d != 0; temp_d--)
    {
      decrypted[i] *= encrypted[i];
      decrypted[i] %= n;
    }
  }

  for(int i = 0; i < strlen(msg); i++)
  {
    msg_decrypted[i] = decrypted[i];
  }
}

int
main()
{
  long long int p = 7393;
  long long int q = 13759;
  long long int n = p * q;
  long long int phi = (p - 1) * (q - 1);
  long long int e = 0;
  long long int d = 0;
  char msg[256] = "3100C0019D6D\0";
  long long int encrypted[256];
  long long int decrypted[256];
  char msg_decrypted[256];

  printf("P = %lld\tQ = %lld\n", p, q);
  printf("Phi = %lld\n", phi);

  e = pick_e(phi);

  printf("E = %lld\n", e);
  
  d = pick_d(e, phi);
   
  printf("D = %lld\n", d);
  
  printf("\nMensagem original:\n%s\n", msg);
 
  encrypt(e, n, msg, encrypted);
  
  printf("\nMensagem criptografada:\n");
  for(int i = 0; i < strlen(msg); i++)
  {
    printf("%lld,", encrypted[i]);
  }
  printf("\n");
  
  decrypt(d, n, msg, encrypted, decrypted, msg_decrypted);
  
  printf("\nMensagem descriptografada:\n%s\n", msg_decrypted);

  FILE *file_text = fopen("rfid.txt","wt");
  FILE *file_bi = fopen("rfid.byte","wb");

  for(int i = 0; i < strlen(msg); i++)
  {
    fwrite(&encrypted[i], sizeof(long long int), 1, file_bi);
    fprintf(file_text,"%lld,", encrypted[i]);
  }
  fprintf(file_text,"0");

  fclose(file_bi);
  fclose(file_text);

  file_bi = fopen("rfid.byte","rb");

  for(int i = 0; i < strlen(msg); i++)
  {
    fread(&decrypted[i], sizeof(long long int), 1, file_bi);
  }

  decrypt(d, n, msg, encrypted, decrypted, msg_decrypted);
  
  printf("\nMensagem descriptografada:\n%s\n", msg_decrypted);
  
  fclose(file_bi);

  return(0);
}

