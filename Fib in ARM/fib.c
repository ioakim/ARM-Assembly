/**********************************************************************
 * fib.c - computes fibonacci numbers
 *
 * Version:	1.0
 * Author:	Mark Fisher, CMP, UEA
 * Date:	03.11.16
 **********************************************************************/

#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])

/* Write fibonacci number n to stdout, where n is provided as argv[1].
   n is expressed in decimal notation.  The fibonacci number is
   expressed in hexadecimal notation.  Return 0 iff successful. */

{
   int iNum;
   int iScanned;
   int iSuccessful;
   clock_t iInitialClock;
   clock_t iFinalClock;

   /* Validate the command line argument, and assign it to iNum. */

   if (argc != 2)
   {
      fprintf(stderr, "Usage: %s nonneginteger\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   iScanned = sscanf(argv[1], "%d", &iNum);
   if (iScanned != 1)
   {
      fprintf(stderr, "Argument must be an integer\n");
      exit(EXIT_FAILURE);
   }

   if (iNum < 0)
   {
      fprintf(stderr, "Argument must be non-negative\n");
      exit(EXIT_FAILURE);
   }

   /* Compute and write fib(iNum). */

   iInitialClock = clock();

   if (iNum < 2)
   {
      BigInt_T oBigInt = BigInt_new((unsigned int)iNum);
      BigInt_writeHex(stdout, oBigInt);
      putchar('\n');
      BigInt_free(oBigInt);
   }
   else
   {
      int i;
      BigInt_T oSecondPrev = BigInt_new(0);
      BigInt_T oFirstPrev = BigInt_new(1);
      BigInt_T oCurrent = NULL;
      BigInt_T oTemp = BigInt_new(0);

      for (i = 2; i <= iNum; i++)
      {
         oCurrent = oTemp;
         iSuccessful = BigInt_add(oFirstPrev, oSecondPrev, oCurrent);
         if (! iSuccessful)
         {
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
         }
         oTemp = oSecondPrev;
         oSecondPrev = oFirstPrev;
         oFirstPrev = oCurrent;
      }

      BigInt_writeHex(stdout, oCurrent);
      putchar('\n');

      BigInt_free(oTemp);
      BigInt_free(oFirstPrev);
      BigInt_free(oSecondPrev);
   }

   iFinalClock = clock();
   fprintf(stderr, "CPU time:  %f seconds\n",
      ((double)(iFinalClock - iInitialClock)) / CLOCKS_PER_SEC);

   return 0;
}
