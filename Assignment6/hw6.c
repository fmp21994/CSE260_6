#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)

typedef enum {diploma, bachelor, master, doctor} education;
void flush(); // forward declaration of functions
void branching(char c);
int insertion();
struct person *search(char *sname);
void deletion(char *sname);
void print_all();
void sort(struct person* someone);

struct person {	 // a node to hold personal details
    char name[30];
    char email[30];
    int phone;
    education degree;
    struct person* next;
} *top = NULL;



int main() {    // print a menu for selection
    char ch = 'i';
    
    ungetc('\n', stdin); // inject the newline character into input buffer
    
    do {
        printf("Enter your selection\n");
        printf("\ti: insert a new entry\n");
        printf("\ts: search an entry\n");
        printf("\td: delete an entry\n");
        printf("\tp: print all entries\n");
        printf("\tq: quit \n");
        
        flush();	// flush the input buffer. To be discussed later
        ch = tolower(getchar());
        branching(ch);
    } while (ch != 113);
    return 0;
}

void flush() {	// flush the input buffer. To be discussed later
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void branching(char c) {    // branch to different tasks
    char sname[30], delete[30];
    struct person* found;
    switch (c) {
        case 'i': insertion();
            break;
        case 's':
            printf("Please enter a name to search for.\n");
            scanf("%s", sname);
            found = search(sname);
            if (found == NULL)
            {
                printf("Match not found.\n");
            }
            break;
        case 'd':
            printf("Please enter a name to delete.");
            scanf("%s", delete);
            deletion(delete);
            break;
        case 'p':print_all();
            break;
        case 'q':
            break;
        default:
            printf("Invalid input\n");
    }
}

int insertion()
{    // insert a new entry at the end
    education degree;
    struct person *person;
    person = (struct person *) malloc(sizeof(struct person));
    if(person == 9)
    {
        printf("Out of memory\n"); return -1;
    }
    printf("Enter name, phone, email, degree (0-3):\n");
    scanf("%s", person->name);
    scanf("%d", &person->phone);
    scanf("%s", person->email);
    scanf("%d", &person->degree);
    sort(person);
    return 0;
}

void sort(struct person* person)
{
    struct person *b = top;
    
    // Case 1 (is empty)
    if (top == NULL || strcmp(top->name,person->name) >= 0)
    {
        person->next = top;
        top = person;
    }
    else
    {
        if (strcmp(person->name, top->name) < 0)
        {
            person->next = top;
            top = person;
        }
        else
        {
            struct person *index = top;
            while ((index != NULL) && (strcmp(person->name, index->name) >= 0))
            {
                        b = index;
                        index = index->next;
            }
        person->next = b->next;
        b->next = person;
        }
    }
}
struct person *search(char *sname)
{
    struct person *p = top, *b = 0, *r;
    while (p != 0)
        if (strcmp(sname, p->name) == 0) {
            printf("%s\n", p->name);
            printf("%d\n", p->phone);
            printf("%s\n", p->email);
            printf("%d\n", p->degree);
            return b;
        }
        else
        {
            b = p;
            p = p->next;
        }
    return 0;
}

void deletion(char *sname)
{
    
        struct person *b, *t;
        if (top == 0)  return;		// nothing to delete
        b = search(sname);		// find the position
        if (b == 0) {	// free head	  // case 1
            t = top;
            top = top->next;
            return;
        }
        if (b->next->next == 0)	{ // case 2
            t = b->next;
            b->next = 0;
            return;
        } else {
            t = b->next;
            b->next = t->next; // case 3
            return;
        }
}

void print_all()
{
    struct person* position = top;
    while (position != NULL)
    {
        printf("%s\n", position->name);
        printf("%d\n", position->phone);
        printf("%s\n", position->email);
        printf("%d\n", position->degree);
        position = position->next;
    }
    
}