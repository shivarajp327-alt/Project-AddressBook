#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
   printf("enter name : ");
   name:
    scanf("%s",addressBook->contacts[addressBook->contactCount].name);
    for(int i=0;addressBook->contacts[addressBook->contactCount].name[i]!=0;i++)
    {
        if(isalnum(addressBook->contacts[addressBook->contactCount].name[i])==0)
        {
            printf("Re-enter the valid name:");
            goto name;
        }  
    }
    printf("enter phone number:");
    phone_number:
    scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
    for(int i=0;addressBook->contacts[addressBook->contactCount].phone[i]!=0;i++)
    {
        if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])==0)
        {
            printf("Re-enter the valid phone number:");
            goto phone_number;
        }
    }
    if(strlen(addressBook->contacts[addressBook->contactCount].phone)!=10 || addressBook->contacts[addressBook->contactCount].phone[0]<'6')
    {
        printf("Re-enter the valid phone number:");
        goto phone_number;
    }
    printf("enter email:");
    email:
    scanf("%s",addressBook->contacts[addressBook->contactCount].email);
    int at_count=0,at_pos;
    for(int i=0;addressBook->contacts[addressBook->contactCount].email[i]!=0;i++)
    {
        if(addressBook->contacts[addressBook->contactCount].email[0]=='@' || addressBook->contacts[addressBook->contactCount].email[i]==' ' || isupper(addressBook->contacts[addressBook->contactCount].email[i])!=0)
        {
            printf("Re-enter the valid email:");
            goto email;
        }
        if(addressBook->contacts[addressBook->contactCount].email[i]=='@')
        {
            at_count++;
            at_pos=i;
        }
    }
    int email_length=strlen(addressBook->contacts[addressBook->contactCount].email);
    if(at_count!=1 || (email_length-4)-at_pos<2)
    {
        printf("Re-enter the valid email:");
        goto email;
    }
    if(strcmp(&addressBook->contacts[addressBook->contactCount].email[email_length-4], ".com")!=0)
    {
        printf("Re-enter the valid email:");
        goto email;
    }
    addressBook->contactCount++;

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
