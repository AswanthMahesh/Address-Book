#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE* fptr = fopen("contacts.csv","w");
    fprintf(fptr,"%d\n",addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{

    FILE* fptr = fopen("contacts.csv","r");
    if(fptr == NULL)
    {
        printf("File does not exist\n");
        return;
    }
    else
    {
        char str[10];
        fscanf(fptr,"%s\n",str);
        int c = atoi(str);
        addressBook->contactCount = c;
        for(int i = 0; i < c; i++)
        {
            fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    fclose(fptr);
}
