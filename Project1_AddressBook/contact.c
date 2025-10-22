#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"

int c, arr_count[100];

void listContacts(AddressBook *addressBook) 
{

    printf("============================================================================================\n");
    printf("%-10s %-20s %-20s %-30s\n","Sl.no","Name","Ph.no","Mail ID");
    printf("============================================================================================\n");
    for( int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-10d %-20s %-20s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    
    }
    printf("============================================================================================\n\n");
    
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}


void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


int Number_validate(char* Phone_num, AddressBook* addressBook)
{
    int c = 0;
    for( int i = 0; i < strlen(Phone_num); i++)
    {
        if( isdigit(Phone_num[i]) )
            c++;
    }


    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(!strcmp(Phone_num,addressBook->contacts[i].phone))
        {
            printf("Error, Invalid number (already present)!\n");
            return 1;      
        }  
    }

    if(strlen(Phone_num) != 10 || c != strlen(Phone_num))
    {
        printf("Error, Invalid number length not 10!/ non digit chars present\n");
        return 1;
    }
    else
        return 0;        
}

int Email_validate(char* Email_id, AddressBook* addressBook)
{
    for( int i = 0; i < addressBook->contactCount; i++)
    {
        if( !strcmp(Email_id,addressBook->contacts[i].email) )
        {
            printf("Error! Already exist\n");
            return 1;       
        }  
    }

    
    for( int i = 0; i < strlen(Email_id); i++)
    {
        if( isupper(Email_id[i]) )
        {
            printf("Error! Upper case char present\n");
            return 1;      
        } 
    }

    char* mailptr = strstr(Email_id,".com");
    char* mailchar = strchr(Email_id,'@');

    if( strchr(Email_id,' ') || (strchr(Email_id,'@') != strrchr(Email_id,'@')) || strchr(Email_id,'@') == NULL)
    {
        printf("Error, Invalid mail id has space/multiple @ present!/@ not all present\n");
        return 1;
    }
    else if(!(isalnum(*(mailchar + 1)) && isalnum(*(mailchar - 1))))
    {
        printf("Error! no alnum char after/before @\n");
        return 1;
    }
    else if(!(strstr(Email_id,".com") && strlen(mailptr) == 4) || *(mailptr-1) == '.')
    {
        printf("Error, Invalid mail id .com not found at end or at all!/ multiple '.' with com\n");
        return 1;
    }
    else
        return 0;

}

void createContact(AddressBook *addressBook)
{
    char Phone_num[20];
    char Email_id[50];
    printf("Enter name: ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);

    do
    {
        printf("Enter phone number: ");
        scanf(" %[^\n]",Phone_num); 
              
    }while(Number_validate(Phone_num,addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].phone,Phone_num);
    
    do
    {
        printf("Enter Email Id: ");
        scanf(" %[^\n]",Email_id);
    }while(Email_validate(Email_id,addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].email,Email_id);

    printf("\nContact created successfully\n");

    addressBook->contactCount++;    
}


    void Search_name(char* search, AddressBook* addressBook)
    {
        c = 0;
        int flag = 0;
        for(int i=0; i < addressBook->contactCount; i++)
        {
            if(!strcmp(search,addressBook->contacts[i].name))
            {
                if(flag == 0)
                {
                    printf("--------------------------------------------------------------------------------------------\n");
                    printf("%-10s %-20s %-20s %-30s\n","Sl.no","Name","Ph.no","Mail ID");
                    printf("--------------------------------------------------------------------------------------------\n");
                }
                arr_count[c++] = i;
                printf("%-10d %-20s %-20s %-30s\n",c,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag = 1;
            }

        }
        if(flag > 0)
                printf("--------------------------------------------------------------------------------------------\n");

        if(!flag)
        {
            printf("\nContact not found!\n\n");
        }

    }


    void Search_phone(char* search, AddressBook* addressBook)
    {
        c = 0;
        int flag = 0;
        for(int i=0; i < addressBook->contactCount; i++)
        {
            if(!strcmp(search,addressBook->contacts[i].phone))
            {
                if(flag == 0)
                {
                    printf("--------------------------------------------------------------------------------------------\n");
                    printf("%-10s %-20s %-20s %-30s\n","Sl.no","Name","Ph.no","Mail ID");
                    printf("--------------------------------------------------------------------------------------------\n");
                }
                arr_count[c++] = i;
                printf("%-10d %-20s %-20s %-30s\n",c,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag = 1;
            }    
        }
        if(flag > 0)
                printf("--------------------------------------------------------------------------------------------\n");
        if(!flag)
        {
            printf("\nContact not found!\n\n");
        }
    }

    void Search_mail(char* search, AddressBook* addressBook)
    {
        c = 0;
        int flag = 0;
        for(int i=0; i < addressBook->contactCount; i++)
        {
            if(!strcmp(search,addressBook->contacts[i].email))
            {
                if(flag == 0)
                {
                    printf("--------------------------------------------------------------------------------------------\n");
                    printf("%-10s %-20s %-20s %-30s\n","Sl.no","Name","Ph.no","Mail ID");
                    printf("--------------------------------------------------------------------------------------------\n");
                }
                arr_count[c++] = i;
                printf("%-10d %-20s %-20s %-30s\n",c,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);    
                flag = 1;
            }
        }
        if(flag > 0)
                printf("--------------------------------------------------------------------------------------------\n");
        if(!flag)
        {
            printf("\nContact not found!\n\n");

        }
    }


void searchContact(AddressBook *addressBook) 
{
    int choice;
    char search[50];
    label :
    printf("===========================\n");
    printf("       Search Menu\n");
    printf("===========================\n");
    printf("Select criteria for searching\n1. Search by name\n2. Search by phone number\n3. Search by Email ID\n4. Exit\n");
    printf("===========================\n");
    printf("Enter choice: ");
    choice = 0;
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
        case 1: 
                printf("Enter name: ");
                scanf(" %[^\n]",search);
                Search_name(search,addressBook);
            break;
        case 2: 
                printf("Enter Phone num: ");
                scanf(" %[^\n]",search);
                Search_phone(search,addressBook);
            break;
        case 3: 
                printf("Enter Email Id: ");
                scanf(" %[^\n]",search);
                Search_mail(search,addressBook);
            break;
        case 4:
                printf("Exiting...\n");
                return;
            break;    
        default: printf("Enter valid choice\n");                 
    }
    goto label;
}


void edit_fun(AddressBook* addressBook, int i)
{
    int var;
    char phone_new[20];
    char mail_new[50];
    label :
    printf("==========================\n");
    printf("      Edit menu\n");
    printf("==========================\n");
    printf("Enter parameter for editing:\n1. Edit name\n2. Edit phone number\n3. Edit Email ID\n4. Exit\n");
    printf("==========================\n");
    printf("Enter choice: ");
    scanf("%d",&var);
    getchar();

        if(var == 1)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]",addressBook->contacts[arr_count[i]].name);
            goto label;
        }
        else if(var == 2)  
        {
            do
            {
                printf("Enter new phone number: ");
                scanf(" %[^\n]",phone_new);
            } while(Number_validate(phone_new,addressBook));
            strcpy(addressBook->contacts[arr_count[i]].phone,phone_new);
            goto label;
        }   
        else if(var == 3)
        {
           do
            {
                printf("Enter new mail id: ");
                scanf(" %[^\n]",mail_new);
            }while (Email_validate(mail_new,addressBook));
            strcpy(addressBook->contacts[arr_count[i]].email,mail_new);
            goto label; 
        }
        else if(var == 4)
        {
            printf("Exiting edit menu...\n");
            editContact(addressBook);
        }
        else
        {
            printf("Enter valid choice: \n");
            goto label;  
        }

}        
void editContact(AddressBook *addressBook)
{
	int choice, num;
    char search[50];
    printf("==========================\n");
    printf("      Search menu\n");
    printf("==========================\n");
    label: printf("Select criteria for searching\n1. Search by name\n2. Search by phone number\n3. Search by Email ID\n4. Exit\n");
    printf("==========================\n");
    printf("Enter choice: ");
    choice = 0;
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
        case 1: 
            printf("Enter name: ");
            scanf(" %[^\n]",search);
            Search_name(search,addressBook);
        break;    

        case 2: 
            printf("Enter phone num: ");
            scanf(" %[^\n]",search);
            Search_phone(search,addressBook);
        break;

        case 3: 
            printf("Enter mail id: ");
            scanf(" %[^\n]",search);
            Search_mail(search,addressBook);
        break;

        case 4: printf("Exiting...\n");
                return;
        break;    

        default: printf("Enter valid choice\n");
            goto label;                
    }

    if(c>1)
    {
        printf("Enter serial number: ");
        scanf("%d",&num);
        for(int i = 0; i < c; i++)
        {
            if(num == i + 1)
            {
                edit_fun(addressBook,i);
            }
        }
                
    }
    else if(c == 1)
    {
        edit_fun(addressBook,0);
    }
        else if(c == 0)
    {
        editContact(addressBook);
    }
    else
    {
        printf("Enter valid entry: ");
        editContact(addressBook);
    }
    
}

void Delete(AddressBook* addressBook, int index)
{
    char ch;
    label: printf("Do you want to delete (Y/N): ");
    scanf(" %c",&ch);
    if(ch == 'Y')
    {
        {
            for(int i = arr_count[index]; i < addressBook->contactCount; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }
            addressBook->contactCount--;
        }
        printf("Contact deleted!\n");
        deleteContact(addressBook);
    }
    else if(ch == 'N')
    {
        deleteContact(addressBook);
    }
    else
    {
        printf("Invalid choice! Enter correctly\n");
        goto label;
    }
}


void deleteContact(AddressBook *addressBook)
{

    int choice, num;
    char search[50];
    printf("==========================\n");
    printf("       Delete menu\n");
    printf("==========================\n");
    label: printf("Select criteria for searching\n1. Search by name\n2. Search by phone number\n3. Search by Email ID\n4. Exit\n");
    printf("==========================\n");
    printf("Enter choice: ");
    choice = 0;
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
        case 1: 
            printf("Enter name: ");
            scanf(" %[^\n]",search);
            Search_name(search,addressBook);
        break;    

        case 2: 
            printf("Enter phone num: ");
            scanf(" %[^\n]",search);
            Search_phone(search,addressBook);
        break;

        case 3: 
            printf("Enter mail id: ");
            scanf(" %[^\n]",search);
            Search_mail(search,addressBook);
        break;

        case 4: printf("Exiting...\n");   
                return;
        break;    

        default: printf("Enter valid choice\n");
            goto label;                
    }
    if(c>1)
    {
        printf("Enter serial number: ");
        scanf("%d",&num);
        for(int i = 0; i < c; i++)
        {
            if(num == i + 1)
            {
                Delete(addressBook,i);
            }
        }
                
    }
    else if(c == 1)
    {
        Delete(addressBook,0);
    }
    else if(c == 0)
    {
        deleteContact(addressBook);
    }
    else
    {
        printf("Enter valid entry: ");
        editContact(addressBook);
    }

}
