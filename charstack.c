#include "charstack.h"
#include <stdlib.h>

void charinit(cstack *s) {
	*s = NULL;
}
void charpush (cstack *s, char t) {
	cstack temp;
	temp = (chnode *)malloc(sizeof(chnode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}
char charpop(cstack *s) {
	char t;
	cstack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}
int charisempty (cstack *s) {
	return *s == NULL;
}
char chartop(cstack *s) {
	char ch;
	ch = charpop(s);
	charpush(s, ch);
	return ch;
}

