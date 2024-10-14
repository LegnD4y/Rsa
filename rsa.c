#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int
gcd(int e, int phi)
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
main()
{
  long long int p = 10007;
  long long int q = 10009;
  long long int n = p * q;
  long long int phi = (p - 1) * (q - 1);
  int e;
  int d;
  char msg[256] = "Mensagem\0";
  long long int encrypted[256];
  long long int decrypt[256];
  char decrypted[256];

  printf("P = %lld\tQ = %lld\n", p, q);
  printf("Phi = %lld\n", phi);

  for(e = 2; e < phi; e++)
  {
    if(gcd(e, phi) == 1)
    {
      break;
    }
  }
  
  printf("E = %d\n", e);
  
  for(d = 1; 1; d++)
  {
    if(((d * e) % phi) == 1)
    {
      break;
    }
  }
  
  printf("D = %d\n", d);
  
  printf("\nMensagem original =\n%s\n", msg);
 
  for(int i = 0; i < strlen(msg); i++)
  {
    long long int temp_e = e;
    for(encrypted[i] = 1; temp_e != 0; temp_e--)
    {
     encrypted[i] *= msg[i];
     encrypted[i] %= n;
    }
  }
  
  printf("\nMensagem criptografada =\n");
  for(int i = 0; i < strlen(msg); i++)
  {
    printf("%lld", encrypted[i]);
  }
  printf("\n");
  
  for(int i = 0; i < strlen(msg); i++)
  { 
    long long int temp_d = d;
    for(decrypt[i] = 1; temp_d != 0; temp_d--)
    {
      decrypt[i] *= encrypted[i];
      decrypt[i] %= n;
    }
  }

  for(int i = 0; i < strlen(msg); i++)
  {
    decrypted[i] = decrypt[i];
  }
  
  printf("\nMensagem descriptografada =\n%s\n", decrypted);

  return(0);
}

