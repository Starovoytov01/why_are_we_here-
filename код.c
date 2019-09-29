#include <stdio.h>
#include <string.h>
#include <malloc.h>

char * decToBin(int x)
{
	char *t = (char *)malloc(100);
	int i = 0;
	do
	{
		t[i++] = x % 2 + '0';
		x = x / 2;
	} while (x != 0);
	t[i] = '\0';
	// инвертируем t
	int k = strlen(t) - 2;
	int m = k / 2;
	for (int i = 0; i <= m; i++)
	{
		char tmp = t[i];
		t[i] = t[k - i + 1];
		t[k - i + 1] = tmp;
	}
	return t;
}

int main()
{
	int x;
	scanf("%d", &x);
	char *t = decToBin(x);
	puts(t);
}