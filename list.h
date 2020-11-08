#define PLUS 1
#define MINUS -1

typedef struct nodeadt {
	int num;
	struct nodeadt *next, *prev;
}nodeadt;

typedef struct number {
	int sign, afterpt;
	nodeadt *head, * prev;
}number;

void initNumber(number *a);
void addDigit(number *a, char ch);
void printNumber(number a);
void destroyNumber(number *a);
void insert_beg(number *a, int no);
int length(number a);
void remov(number *a, int pos);

void zeroRemov(number *a);
