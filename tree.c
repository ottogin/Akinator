#include<stdio.h>
#include<stdlib.h>

struct Node {
	char* q;
	struct Node* n;
	struct Node* y;
};

char* getstr(char det1, char det2)
{
        char* c = calloc(100, sizeof(char));
        char* r = c;
        char a;
        scanf("%c", &a);
        while(a == '\n')
        {
                scanf("%c", &a);
        }
        while(a != det1 && a != det2)
        {
                *r = a;
                scanf("%c", &a);
                r++;
        }
        *r = 0;
        return c;
}

struct Node* tree_load(FILE* in)
{
	struct Node* t = calloc(1, sizeof(struct Node));
	char* c = calloc(100, sizeof(char));
        char* r = c;
	char a;
	fscanf(in, "%c", &a);
	if(a == '(')
	{
		t->n = tree_load(in);
		a = '1';
	}
	else
	{
		*r = a; r++;
	}
	while(a != '(' && a!= ')')
	{
		fscanf(in, "%c", &a);
		*r = a;
		r++;
	}
	if(*(r - 1) == '(')
	{
		t->y = tree_load(in);
		fscanf(in, "%c", &a);
	}
	*(r - 1) = 0;
	t->q = c;
	return t;
}

struct Node* tree_create(char* name)
{
	struct Node* a;
	FILE* in = fopen(name, "r");
	char ch;
	fscanf(in, "%c", &ch);
	a = tree_load(in);
	fclose(in);
	return a;
}

void tree_destroy(struct Node* tree)
{
	if(tree == NULL)
		return;	
	tree_destroy(tree->y);
	tree_destroy(tree->n);
	free(tree);	
}

char getans()
{
	int c = 0;
	char a;
	scanf("%c", &a);
	while(a != 'y' && a != 'n')
	{
        	if(a == '\n' || a == ' ')
                {
                	scanf("%c", &a);
                        continue;
                }
                if(c % 4 == 0)
                        printf("What?\n");
                if(c % 4 == 1)
                       	printf("I did't understand!\n");
                if(c % 4 == 2)
                       	printf("Repeat please.\n");
                if(c % 4 == 3)
                       	printf("Are you fucking kidding me?\n");
                scanf("%c", &a);
                c++;
        }
	return a;
}

struct Node* tree_ask(struct Node* t)
{
	printf("%s   y/n\n", t->q);
	char a = getans();
	if(a == 'y')
		return t->y;
	return t->n;
}

void tree_print(struct Node* t, FILE* out)
{
	if(t == NULL)
		return;
	fprintf(out, "("); 
	tree_print(t->n, out);
	fprintf(out, "%s", t->q);
	tree_print(t->y, out);
	fprintf(out, ")");
}

void tree_save(struct Node* t, char* name)
{
	FILE* out = fopen(name, "w");
	tree_print(t, out);
	fclose(out);
}

void tree_execute()
{
	char f = 1;
	struct Node* t = tree_create("save.txt");
	struct Node* root = t;
	while(f == 1)
	{	
		while(t->y != NULL)
			t = tree_ask(t);
		printf("%s\n", t->q);
		printf("Am I right?  y/n\n");
		char a = getans();
		if(a == 'n')
		{
			struct Node* y = calloc(1, sizeof(struct Node));
			struct Node* n = calloc(1, sizeof(struct Node));
			n->q = t->q;
			n->y = NULL; n->n = NULL;
			printf("Who is he?\n");
			y->q = getstr('\n', '\n');
			y->y = NULL; y->n = NULL; 
			printf("Which question discriminate them?\n");
			t->q = getstr('\n', '\n');
			printf("Which answer?  y/n\n");
			a = getans();
			if(a == 'y')
			{
				t->y = y;	
				t->n = n;	
			}
			else
			{
				t->y = n;
				t->n = y;
			}
			printf("I rememer it..\n");
		}
		printf("Again?  y/n\n");
		
		a = getans();
		
		if(a == 'n')
			f = 0;
		t = root;
	}
	tree_save(t, "save.txt");
	tree_destroy(t);
}

int main()
{
	tree_execute();
	return 0;
}
