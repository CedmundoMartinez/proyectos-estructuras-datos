#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

typedef struct _ListType {
    char * name;
    char * phone_number;
    char * email;
    int8_t age;
} ListType;
typedef ListType Contact;

typedef struct _ListNode {
    ListType content;

    struct _ListNode * next;
    struct _ListNode * prev;
} ListNode;

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
    return (Contact *) malloc (sizeof(Contact));
}

ListNode * alloc_list_node (){
    ListNode * ns = (ListNode *) malloc (sizeof(ListNode));
    if (ns != NULL){
        memset(ns, 0, sizeof(ListNode));
    }
    return ns;
}

DoubleLinkList * alloc_double_link_list (){
    DoubleLinkList * ns = (DoubleLinkList *) malloc (sizeof(DoubleLinkList));
    if (ns != NULL){
        memset(ns, 0, sizeof(DoubleLinkList));
    }
    return ns;
}

void init_list_node(ListNode * node, ListType content){
    node->content = content;
}

int8_t is_major_string(char * a, char * b){
    int32_t alen = strlen(a);
    int32_t blen = strlen(b);
    int32_t i, mlen;
    char * major, minor;

    major = alen > blen ? a : b;
    minor = blen > alen ? a : b;
    mlen = alen > blen ? alen : blen;

    for( i = 0; i < mlen; i++ ){
        if (minor[i] > major[i])
            return 1;
    }

    return 0;
}

void insert_contact (ContactBook * list, Contact * new_contact){
    ListNode * current_contact = list->cursor;
    char * current_name, * new_name;

    if ( current_contact != NULL ) {
        current_name = current_contact->name;
        new_name = new_contact->name;

        if ( is_major_string (current_name, new_name) ){
        
        }else{
        
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

void print_contacts_book (ContactBook * book){
}

int8_t read_string_field ( char ** field, FILE * stream ){
    int64_t start_pos = ftell(stream);
    int64_t end_pos, tok_size;
    char c;

    while ( !(feof(stream) || ferror(stream)) ){
        c = fgetc(stream);

        if (c == '\n' || c == ' ' || c == ';' || c == '|'){
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
    contacts_book = alloc_double_link_list();

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

        if (!ferror(stored_contacts))
            return 0;
    }

    errnum = errno;
    printf("ERROR: %s\n", strerror( errnum ));
    return errnum;
}