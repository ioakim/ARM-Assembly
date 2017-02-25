/**********************************************************************
 * bigintprivate.h
 *
 * Author:	Mark Fisher, CMP, UEA
 * Date:	03.11.16
 **********************************************************************/

#ifndef BIGINTPRIVATE_INCLUDED
#define BIGINTPRIVATE_INCLUDED

enum {MAX_DIGITS = 32768};   /* Arbitrary */

struct BigInt
{
   int iLength;
   /* The number of used digits (<= MAX_DIGITS) in the BigInt
      object */

   unsigned int auiDigits[MAX_DIGITS];
   /* The digits comprising the BigInt object */
};

#endif
