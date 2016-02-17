#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define ASSERT_OK(object, pointer)\
        if(!object##_ok (pointer))\
        {\
                object##_dump (pointer);\
                assert(!"Bad object" #pointer);\
        }             

struct Node {
	char* q;
	struct Node* n;
	struct Node* y;
};

char tree_ok(struct Node* this)
{
	if(this == NULL) 
		return 0;
	if(this->n != NULL)
	{
		if(this->y == NULL)
			return 0;
		if(tree_ok(this->n) && tree_ok(this->y))
			return 1;
		return 0;
	}
	if(this->y != NULL)
        {
                if(this->n == NULL)
                        return 0;
                if(tree_ok(this->n) && tree_ok(this->y))
                        return 1;
                return 0;
       	}
        return 1;
}

char file_ok(FILE* this)
{
	if(this == NULL) 
		return 0;
	return 1;
}

void file_dump(FILE* this)
{
	printf("\n\n/////////// TREE DUMP //////////\n\n");
	printf("Cann't open file\n");
        printf("\n////////////////////////////////\n\n");
}

void tree_dmpprt(struct Node* this, int level)
{
        if(this == NULL)
        {
                printf("This tree wasn't create\n");
        }
        for(int i = 0; i < level; i++)
                printf("    ");
        printf("%s    %p    %p\n",this->q, this->n, this->y);
        if(this->y != NULL)
                tree_dmpprt(this->y, level + 1);
        if(this->n != NULL)
                tree_dmpprt(this->n, level + 1);
}

void tree_dump(struct Node* this)
{
	printf("\n\n/////////// TREE DUMP //////////\n\n");
	tree_dmpprt(this, 0);
	printf("\n////////////////////////////////\n\n");
}

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

	ASSERT_OK(file, in);

	char ch;
	fscanf(in, "%c", &ch);
	a = tree_load(in);
	fclose(in);

	ASSERT_OK(file, in)	

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

	ASSERT_OK(file, out)
	
	tree_print(t, out);
	fclose(out);
}

void tree_execute()
{
	char f = 1;
	struct Node* t = tree_create("save.txt");

	ASSERT_OK(tree, t)

	struct Node* root = t;
	while(f == 1)
	{	
		ASSERT_OK(tree, t)

		while(t->y != NULL)
			t = tree_ask(t);

		ASSERT_OK(tree, t)

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
			
		ASSERT_OK(tree, t)
		
		printf("Again?  y/n\n");
		a = getans();
		if(a == 'n')
			f = 0;
		t = root;
	}

	ASSERT_OK(tree, t)

	tree_save(t, "save.txt");

	ASSERT_OK(tree, t)

	tree_destroy(t);
}

int main()
{
	tree_execute();
	return 0;
}
