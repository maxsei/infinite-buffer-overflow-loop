#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ADDR(x) (unsigned int)(long int)x
#define BOOLSTR(x) x ? "true" : "false"

int main(int argc, char *argv[])
{
  /* Parse command line arguments. */
  int n = 10;
  bool do_loop = true;
  switch (argc) {
    case 1:
      break;
    case 2:
      n = atoi(argv[1]);
      break;
    case 3:
      n = atoi(argv[1]);
      do_loop = (bool)atoi(argv[2]);
      break;
    default:
      fprintf(stderr, "got %d arguemnts expected at most 2\n", argc - 1);
      return 1;
  }

  /* Allocate 'arr' and 'i' as indexer of array. */
  int * arr = (int*)malloc(sizeof(int) * n);
  int * i = (int*)malloc(sizeof(int));
  *i = 0;

  /* Get the memory location of 'arr' and 'i' as integers. */
  /* int loc_arr = (long int)arr; */

  /* Print out the address locations of 'i' and 'arr' as well as the difference */
  /* in the addresses. */
  printf("addr(arr) = 0x%08X\n", ADDR(arr));
  printf("addr(i) = 0x%08X\n", ADDR(i));
  printf("\n");
  printf("addr(i) - addr(arr) = 0x%08X\n", ADDR(i) - ADDR(arr));
  printf("offset of 'i' from 'arr' in bytes = %i\n", ADDR(i) - ADDR(arr));

  /* Calculate the allocated bytes in the array between 'arr' and 'i'. */
  int allocated_bytes = 16 * ( (sizeof(int) * ( n + 1 ) / 16) + 1 );
  printf("offset of 'i' from 'arr' in bytes (calculated) = %d\n", allocated_bytes);
  printf("\n");

  /* Calculate padding between 'arr' and 'i'. */
  int padding = allocated_bytes / sizeof(int) - n;

  /* Print out padding information. */
  printf("padding = %i\n", padding);
  printf("padding in bytes = %i\n", padding * (int)sizeof(int));
  printf("padding (actual) in bytes = %i\n", ( ADDR(i) - ADDR(arr) ) - ( n * (int)sizeof(int) ));
  printf("\n");

  /* If not doing the loop then just exit. */
  if ( !do_loop )
    return 0;

  /* Loop through n+padding+1 setting the i'th element of the array to zero.
   * This is the same as iterating just outside the padding.
   *
   * Memory Layout:
   * n = 5;
   * array[ ##### ] padding[ --- ] i[ ]
   */
  printf("%-12s:%-3s:%-3s\n", "&(arr[*i])", "*i", "in bounds");
  for (; *i < n + padding + 1; ( *i )++) {
    arr[*i] = 0;
    printf("0x%08X: %03d %-5s\n",
        ADDR(&arr[*i]), *i, BOOLSTR(*i < n));
  }
}
