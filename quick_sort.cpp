#include <stdio.h>
#include <stdlib.h>
#include "any_stack.h"
// diff input output | wc -l

#define swap(x, y){   \
	__typeof(x) temp = x;  \
	x = y;    \
	y = temp;   \
}

typedef struct QuickArgs
{
	int* num, l, r, x, y;
	int status;
} QuickArgs;

QuickArgs* getNewQuick(int *num, int l, int r)
{
	QuickArgs *p = (QuickArgs*)malloc(sizeof(QuickArgs));
	p->num = num;
	p->l = l;
	p->r = r;
	p->status = 0;
	return p;
}
void quick_sort(int *num, int l, int r)
{
	Stack* s = init_stack(1000, QuickArgs);
	QuickArgs *temp_args = getNewQuick(num, l, r), *p_args;
	push_stack(s, temp_args);
	while (!empty_stack(s))
	{
		p_args = top_stack(s, QuickArgs);
		switch (p_args->status)
		{
			case 0:
				//int x = p_args->l, y = p_args->r;
				if (p_args->l < p_args->r)
				{
					int x = p_args->l, y = p_args->r;
					int ans = p_args->num[x];
					do
					{
						while (p_args->num[x] < ans) x++;
						while (p_args->num[y] > ans) y--;
						if (x <= y)
						{
							swap(p_args->num[x], p_args->num[y])
							x++, y--;
						}
					}while (x < y);
					p_args->x = x;
					p_args->y = y;
					temp_args->num = p_args->num;
					temp_args->l = x;
					temp_args->r = p_args->r;
					temp_args->status = 0;
					push_stack(s, temp_args);
					p_args->status = 1;
				}
				else
				{
					p_args->status = 100;
				}
				break;
			case 1:
				p_args->r = p_args->y;
				p_args->status = 0;
				break;
			case 100:
				pop_stack(s);
				break;
		}
	}
	free(temp_args);
	clear(s);
}

void __quick_sort(int *num, int l, int r)
{
	while (l < r)
	{
		int x = l, y = r;
		int ans = num[x];
		do
		{
		    while (num[x] < ans) x++;
	 	    while (num[y] > ans) y--;
			if (x <= y)
			{
				swap(num[x], num[y]);
				x++, y--;
			}
		}while (x < y);
		__quick_sort(num, x, r);
		r = y;
	}
}

int main()
{
	FILE* fin = fopen("./input", "r");
	FILE* fout = fopen("./output2", "w");
	int n;
	fscanf(fin,"%d", &n);
	int *num = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		fscanf(fin, "%d", &num[i]);
	}

	quick_sort(num, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		fprintf(fout, "%d\n", num[i]);
	}

	free(num);

	return 0;
}

