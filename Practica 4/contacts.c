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
    Contact * ns = (Contact *) malloc (sizeof(Contact));
    if (ns != NULL){
        memset(ns, 0, sizeof(Contact));
    }
    return ns;
}

DoubleLinkList * alloc_contacts_book (){
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

void insert_contact (ContactBook * list, Contact * new_contact){
    Contact * current = list->cursor;
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

    list->cursor = new_contact;
}

void print_contact_details (Contact * contacty){
    printf("Nombre: %s\n", contacty->name);
    printf("Telefono: %s\n", contacty->phone_number);
    printf("Email: %s\n", contacty->email);
    printf("Edad: %d\n", contacty->age);
}

void print_contact_preview (Contact * c){
    printf("%s <%s>\n", c->name, c->email);
}

void print_contacts_book (ContactBook * book){
    Contact * most_left = book->cursor;
    Contact * printing;

    if (most_left == NULL){
        printf("Libreta de contactos vacía.\n");
    }

    while ( most_left->prev != NULL ){
        most_left = most_left->prev;
    }

    printf("Libreta de contactos: ");

    printing = most_left;
    while( printing != NULL){
        print_contact_preview (printing);
        printing = printing->next;
    }

    printf("\n\n");
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

int main(int argc, char ** argv){
    
    Contact * new_contact;
    ContactBook * contacts_book;

    FILE * stored_contacts;
    char * tmp_number;
    int32_t errnum;

    stored_contacts = fopen("contacts.txt", "r");
    contacts_book = alloc_contacts_book();

    if ( stored_contacts != NULL){

        while ( !(feof(stored_contacts) || ferror(stored_contacts)) ){
            new_contact = alloc_contact ();

            read_string_field( &(new_contact->phone_number), stored_contacts );
            read_string_field( &(new_contact->name), stored_contacts );
            read_string_field( &(new_contact->email), stored_contacts );
            read_string_field( &tmp_number, stored_contacts  );

            if ( tmp_number != NULL ){
                new_contact->age = atoi(tmp_number);
                free(tmp_number);
                tmp_number = NULL;
            }

            printf("========================\n");
            print_contact_details(new_contact);
            insert_contact(contacts_book, new_contact);
        }

        if (!ferror(stored_contacts)){
            print_contacts_book(contacts_book);
            return 0;
        }
    }

    errnum = errno;
    printf("ERROR: %s\n", strerror( errnum ));
    return errnum;
}