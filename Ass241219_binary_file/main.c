/* TO DO:
- 1 file contact include:
+ index base :100 elements save index of contact by name and start byte of contact
+ data base: the rest of file, save dynamic data of contact
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_HEADER 50 
#define FILE_LINK "CONTACT.txt"

typedef struct contact_index {
    char header[MAX_LEN_HEADER];  // username as index, fixed 100 elements
    long int start_byte;          // start byte of contact_data
} c_id;

#define SIZE_INDEX      sizeof(c_id)
#define MAX_NUM_INDEX   100
#define MAX_SIZE_INDEX  (SIZE_INDEX * MAX_NUM_INDEX)

typedef struct contact_data {
    int yob;           // year of birth
    int name_len;
    int telnum_len;
    char* name;        // name
    char* telnum;      // tel number
} c_data;

/******************************************************
 * Prototypes
 *****************************************************/
int init_new_contact_book();
char* get_input_string();
int add_contact();
int search_by_name();
int delete_contact();
int menu();

/******************************************************
 * Code
 *****************************************************/
int main(int argc, char* argv[]) {
    // init
    int ret;

    // start create contact book script
    if(init_new_contact_book())
    { 
        printf("[ERR] can't renew contact book\n");
        return 1;
    } // can't init contact book

    // add inform
    ret = menu();
    while (ret) {
        switch (ret) {
            case 1:
                add_contact();
                break;
            case 2:
                search_by_name();
                break;
            case 3:
                delete_contact();
                break;
            default:
                printf("[Note] Invalid input. Please try again.\n");
                break;
        }
        ret = menu();  // Ask for the next choice
    }

    printf("Program ended.\n");
    return 0;
}


int menu() {
    int order;
    printf("------------------------\n");
    printf("Function:\n1. Add contact\n2. Search by name\n3. Delete contact\n0. End\n");
    scanf("%d", &order);
    if (order < 0 || order > 3) {
        return -1;
    }
    return order;
}

int init_new_contact_book()
{
    char* init_string = NULL;
    FILE* f = NULL;
    f = fopen(FILE_LINK, "wb+"); //w+ mode is create new empty file, if file existed then renew it
    
    // check fail open file
    if(f==NULL)
    {return -1;}

    // create 100 NULL element index
    init_string = (char*)calloc(MAX_SIZE_INDEX , 1);
    fwrite(init_string, MAX_SIZE_INDEX, 1, f);

    // then close file
    fclose(f);
    return 0;
}

char* get_input_string()
{
    int check_input = 1; //1 - start check, 0 end check
    char* full_string = (char*)calloc(1, sizeof(char)); // init a empty string end with \0
    int size_of_full_string = 1;

    scanf("%*c");

    while (check_input)
    {
        int check_char = -1;
        char* temp_string = (char*)calloc( 51, sizeof(char)); // init 50 + 1 for \0
        for(int i = 0; i < 50; i++)
        {
            check_char = getchar();

            if(check_char == -1 || check_char == (int)'\n')
            {break;}

            temp_string[i] = check_char;
        }
        
        if(temp_string[49] == '\0')
        {check_input = 0;} // complete get full string
        
        size_of_full_string += 50;
        full_string = (char*)realloc(full_string, size_of_full_string);
        full_string = strcat(full_string, temp_string);

        free(temp_string);
    }
    
    return full_string;
}

int add_contact() {
    int empty_slot = -1;
    // Allocate memory for the contact
    c_data new_contact;
    c_id new_index;

    FILE* f = fopen(FILE_LINK, "rb+"); // open file and start cursor at position 0

    if (f == NULL) {
        printf("[ERR] Can't open file: %s\n", FILE_LINK);
        return -1;
    }

    // search the empty slot for new contact
    for(int i = 0; i < MAX_NUM_INDEX; i++)
    {
        char temp[1] = {'\0'};
        fseek(f, i*SIZE_INDEX, SEEK_SET); // Move to the beginning
        fread(temp, 1,1,f); // get first byte
        if (temp[0] == '\0')
        {
            empty_slot = i*SIZE_INDEX;
            break; // ok found
        }
    }
    if(empty_slot == -1)
    {
        printf("[WARN] The contact book is full");
        return -1;
    }


    // Input the contact details
    printf("Enter name: ");
    new_contact.name = get_input_string();
    new_contact.name_len = strlen(new_contact.name);

    printf("Enter year of birth: ");
    scanf("%d", &new_contact.yob);

    printf("Enter phone number: ");
    new_contact.telnum = get_input_string();
    new_contact.telnum_len = strlen(new_contact.telnum);

    // Write the contact data
    fseek(f, 0, SEEK_END);  // Move the file pointer to the end
    long int contact_pos = ftell(f);  // Get the current position (start byte of the contact data)

    // Write the contact data into the file
    fwrite(&new_contact.yob, sizeof(new_contact.yob), 1, f);
    fwrite(&new_contact.name_len, sizeof(new_contact.name_len), 1, f);
    fwrite(&new_contact.telnum_len, sizeof(new_contact.telnum_len), 1, f);
    fwrite(new_contact.name, strlen(new_contact.name), 1, f);
    fwrite(new_contact.telnum, strlen(new_contact.telnum), 1, f);

    // Update the header with the new contact index
    memcpy(new_index.header,new_contact.name, MAX_LEN_HEADER);
    
    // note that snprintf add /0 auto matic
    new_index.start_byte = contact_pos;

    // Write the index to the file
    fseek(f, empty_slot, SEEK_SET);  // Move to the empty slot
    fwrite(&new_index, sizeof(c_id), 1, f);

    //end
    fclose(f);

    free(new_contact.name);
    free(new_contact.telnum);

    return 0;
}

int search_by_name() {
    FILE* f = fopen(FILE_LINK, "rb");
    if (f == NULL) {
        printf("[ERR] Can't open file: %s\n", FILE_LINK);
        return -1;
    }

    c_id user_contact;
    char search_name[MAX_LEN_HEADER] = {'\0'};
    int found = 0;  // Flag to indicate if the contact is found

    // Input the name to search
    printf("Enter contact name to search [max 50]: ");
    scanf(" %50[^\n]", search_name);
    fflush(stdin); // clear buffer if input too long

    // Search for the name in the index
    for (int i = 0; i < MAX_NUM_INDEX; i++) {
        fseek(f, i * SIZE_INDEX, SEEK_SET);  // Move to the i-th index
        fread(&user_contact, SIZE_INDEX, 1, f);  // Read the index

        // Compare the search name with the header in the index
        if (strncmp(user_contact.header, search_name, MAX_LEN_HEADER) == 0) {
            c_data contact_info;

            found = 1;  // If a match is found, set the flag

            // Now, move to the start_byte to read the contact's data
            fseek(f, user_contact.start_byte, SEEK_SET);
            fread(&contact_info.yob, sizeof(contact_info.yob), 1, f);  // Read contact data
            fread(&contact_info.name_len, sizeof(contact_info.name_len), 1, f);
            fread(&contact_info.telnum_len, sizeof(contact_info.telnum_len), 1, f);
            contact_info.name = (char*) calloc (contact_info.name_len+1,sizeof(char));
            contact_info.telnum = (char*) calloc (contact_info.telnum_len+1,sizeof(char));
            fread(contact_info.name, contact_info.name_len, 1, f);
            fread(contact_info.telnum, contact_info.telnum_len, 1, f);

            // Print the contact details
            printf("Found contact:\n");
            printf("Name: %s\n", contact_info.name);
            printf("Year of Birth: %d\n", contact_info.yob);
            printf("Phone Number: %s\n", contact_info.telnum);

            //free
            free(contact_info.name);
            free(contact_info.telnum);

            break;  // Exit the loop once the contact is found
        }
    }

    if (!found) {
        printf("[INFO] Contact with name '%s' not found.\n", search_name);
    }

    fclose(f);
    return 0;
}

int delete_contact()
{
    printf(":) Oh it's too hard for me\n");
}