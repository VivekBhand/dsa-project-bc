#include<stdlib.h>
#include "stack.h"


void initnum(stack *s) {
	*s = NULL;
}
void pushnum (stack *s, number *t) {
	stack temp;
	temp = (node *)malloc(sizeof(node));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}
number *popnum(stack *s) {
	number *t;
	stack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}
int isemptynum (stack *s) {
	return *s == NULL;
}

