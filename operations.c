#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "list.h"
#include "operations.h"

//after decimal point zeroes are added to get make numbers equal in length
void decimalEqual(number *a, number *b) {
	int i;
	if(a->afterpt > b->afterpt) {
		int diff = a->afterpt - b->afterpt;
		for(i = 0; i < diff; i++) {
			addDigit(b, '0');
			b->afterpt++;
		}
	}
	else if(b->afterpt > a->afterpt) {
		int diff = b->afterpt - a->afterpt;
		for(i = 0; i < diff; i++) {
			addDigit(a, '0');
			a->afterpt++;
		}
	}
}

//equals the length of both numbers by inserting zeros at start to small number.
void lengthEqual(number *a, number *b) {
	int gap;
	gap = length(*a) - length(*b);
	if(gap > 0) {
		int i = 0;
		while(i < gap) {
			insert_beg(b, 0);
			i++;
		}
	}
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		while(i < gap) {
			insert_beg(a, 0);
			i++;
		}
	}
}

//if number entered is zero
int zeroNumber(number a) {
	int i, flag = 0;
	nodeadt *p = a.head;
	for(i = 0; i < length(a); i++) {
		if(p->num != 0)
			flag = 1;
		 p = p->next;
	}
	return flag;
}

//copy number a in number b.
void copy(number *a, number *b) {
	int i, no, len;
	char ch;
	len = length(*a);
	nodeadt *t1 = a->head;
	for(i = 0; i < len; i++) {
		no = t1->num;
		ch = no + '0';
		addDigit(b, ch);
		t1 = t1->next;
	}
	b->afterpt = a->afterpt;
	b->sign = a->sign;
	return;
}
//Addition Operation
number *add(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	decimalEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = sub(b, a);
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = sub(a, b);
		}
	}
	else if(a->sign == b->sign) {
		int i, n1, n2, carry = 0, sum;
		int len_a, len_b;
		nodeadt *t1 = a-> prev;
		nodeadt *t2 = b-> prev;
		len_a = length(*a);
		len_b = length(*b);
		if(a->sign == MINUS)
			ans->sign = MINUS;
		else
			ans->sign = PLUS;
		if(len_a >= len_b) {
			for(i = 1; i <= len_b; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_beg(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_a - len_b; i++) {
				n1 = t1->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_beg(ans, sum);
				t1 = t1->prev;
			}
		}else {
			for(i = 1; i <= len_a; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_beg(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_b - len_a; i++) {
				n1 = t2->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_beg(ans, sum);
				t2 = t2->prev;
			}
		}
		ans->afterpt = a->afterpt;
		if(carry != 0)
			insert_beg(ans, carry);
	}
	return ans;
}


int compareEqual(number a, number b) {
	lengthEqual(&a, &b);
	decimalEqual(&a, &b);
	nodeadt *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;
		else if(p->num < q->num)
			return -1;
		p = p->next;
		q = q->next;
	}
	return 0;
}

number *sub(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);

	decimalEqual(a, b);
	lengthEqual(a, b);

	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = add(a, b);
			ans->sign = MINUS;
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = add(a, b);
			ans->sign = PLUS;
		}
	}
	else if(a->sign == b->sign) {
		if(a->sign == MINUS) {
			a->sign = b->sign = PLUS;
			ans = sub(b, a);
		}
		else if(a->sign == PLUS) {
			int n1, n2, diff, borrow = 0, i, len;
			nodeadt *t1 = a-> prev;
			nodeadt *t2 = b-> prev;

			len = length(*b);
			if(compareEqual(*a, *b) == 1) {
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;
						insert_beg(ans, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						insert_beg(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(compareEqual(*a, *b) == -1) {
				ans->sign = MINUS;
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						insert_beg(ans, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						insert_beg(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {
				if(compareEqual(*a, *b) == 0) {
					insert_beg(ans, 0);
				}
			}
		}
	}
	ans->afterpt = a->afterpt;
	return ans;
}

number *multiply(number *a, number *b) {
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);

	if((zeroNumber(*a) == 0) || (zeroNumber(*b) == 0)) {
		addDigit(ans, '0');
		return ans;
	}
	int lengthdiff;
	if(a->sign == b->sign) {
		ans->sign = PLUS;
		a->sign = b->sign = PLUS;
	}
	else {
		ans->sign = MINUS;
		a->sign = b->sign = PLUS;
	}
	lengthdiff = length(*a) - length(*b);
	if(lengthdiff < 0) {
		ans = multiply(b, a);
		return ans;
	}
	else {
		nodeadt *t1, *t2;
		int len_a = length(*a);
		int len_b = length(*b);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_a];
		for(i = 0; i < 2 *len_a; i++)
			tempresult[i] = 0;
		int k = 2 * len_a - 1;
		t2 = b-> prev;
		for(i = 0; i < len_b; i++) {
			t1 = a-> prev;
			int carry1 = 0, carry2 = 0;
			for(j = k - i; j > len_a - 2; j--) {
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->num * t2->num + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2;
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_a--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_a - 1 && i >= 0; i--) {
			insert_beg(ans, tempresult[i]);
		}
		ans->afterpt = a->afterpt + b->afterpt;
		return ans;
	}
}
//Division Operation.
number *division(number *m, number *n){
	if(zeroNumber(*n) == 0) {
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	zeroRemov(m);
	zeroRemov(n);

	int k = m->afterpt > n->afterpt ? m->afterpt : n->afterpt;
	int i = 0;

	while(i < k) {
		if(m->afterpt > 0)
			m->afterpt--;
		else
			addDigit(m, '0');
		if(n->afterpt > 0)
			n->afterpt--;
		else
			addDigit(n, '0');
		i++;
	}
	i = 9;
	number *c, *d, *ans, *q, *pro;
	c = (number *)malloc(sizeof(number));
	d = (number *)malloc(sizeof(number));
	ans = (number *)malloc(sizeof(number));
	pro = (number *)malloc(sizeof(number));
	q = (number *)malloc(sizeof(number));

	initNumber(ans);
	initNumber(c);
	initNumber(q);
	initNumber(d);
	if(m->sign == n->sign) {
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}
	nodeadt *p = m->head;
	char ch = p->num + '0';
	addDigit(d, ch);
	while(q->afterpt < SCALE){
		while(i >= 0){
			insert_beg(c, i);
			pro = multiply(n, c);
			ans = sub(d, pro);
			if(ans->sign != MINUS) {
				addDigit(q, i + '0');
				nodeadt *tmp = c->head;
				free(tmp);
				c->head = c-> prev = NULL;
				break;
			}
			else{
				nodeadt *tmp = c->head;
				free(tmp);
				c->head = c-> prev = NULL;
				i--;
			}
		}
		d = ans;
		if(p->next != NULL) {
			p = p->next;
			ch = p->num + '0';
			addDigit(d, ch);
		}
		else{
			q->afterpt++;
			addDigit(d, '0');
		}
		i = 9;
		nodeadt *tmp = c->head;
		free(tmp);
		c->head = c-> prev = NULL;
	}
	q->afterpt--;
	return q;
}

//FORMULA :- remainder = a - floor_division(a/b) * b
number *mod(number *a, number *b) {
	if(zeroNumber(*b) == 0) {
		printf("ERROR : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	int tempsign;
	if(a->sign == MINUS) {
		tempsign = MINUS;
		a->sign = b->sign = PLUS;
	}
	else {
		tempsign = PLUS;
		a->sign = b->sign = PLUS;
	}
	decimalEqual(a, b);
	int a_afterpt = a->afterpt;
	number *ans = (number *)malloc(sizeof(number));
	number *temp = (number *)malloc(sizeof(number));
	initNumber(ans);
	initNumber(temp);
	temp = division(a, b);
	if(temp->afterpt != 0) {
		int pos = length(*temp) - 1;
		while(temp->afterpt != 0) {
			remov(temp, pos);
			temp->afterpt--;
			pos--;
		}
	}
	temp = multiply(temp, b);
	ans = sub(a, temp);
	ans->sign = tempsign;
	ans->afterpt = a_afterpt;
	return ans;
}

number *compare(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (compareEqual(*a, *b)==1)
        	addDigit(result,'1');
	else addDigit(result,'0');
	return result;
}


number *isequal(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (compareEqual(*a, *b)==0 && compareEqual(*b, *a)==0)
        	addDigit(result,'1');
	else addDigit(result,'0');
	return result;
}

number *isnotequal(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (!(compareEqual(*a, *b)==0 && compareEqual(*b, *a)==0))
        	addDigit(result,'1');
	else addDigit(result,'0');
	return result;
}

number *logical_and(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (zeroNumber(*a)!=0 && zeroNumber(*b)!=0)
        	addDigit(result,'1');
	else addDigit(result,'0');
	return result;

}
number *logical_or(number *a, number *b){
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	if (zeroNumber(*a)!=0 || zeroNumber(*b)!=0)
        	addDigit(result,'1');
	else addDigit(result,'0');
	return result;

}
//Factorial Operation.
number *factorial(number *a) {
	if(a->afterpt != 0 || a->sign == MINUS) {
		printf("ERROR : Factorial of given number is not possible\n");
		exit(1);
	}
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	addDigit(ans, '1');
	number *b = (number *)malloc(sizeof(number));
	initNumber(b);
	addDigit(b, '1');
	while(compareEqual(*a, *b) > 0) {
		ans = multiply(a, ans);
		a = sub(a, b);
	}
	return ans;
}

//Power Operation.....gives ans = a^b
number *power(number *a, number *b) {
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	addDigit(ans, '1');
	number *n1 = (number *)malloc(sizeof(number));
	initNumber(n1);
	addDigit(n1, '1');
	number *n2 = (number *)malloc(sizeof(number));
	initNumber(n2);
	addDigit(n2, '2');
	number *n0 = (number *)malloc(sizeof(number));
	initNumber(n0);
	addDigit(n0, '0');
	number *c = (number *)malloc(sizeof(number));
	initNumber(c);
	copy(b, c);
	int sign = a->sign;
	if(b->sign == PLUS) {
		while(zeroNumber(*c) != 0) {
			ans = multiply(ans, a);
			c = sub(c, n1);
		}
	}
	else if(b->sign == MINUS) {
		while(zeroNumber(*c) != 0) {
			ans = division(ans, a);
			c = add(c, n1);
		}
	}
	a->sign = sign;
	if(a->sign == MINUS) {
		number *temp;
		temp = mod(b, n2);
		if(compareEqual(*temp, *n0) == 0)
			ans->sign = PLUS;
		else
			ans->sign = MINUS;
	}
	return ans;
}

