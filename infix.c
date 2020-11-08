#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "stack.h"
#include "charstack.h"
#include "operations.h"
#include <limits.h>

#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400


typedef struct token{
	int type;
	union data{
	number *num;
	char op;
	}data;
}token;
enum state {START, NUMBER, POINT, OP, FINISH, ERROR, SPC };


token gettoken(char *expr, int *reset) {
	static int i = 0;
	number *a = (number *)malloc(sizeof(number));
	initNumber(a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
		    /*case START:
                switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						addDigit(a, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					case '.':
						nextstate = POINT;
						i++;
						break;

					default:
						nextstate = ERROR;
						break;
				}
*/
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						addDigit(a, currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = POINT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case POINT:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						addDigit(a, currchar);
						a->afterpt++;
						nextstate = POINT;
						currstate = nextstate;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = POINT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;

						return t;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '.':
						nextstate = POINT;
						t.type = OPERATOR;
						t.data.op = expr[i -1];
						currstate = nextstate;
						i++;
						return t;
						break;

					default: // anything else
						nextstate = ERROR;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						//no = currchar - '0';
						addDigit(a, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case '>': case '&': case '|': case '<': case '=': case '!':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					case '.':
						nextstate = POINT;
						i++;
						break;

					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

int precedance(char o) {
	switch(o) {
		case '>':
		case '<':
		case '=':
		case '!':
			return 6;
			break;
		case '&':
		case '|':
			return 7;
			break;
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
		default :
			return 5;
			break;
	}
}




number *infix(char *exp) {
	token t;
	char curr_op, prev_op, ch;
	int  cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	number *a, *b, *z;
	a = (number *)malloc(sizeof(number));
	b = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));
	initNumber(a);
	initNumber(b);
	initNumber(z);
	stack is;
	cstack cs;
	initnum(&is);
	charinit(&cs);
	prev = ERR;
	while(1) {
		t = gettoken(exp, &reset);
		curr = t.type;
		if(curr == prev && prev == OPERAND) {
			return NULL;
		}
		if(t.type == OPERAND){
			pushnum(&is, t.data.num);

		}
		else if(t.type == OPERATOR){
			curr_op = t.data.op;
			if(curr_op == '(')
				cnt_ob++;
			if(curr_op == ')')
				cnt_cb++;
			if(cnt_cb > cnt_ob)
				return NULL;
			if(!charisempty(&cs)) {
				prev_op = chartop(&cs);
				while(precedance(prev_op) >= precedance(curr_op)) {
					prev_op = charpop(&cs);
					if(!isemptynum(&is)) {
						a = popnum(&is);
					}
					else{
						charpush(&cs, prev_op);
						break;
					}
					if(!isemptynum(&is)) {
						b = popnum(&is);
					}
					else {
						charpush(&cs, prev_op);
						pushnum(&is, a);
						break;
					}
					if((prev_op == '/' || prev_op == '%') && a == 0) {
                        fprintf(stderr, "Mathematical error\n");
                        return NULL;
                    }
					switch (prev_op) {
						case '+' :
							//z = b + a;
							z = add(a, b);
							pushnum(&is, z);
							break;
						case '-' :
							//z = b - a;
							z = sub(b, a);
							pushnum(&is, z);
							break;
						case '*' :
							//z = b * a;
							z = multiply(b, a);
							pushnum(&is, z);
							break;
						case '/' :
							//z = b / a;
							z = division(b, a);
							pushnum(&is, z);
							break;
						case '%' :
							//z = b % a;
							z = mod(b, a);
							pushnum(&is, z);
							break;
			case '>':
				z = compare(b,a);
				pushnum(&is,z);
				break;
			case '<':
				z=compare(a,b);
				pushnum(&is,z);
				break;
			case '=':
				z=isequal(a,b);
				pushnum(&is,z);
				break;
			case '!':
				z=isnotequal(a,b);
				pushnum(&is,z);
				break;
                        case '&':
                            z = logical_and(b,a);
                            pushnum(&is,z);
                            break;
			case '|':
                            z = logical_or(b,a);
                            pushnum(&is,z);
                            break;

						case '(' :
							charpush(&cs, prev_op);
							pushnum(&is, b);
							pushnum(&is, a);
							break;
						default :
							return NULL;
					}
					if (prev_op == '(')
						break;
					if(!charisempty(&cs))
						prev_op = chartop(&cs);
					else
						break;
				}
			}
			charpush(&cs, t.data.op);
			if(curr_op == ')') {
				ch = charpop(&cs);
				cnt_cb--;
				ch = charpop(&cs);
				cnt_ob--;
			}
		}
		else if(t.type == END) {
			if(cnt_ob == cnt_cb) {
				while(!charisempty(&cs)) {
					if(!isemptynum(&is)) {
						a = popnum(&is);
					}
					else {
						fprintf(stderr, "Less operands\n");
                        return NULL;
					}
					if(!isemptynum(&is)) {
						b = popnum(&is);
					}
					else {
						fprintf(stderr, "Less operands\n");
                            return NULL;
					}
					ch = charpop(&cs);
					if((ch == '/' || ch == '%') && a == 0) {
						fprintf(stderr, "Mathematical error\n");
						return NULL;
					}
					switch(ch) {
						case '+' :
							z = add(b, a);
							pushnum(&is, z);
							break;
						case '-' :
							z = sub(b, a);
							pushnum(&is, z);
							break;
						case '*' :
							z = multiply(b, a);
							pushnum(&is, z);
							break;
						case '/' :
							z = division(b, a);
							pushnum(&is, z);
							break;
                        case '%' :
							//z = b % a;
							z = mod(b, a);
							pushnum(&is, z);
							break;
			case '>':
				z = compare(b,a);
				pushnum(&is,z);
				break;
			case '<':
				z=compare(a,b);
				pushnum(&is,z);
				break;
                        case '=':
				z=isequal(a,b);
				pushnum(&is,z);
				break;
			case '!':
				z=isnotequal(a,b);
				pushnum(&is,z);
				break;
			case '&':
                            z = logical_and(b,a);
                            pushnum(&is,z);
                            break;
			case '|':
                            z = logical_or(b,a);
                            pushnum(&is,z);
                            break;
						default :
							return NULL;
					}
				}
			}
			else {
				fprintf(stderr, "Error in Expression\n");
            	return NULL;
			}
			if(!isemptynum(&is)){
				z = popnum(&is);
				if(isemptynum(&is))
					return z;
				else {
                fprintf(stderr, "Less Operators\n");
                    return NULL;
                }
			}
			else {
				fprintf(stderr, "Less Operands\n");
				return NULL;
			}
		}
		else if(t.type == ERR) {
			return NULL;
		}
		prev = curr;
	}
}

int readline(char *line, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			line[i++] = '\0';
			return i - 1;
		}
		else
			line[i++] = ch;
	}
	line[len - 1] = '\0';
	return len - 1;
}

int main() {
	number *r;
	char line[2048];
	while(readline(line, 2048)) {
		r = infix(line);
		if(r != NULL)
			printNumber(*r);
		else
			fprintf(stderr, "Error in expression\n");
	}
	return 0;
}

