#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
struct cell{
    struct cell *next;
    int data;
};
typedef struct cell cell_t;
cell_t *
list_alloc(int data)
{
    cell_t *new = NULL;

    new = (cell_t *)malloc(sizeof(cell_t));
    if(new == NULL){
        fprintf(stderr, "ERROR: list_alloc(): %s\n", strerror(errno));
        return(NULL);
    }

    new->next = NULL;
    new->data = data;

    return(new);
}
int
list_add(cell_t *header, int data)
{
    cell_t *next = NULL;
    cell_t *prev = header;
    next = list_alloc(data);
    if(next == NULL) return(-1);
   while(prev->next != NULL){
        prev = prev->next;
    }
    prev->next = next;

    return(0);
}  
void
list_free(cell_t *header)
{
    cell_t *temp = header;
    cell_t *swap = NULL;

    while(temp != NULL){
        swap = temp->next;
        free(temp);
        temp = swap;
    }
}
static void
list_print(cell_t *header)
{
    cell_t *p = header;

    printf("list{ ");
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("}\n");
}
int main(int argc, char *argv[]) 
{
    char str[5];
    int n;
    int index = 0;
    cell_t *header = list_alloc(0);
    if(header == NULL) return(-1);
    while(fgets(str, sizeof(str), stdin)){
        n = atoi(str);
        if(n==0){
        list_print(header);
        }
        if(n==-1){
            list_free(header);
        }
        else{
            str[index++]=n;
            list_add(header, str);
        }
        
        
    }
list_free(header);
    return 0;
}
