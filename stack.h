#include "list.h"


typedef struct node {
	number *a;
	struct inode *p;
}node;
typedef node *stack;
void initnum(stack *s);

void pushnum(stack *s, number *a);

number *popnum(stack *s);

int isemptynum(stack *s);


