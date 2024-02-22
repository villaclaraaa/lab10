#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct books
{
	char name[50];
	char author[50];
	int pages;
	int cost;
	struct books* next;
};
