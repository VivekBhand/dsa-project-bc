#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initNumber(number *a) {
	a->head = a-> prev = NULL;
	a->afterpt = 0;
	a->sign = PLUS;
}
void addDigit(number *a, char ch) {
	if(ch < '0' || ch > '9')
		return;
	nodeadt *tmp = (nodeadt *)malloc(sizeof(nodeadt));
	if(tmp == NULL)
		return;
	tmp->num = ch - '0';
	tmp->next = NULL;
	if((a->head == NULL) && (a-> prev == NULL)) {
		tmp->prev = NULL;
		a->head = tmp;
		a-> prev = tmp;
		return;
	}
	tmp->prev = a-> prev;
	a-> prev->next = tmp;
	a-> prev = tmp;
	return;
}
int length(number c) {
	nodeadt *p;
       	p = c.head;
	int count = 0;
	while(p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}
void insert_beg(number *c, int no) {
	if(no < 0 || no > 9)
		return;
	nodeadt *tmp = (nodeadt *)malloc(sizeof(nodeadt));
	if(!tmp)
		return;
	tmp->num = no;
	tmp->prev = NULL;
	if((c->head == NULL) && (c-> prev == NULL)){
		tmp->next = NULL;
		c->head = c-> prev = tmp;
		return;
	}
	tmp->next = c->head;
	c->head->prev = tmp;
	c->head = tmp;
	return;
}
void remov(number *a, int pos){
	int i;
	nodeadt *p, *tmp;

	if(pos < 0 || pos >= length(*a))
		return;

	p = a->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(a->head == NULL) {
		return;
	}
	if(length(*a) == 1) {
		a->head = a-> prev = p = NULL;
		return;
	}
	if(pos == 0) {
		p->next->prev = NULL;
		a->head = p->next;
		free(p);
		return;
	}
	if(pos == length(*a) - 1) {
		tmp = p->next;
		p->next = NULL;
		a-> prev = p;
		free(tmp);
		return;
	}

	tmp = p->next;
	p->next = p->next->next;
	tmp->next->prev = p;
	free(tmp);
	return;
}
//Function to remove extra zeroes on left of number.
void zeroRemov(number *a) {
	nodeadt *p = a->head;
	int i, len = length(*a);
	for(i = 0; i < len - a->afterpt -1; i++) {
		if(p->num == 0) {
			a->head = p->next;
			p->next = NULL;
			a->head->prev = NULL;
			free(p);
			p = a->head;
		}else {
			break;
		}
	}
	p = a-> prev;
	int decimal = a->afterpt;
	for(i = 0; i < decimal - 1; i++) {
		if(p->num == 0) {
			a-> prev = p->prev;
			p->prev = NULL;
			a-> prev->next = NULL;
			free(p);
			p = a-> prev;
			a->afterpt--;

		}else {
			break;
		}
	}
	return;
}
void printNumber(number c) {
	nodeadt *p;
	int pos = 0;
	zeroRemov(&c);
	p = c.head;
	if(c.sign == MINUS) {
		printf("-");
		c.sign = PLUS;
	}
	while(p != NULL) {
		pos++;
		if(pos == (length(c) - c.afterpt + 1))
			printf(".");
		printf("%d", p->num);
		p = p->next;
	}
	printf("\n");
}
