CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c -g  $(CFLAGS)

clean:
	 rm -f *.o testme.exe testme  *.gcov *.gcda *.gcno *.so
