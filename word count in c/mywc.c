/************************************************************
 * filename: mywc.c
 *
 * A naive implementation of wc.c
 *
 * Version: 1.0
 * Author: Mark Fisher, CMP, UEA
 * Date: 03 Nov. 2016
 *
 ************************************************************/

#include <stdio.h>

int main()
{
  int ch;
  int linecount = 0;
  int wordcount = 0;
  int charcount = 0;
  int flag = 0;

  //Repeat until End Of File character is reached
  while ((ch = getchar()) != EOF) {
    // Increment character count if NOT new line or space
    if ((ch != ' ') && (ch != '\n')) {
      charcount++;
      flag = 0;
    }
    else {
      if (flag==0) {
        wordcount++;
        flag = 1;
      }
      charcount++;
    }

    // Increment line count if new line character
    if (ch == '\n') { linecount++; }

  }

  if (flag==0) wordcount++;

  printf(" %d %d %d\n", linecount, wordcount, charcount);

  getchar(); // consume EOF

  return(0);
}

