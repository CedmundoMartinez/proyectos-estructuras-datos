#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

typedef struct _ListNode {
    char * name;
    char * phone_number;
    char * email;
    int8_t age;

    struct _ListNode * next;
    struct _ListNode * prev;
} ListNode;
typedef ListNode Contact;

typedef struct _DoubleLinkList {
    ListNode * cursor;
} DoubleLinkList;
typedef DoubleLinkList ContactBook;

char * alloc_string (size_t size){
    char * ns = (char *) malloc (size * sizeof(char));
    if (ns != NULL){
        memset(ns, 0, size);
    }
    return ns;
}

Contact * alloc_contact (){
    ListNode * ns = (ListNode *) malloc (sizeof(ListNode));
    if (ns != NULL){
        memset(ns, 0, sizeof(ListNode));
    }
    return ns;
}

ContactBook * alloc_contacts_book (){
    DoubleLinkList * ns = (DoubleLinkList *) malloc (sizeof(DoubleLinkList));
    if (ns != NULL){
        memset(ns, 0, sizeof(DoubleLinkList));
    }
    return ns;
}

int8_t is_major_string(char * a, char * b){
    char * str_major, * str_minor;
    int32_t i;

    if ( strlen(a) > strlen(b) ){
        str_major = a;
        str_minor = b;
    }else{
        str_major = b;
        str_minor = a;
    }

    for( i = 0; i < strlen(str_minor); i++ ){
        if (str_minor[i] > str_major[i])
            return 1;
    }

    return 0;
}

void insert_contact (ContactBook * book, Contact * new_contact){
    Contact * current = book->cursor;
    
    if (current != NULL){
        char * cur_name = new_contact->name;
        char * new_name = current->name;
        Contact * before_insert = NULL;

        if ( is_major_string(new_name, cur_name) ){
            Contact * next = current->next;

            while ( current->next != NULL && is_major_string(new_name, current->name) ) {
                current = current->next;
            }

            before_insert = next;
            current->next = new_contact;
            new_contact->prev = current;
            new_contact->next = before_insert;

            if (next != NULL){
                next->prev = new_contact;
            }
        } else {
            Contact * prev = current->prev;

            while ( current->prev != NULL && !is_major_string(new_name, current->name) ) {
                current = current->prev;
            }

            before_insert = prev;
            current->prev = new_contact;
            new_contact->next = current;
            new_contact->prev = before_insert;

            if (prev != NULL){
                prev->next = new_contact;
            }

        }
    }

    book->cursor = new_contact;
}

Contact * search_contact_by_name (ContactBook * book, char * name){
    Contact * current = book->cursor;
    
    if (current != NULL){

        if ( strcmp(current->name, name) == 0 ) {
            return current;
        }else if ( is_major_string(current->name, name) ){
            Contact * next = current->next;

            while ( current->next != NULL) {
                if ( strcmp(current->name, name) == 0 )
                    return current;

                current = current->next;
            }

        } else {
            Contact * prev = current->prev;

            while ( current->prev != NULL) {
                if ( strcmp(current->name, name) == 0 )
                    return current;

                current = current->prev;
            }

        }
    }

    return NULL;
}

void delete_contact (ContactBook * book, Contact * contact){
    contact->next->prev = contact->prev;
    contact->prev->next = contact->next;

    free(contact);
}

int32_t get_contact_index(Contact * contact){
    Contact * first_contact = contact;
    Contact * counting;

    if (first_contact == NULL){
        return -1;
    }

    while ( first_contact->prev != NULL ){
        first_contact = first_contact->prev;
    }

    int32_t index = 0;

    counting = first_contact;
    for (index = 0; counting != NULL; index += 1 || (counting = counting->next) ){
        if (counting == contact){
            return index;
        }
    }

    return -1;
}

void print_contact_details (Contact * contacty){
    printf("Nombre: %s\n", contacty->name);
    printf("Telefono: %s\n", contacty->phone_number);
    printf("Email: %s\n", contacty->email);
    printf("Edad: %d\n", contacty->age);
}

void print_contact_file (FILE *file, Contact * c){
    fprintf(file, "%s %s %s %d\n", c->phone_number, c->name, c->email, c->age);
}

void print_contact_preview (int32_t idx, Contact * c){
    printf("%d:\t%s <%s>\n", idx, c->name, c->email);
}

void print_contacts_book (ContactBook * book){
    Contact * first_contact = book->cursor;
    Contact * printing;

    if (first_contact == NULL){
        printf("Libreta de contactos vacía.\n");
    }

    while ( first_contact->prev != NULL ){
        first_contact = first_contact->prev;
    }

    printf("Libreta de contactos: \n");
    int32_t index = 0;

    printing = first_contact;
    while( printing != NULL){
        print_contact_preview (index++, printing);
        printing = printing->next;
    }

    printf("\n");
}

int8_t read_string_field ( char ** field, FILE * stream ){
    int64_t start_pos = ftell(stream);
    int64_t end_pos, tok_size;
    char c;

    while ( !(feof(stream) || ferror(stream)) ){
        c = fgetc(stream);

        if (c == '\n' || c == ' ' || c == '\t'){
            end_pos = ftell(stream);
            tok_size = end_pos - start_pos;

            *field = alloc_string( tok_size + 1 );
            if ( *field == NULL )
                return 2;

            fseek(stream, start_pos, SEEK_SET);

            if (fgets(*field, tok_size, stream) != *field)
                return 0;

            fseek(stream, end_pos, SEEK_SET);
            return 1;
        }
    }
    return 0;
}

int8_t read_contacts(ContactBook * book, FILE * stored_contacts){
    Contact * new_contact;
    char * tmp_number;

    while ( !(feof(stored_contacts) || ferror(stored_contacts)) ){
        new_contact = alloc_contact ();

        if ( new_contact != NULL ){
            read_string_field( &(new_contact->phone_number), stored_contacts );
            read_string_field( &(new_contact->name), stored_contacts );
            read_string_field( &(new_contact->email), stored_contacts );
            read_string_field( &tmp_number, stored_contacts  );

            if ( tmp_number != NULL ){
                new_contact->age = atoi(tmp_number);
                free(tmp_number);
                tmp_number = NULL;
            }

            insert_contact(book, new_contact);
        }
    }

    if (ferror(stored_contacts))
        return 0;

    return 1;
}

int8_t save_contacts(ContactBook * book, FILE * contacts_store){
    Contact * first_contact = book->cursor;
    Contact * printing;

    if (first_contact == NULL){
        return 0;
    }

    while ( first_contact->prev != NULL ){
        first_contact = first_contact->prev;
    }

    printing = first_contact;
    while( printing != NULL){
        print_contact_file(contacts_store, printing);
        printing = printing->next;
    }
}

void perform_operation (int32_t operation, ContactBook * contacts_book) {
    // Menues y demás...
}

int main(int argc, char ** argv){
    
    ContactBook * contacts_book;
    FILE * stored_contacts;

    int32_t errnum, option;
    int8_t success_op;

    stored_contacts = fopen("contacts.txt", "r");
    contacts_book = alloc_contacts_book();

    success_op = read_contacts(contacts_book, stored_contacts);
    fclose(stored_contacts);

    if ( stored_contacts != NULL){
        if (success_op){
            print_contacts_book(contacts_book);

            do{
                printf( "=== Menú principal === \n"
                        "0. Salir sin guardar.\n"
                        "1. Guardar y salir.\n"
                        "2. Guardar.\n"
                        "3. Imprimir libreta de contactos.\n"
                        "4. Buscar un contacto.\n"
                        "5. Ver detalles de un contacto.\n"
                        "6. Actualizar un contacto.\n"
                        "7. Agregar un contacto.\n"
                        "8. Eliminar un contacto.\n" );
                printf("Ingrese una opción para continuar: ");
                scanf("%d", &option);
                
                perform_operation(option, contacts_book);
            } while(option >= 2);

            if ( option == 1) {
                stored_contacts = fopen("contacts.txt", "w");
                save_contacts(contacts_book, stored_contacts);
                fclose(stored_contacts);
            }

            return 0;
        }
    }

    errnum = errno;
    printf("ERROR: %s\n", strerror( errnum ));
    return errnum;
}