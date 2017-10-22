#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char randomletter = ' ' + (rand() % 95); // space to ~
	return randomletter;
}

char *inputString()
{
	int i;
	int string_length = 6;
	char string[string_length + 1];
	char *str = (char*)malloc(string_length);
	for (i = 0; i < string_length-1; ++i) {
		string[i] = 'a' + rand() % 26; // a-z
	}
	string[string_length] = '\0';
	strcpy(str, string);
	return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
	int n;

	printf("Testing testme.\n");
	printf("Random Tests.\n");

	for (n = 0; n < 2000; n++)
	{
		testme();
	}
    
    return 0;
}
