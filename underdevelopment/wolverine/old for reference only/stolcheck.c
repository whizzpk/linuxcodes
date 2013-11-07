#include<stdio.h>

int main(int argc[],char** argv[])
{
  int count;

  printf ("This program was called with \"%s\".\n",argv[0]);

  if (argc > 1)
    {
      for (count = 1; count < argc; count++)
	{
	  printf("argv[%d] = %s\n", count, argv[count]);
	}
    }
  else
    {
      printf("The command had no other arguments.\n");
    }

  
char num[10];

				/* Test a valid number		*/
  strcpy(num,"13");

  printf("%s(Oct) is %i(Dec)\n", num, strtol(num, NULL,  8));
  printf("%s(Dec) is %i(Dec)\n", num, strtol(num, NULL, 10));
  printf("%s(hex) is %i(Dec)\n", num, strtol(num, NULL, 16));

  puts("----------------------------------");

				/* Test a slightly valid number
				 * Returns the same results as 
				 * above. 			*/
  strcpy(num, "13hzcd");

  printf("%s(Oct) is %i(Dec)\n", num, strtol(num, NULL,  8));
  printf("%s(Dec) is %i(Dec)\n", num, strtol(num, NULL, 10));
  printf("%s(hex) is %i(Dec)\n", num, strtol(num, NULL, 16));

  puts("----------------------------------");

				/* Test an invalid number
				 * Returns ZERO			*/
  strcpy(num, "hzcd");

  printf("%s(Oct) is %i(Dec)\n", num, strtol(num, NULL,  8));
  printf("%s(Dec) is %i(Dec)\n", num, strtol(num, NULL, 10));
  printf("%s(hex) is %i(Dec)\n", num, strtol(num, NULL, 16));


  puts("----------------------------------");

				/* Test 0 base.
				 * This will look at the number 
				 * and decide the base for its self!
				 */
  strcpy(num, "13");
  printf("%s is %i(Dec)\n", num, strtol(num, NULL, 0));

  strcpy(num, "013");
  printf("%s is %i(Dec)\n", num, strtol(num, NULL, 0));

  strcpy(num, "0x13");
  printf("%s is %i(Dec)\n", num, strtol(num, NULL, 0));
return 0;


}
