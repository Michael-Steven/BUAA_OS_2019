/************************************************************************
    > File Name: user/testbss.c
    > Author: Michael_Shan
    > Mail: 727950731@qq.com 
    > Created Time: Sat May 25 17:45:12 2019
************************************************************************/

#include "lib.h"

#define ARRAYSIZE (1024*10)

int bigarray[ARRAYSIZE]={0};

void

umain(int argc, char **argv)

{

	int i;

	writef("Making sure bss works right...\n");

	for(i = 0;i < ARRAYSIZE; i++)

		if(bigarray[i]!=0)

			user_panic("bigarray[%d] isn't cleared!\n",i);

	for (i = 0; i < ARRAYSIZE; i++)

		bigarray[i] = i;

	for (i = 0; i < ARRAYSIZE; i++)

		if (bigarray[i] != i)

			user_panic("bigarray[%d] didn't hold its value!\n", i);

	writef("Yes, good. Now doing a wild write off the end...\n");

	bigarray[ARRAYSIZE+1024] = 0;

	user_panic("SHOULD HAVE TRAPPED!!!");

}
