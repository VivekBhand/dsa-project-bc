typedef struct chnode {
	char a;
	struct cnode *p;
}chnode;
typedef chnode *cstack;
void charinit(cstack *s);

void charpush(cstack *s, char t);

char charpop(cstack *s);

int charisempty(cstack *s);

char chartop(cstack *s);

