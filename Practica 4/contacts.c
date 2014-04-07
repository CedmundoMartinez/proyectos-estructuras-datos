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

void print_contact_details (Contact * contacty){
    printf("Nombre: %s\n", contacty->name);
    printf("Telefono: %s\n", contacty->phone_number);
    printf("Email: %s\n", contacty->email);
    printf("Edad: %d\n", contacty->age);
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

            fseek(stream, start_pos, SEEK_CUR);

            if (fgets(*field, tok_size, stream) != *field)
                return 0;

            fseek(stream, end_pos + 1, SEEK_CUR);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char ** argv){
    
    Contact * new_contact;
    FILE * stored_contacts; 
    char * tmp_number;
    int32_t errnum;

    stored_contacts = fopen("contactos.txt", "r");
    
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

            print_contact_details(new_contact);
        }

        if (!ferror(stored_contacts))
            return 0;
    }

    errnum = errno;
    printf("ERROR: %s\n", strerror( errnum ));
    return errnum;
}