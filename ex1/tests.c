#include "tests.h"
#include "cipher.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define K_1 3
#define K_2 2
#define K_3 (-1)
#define K_4 (-3)
#define K_5 29

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "!,xy z";
  char out[] = "!,za b";
  cipher (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "!,bc d";
  char out[] = "!,ab c";
  cipher (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
  char in[] = "cde";
  char out[] = "zab";
  cipher (in, K_4);
  return strcmp (in, out) != 0;
}


// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
  char in[] = "FGR";
  char out[] = "IJU";
  cipher (in, K_5);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char out[] = "abc";
  char in[] = "def";
  decipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
  char out[] = "!,xy z";
  char in[] = "!,za b";
  decipher (in, K_2);
  return strcmp (in, out) != 0;}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char out[] = "!,bc d";
  char in[] = "!,ab c";
  decipher (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k () {
  char out[] = "cde";
  char in[] = "zab";
  decipher (in, K_4);
  return strcmp (in, out) != 0;
}
// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
  char out[] = "FGR";
  char in[] = "IJU";
  decipher (in, K_5);
  return strcmp (in, out) != 0;
}
