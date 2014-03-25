#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef char ElementType;

typedef struct _Element {
    ElementType inner_value;
    struct _Element *next;
} Element;

typedef struct _Queue {
    Element * front;
    Element * back;
    int32_t length;
}  Queue;

Element *alloc_element(void);
Element *init_element(Element *, ElementType);

Queue *alloc_queue(void);
void init_queue (Queue *);

int8_t is_empty(Queue * q);
Element *whois_front(Queue * q);
Element *whois_back(Queue * q);

void queue_element (Queue *q, Element * e);
Element * dequeue_element (Queue * q);

void deep_free (Queue * q);

void print_queue(Queue *q);

int main(){

    Element *e;
    ElementType elc;
    int32_t option, i;
    char input[255];
    input[254] = 0;
    
    Queue *q = alloc_queue();
    
    if (q == NULL){
        printf("Error en creación de cola, memoria insuficiente.\n");
        return 1;
    }
    
    printf("Programa para manejo de cola de caracteres\n");
    init_queue(q);
    
    do {

        printf ("\n\n================\n");
        if (!is_empty(q)){
            printf ("\tCaracter incial: %c\n", whois_front(q)->inner_value );
            printf ("\tCaracter final: %c", whois_back(q)->inner_value );
        }else{
            printf("Cola vacía.");
        }
        printf ("\n================\n\n");

        printf("Menú principal.\n0 - Salir.\n1 - Poner caracter en cola.\n2 - Quitar caracter de cola.\n"
                "3 - Imprimir cola.\nIngrese una opción (0-3): ");
        gets(input);
        if (strlen(input) > 1 || !isdigit(input[0])){
            printf("Debe ingresar un número entero de entre 0 y 3.\n");
            continue;
        }
        option = atoi(input);

        switch (option){
            case 0:
                break;
            case 1:
                printf("Ingrese un caracter: ");
                
                gets(input);
                if (strlen(input) > 1){
                    printf("Debe ingresar solamente un (1) caracter.\n");
                    continue;
                }
                elc = input[0];
                
                e = alloc_element();
                if ( e == NULL){
                    printf("\n>> Error en creación de cola, memoria insuficiente.\n");
                    return 1;
                }
                
                init_element(e, elc);
                queue_element (q, e);

                break;
            case 2:
                if ( is_empty (q) ){
                    printf("\n>> La cola está vacía.\n");
                    continue;
                }
            
                e = dequeue_element (q);
                printf("\n>> El caracter eliminado fue: %c\n", e->inner_value);
                free(e);
                break;
            case 3:
                print_queue (q);
                break;
            default:  
                  printf("%d no es una opción válida.\n\n", option);
                  continue;
        }
    } while ( option != 0 );
    
    deep_free(q);
    return 0;
}

Element *alloc_element(){
    return (Element *) malloc ( sizeof(Element)  );
}

Element *init_element(Element *e, ElementType value){
   if (e != NULL){
        memset( e, 0, sizeof(Element) );
        e->inner_value = value;
        return e;
    }
    
    return NULL;
}

Queue *alloc_queue() { 
    return (Queue *) malloc (sizeof(Queue));
}

void init_queue (Queue *q) {
    memset(q, 0, sizeof(Queue));
}

int8_t is_empty(Queue * q){
    return q->length == 0;
}

Element *whois_front(Queue * q){
    return q->front;
}

Element *whois_back(Queue * q){
    return q->back;
}

void queue_element (Queue *q, Element * e){
    if (q->back != NULL){
        q->back->next = e;
    } else {
        q->front = e;
    }

    e->next = e;
    q->back = e;
    q->length ++;
}

Element * dequeue_element (Queue * q){
    Element * last = q->back;
    Element * aux = q->front;
    int32_t i;

    for ( i=0;i<q->length-2;i++ ){
        aux = aux->next; 
    }

    q->back = aux;
    aux->next = NULL;
    q->length --;
    
    return last;
}

void deep_free (Queue * q){
    Element * e;
    while (!is_empty(q)){
        e = dequeue_element (q);
        free(e);
    }
    
    free(q);
}

void print_queue(Queue *q) {
    Element * aux = q->front;
    int32_t i;

    printf("\n================\n");

    if (is_empty(q)){
        printf("Cola vacía.\n");
        return;
    }
            
    printf("Cola completa: ");
    for (i=0;i<q->length;i++){
        if (aux != NULL)
            printf("%c", aux->inner_value);
            
        aux = aux->next;
    }
    
    printf("\n================\n");
}
