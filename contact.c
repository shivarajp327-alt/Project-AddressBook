#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"

void display(AddressBook *addressBook)
{
           printf("\nSl.no|\tName\t\t\tPhone Number\tEmail ID\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("  %d  |\t%s\t\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
       
}
void sortby_name(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        display(addressBook);
}
void sortby_phone(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        display(addressBook);
}
void sortby_email(AddressBook *addressBook)
{
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
         display(addressBook);
}
void listContacts(AddressBook *addressBook) 
{
   // loadContactsFromFile(addressBook); // Load contacts from file before listing
    // Sort contacts based on the chosen criteria
    int choice;
    printf("Choose sorting criteria:\n");
    do
    {
        printf("1.Sort by name\n");
        printf("2.Sort by phone number\n");
        printf("3.Sort by email\n");
        printf("4.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                sortby_name(addressBook);
                break;
            case 2:
                sortby_phone(addressBook);
                break;
            case 3:
                sortby_email(addressBook);
                break;
            case 4:
                return;
                break;
            default:
                printf("Invalid choice,Please try again\n");
        }
        /* code */
    } while (choice>0 && choice<5);
    return;
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
   loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int name_validation(char *name,AddressBook *addressBook,int index)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(i!=index && strcasecmp(addressBook->contacts[i].name,name)==0)
        {
            printf("\nName already exists,Please re-enter:\n");
            return 0; // Name already exists
        }
    }
    for(int i=0;name[i]!=0;i++)
    {
        if(isalnum(name[i])==0 && name[i]!=' ')
        {
            printf("\nRe-enter the valid name:\n");
            return 0; // Invalid character in name
        }
    }
    return 1; // Name is unique
}
int phone_validation(char *phone,AddressBook *addressBook,int index)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(i!=index && strcasecmp(addressBook->contacts[i].phone,phone)==0)
        {
            printf("\nPhone number already exists,Please re-enter:\n");
            return 0; // Phone number already exists
        }
    }
    for(int i=0;phone[i]!=0;i++)
    {
        if(isdigit(phone[i])==0)
        {
            printf("\nRe-enter the valid phone number:\n");
            return 0; // Invalid character in phone number
        }
    }
    if(strlen(phone)!=10 || phone[0]<'6')
    {
        printf("\nRe-enter the valid phone number:\n");
        return 0; // Invalid phone number length or starting digit
    }
    return 1; // Phone number is unique and valid
}
int email_validation(char *email,AddressBook *addressBook,int index)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(i!=index && strcasecmp(addressBook->contacts[i].email,email)==0)
        {
            printf("\nEmail already exists,Please re-enter:\n");
            return 0; // Email already exists
        }
    }
    int at_count=0,at_pos;
    for(int i=0;email[i]!=0;i++)
    {
        if(email[0]=='@' || email[i]==' ' || isupper(email[i])!=0)
        {
            printf("\nRe-enter the valid email:\n");
            return 0; // Invalid character in email
        }
        if(email[i]=='@')
        {
            at_count++;
            at_pos=i;
        }
    }
    int email_length=strlen(email);
    if(at_count!=1 || (email_length-4)-at_pos<2)
    {
        printf("\nRe-enter the valid email:\n");
        return 0; // Invalid email format
    }
    if(strcmp(&email[email_length-4], ".com")!=0)
    {
        printf("\nRe-enter the valid email:\n");
        return 0; // Invalid email domain
    }
    return 1; // Email is unique and valid
}


void createContact(AddressBook *addressBook)
{
    //loadContactsFromFile(addressBook); // Load contacts from file before creating a new contact
   printf("enter name : ");
   do
   {
    scanf("%s",addressBook->contacts[addressBook->contactCount].name);
   } while (!name_validation(addressBook->contacts[addressBook->contactCount].name, addressBook, addressBook->contactCount));

    printf("enter phone number:");
    do
    {
        scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
    } while (!phone_validation(addressBook->contacts[addressBook->contactCount].phone, addressBook, addressBook->contactCount));

    printf("enter email:");

    do
    {
        scanf("%s",addressBook->contacts[addressBook->contactCount].email);
    } while (!email_validation(addressBook->contacts[addressBook->contactCount].email, addressBook, addressBook->contactCount));
    addressBook->contactCount++;
    printf("Contact created successfully.\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    printf("1. Search by name\n");
    printf("2. Search by phone number\n");  
    printf("3. Search by email\n");
    printf("4. Exit\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    char search[50];
    printf("Enter the search term:");
    scanf("%s", search);
    switch(choice)
    {
        case 1:
        printf("Sl.no\tName\tPhone Number\tEmail\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name,search)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    break;
                }
            }
            break;
        case 2:
        printf("Sl.no\tName\tPhone Number\tEmail\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].phone,search)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    break;
                }
            }
            break;
        case 3:
        printf("Sl.no\tName\tPhone Number\tEmail\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].email,search)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    break;
                }
            }
            break;
        case 4:
            printf("Exiting search...\n");
            break;
        default:
            printf("Invalid choice,Please try again\n");

    }

}
void read_index(int *index,AddressBook *addressBook)
{
    while(1)
    {
       // printf("Enter the index of the contact:\n");
        scanf("%d",index);
        if(*index>0 && *index<=addressBook->contactCount)
        {
            break;
        }
        else
        {
            printf("Invalid index,Please re-enter:\n");
        }
    }
}
void search_display_name(AddressBook *addressBook,char *name)
{
    printf("Sl.no\tName\tPhone Number\tEmail\n");
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcasestr(addressBook->contacts[i].name,name)!=0)
        {
            found=1;
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(found==0)
    {
        printf("Contact not found\n");
    }
    {
        printf("Contact not found\n");
    }
}
void search_display_phone(AddressBook *addressBook,char *phone)
{
    printf("Sl.no\tName\tPhone Number\tEmail\n");
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcasestr(addressBook->contacts[i].phone,phone)!=0)
        {
            found=1;
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(found==0)
    {
        printf("Contact not found\n");
    }
}
void search_display_email(AddressBook *addressBook,char *email)
{
    printf("Sl.no\tName\tPhone Number\tEmail\n");
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcasestr(addressBook->contacts[i].email,email)!=0)
        {
            found=1;
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(found==0)
    {
        printf("Contact not found\n");
    }
}

void edit_choice(int index,AddressBook *addressBook)
{
    int choice;
    do
    {
        printf("\n Choose method to editing contact:\n");
        printf("1. Edit by name\n");
        printf("2. Edit by phone number\n");
        printf("3. Edit by email\n");
        printf("4. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter new name:\n");
                do
                {
                    scanf("%s",addressBook->contacts[index-1].name);
                } while (!name_validation(addressBook->contacts[index-1].name, addressBook, index-1));
                break;
            case 2:
                printf("Enter new phone number:\n");
                do
                {
                    scanf("%s",addressBook->contacts[index-1].phone);
                } while (!phone_validation(addressBook->contacts[index-1].phone, addressBook, index-1));
                break;
            case 3:
                printf("Enter new email:\n");
                do
                {
                    scanf("%s",addressBook->contacts[index-1].email);
                } while (!email_validation(addressBook->contacts[index-1].email, addressBook, index-1));
                break;
            case 4:
                printf("Exiting edit...\n");
                return;
            default:
                printf("Invalid choice,Please try again\n");
        }

    }
    while(choice>0 || choice>=3);
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice,index;
    char edit[50];
    do
    {
        printf("\n Choose method to searching contact:\n");
        printf("1. Edit by name\n");
        printf("2. Edit by phone number\n");
        printf("3. Edit by email\n");
        printf("4. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d",&choice);
        printf("Enter the search term:\n");
        scanf("%s", edit);
        switch(choice)
        {
            case 1:
                search_display_name(addressBook,edit);
                printf("Enter the index of the contact to edit:\n");
                read_index(&index,addressBook);
                edit_choice(index,addressBook);
                break;
            case 2:
                search_display_phone(addressBook,edit);
                printf("Enter the index of the contact to edit:\n");
                read_index(&index,addressBook);
                edit_choice(index,addressBook);
                break;
            case 3:
                search_display_email(addressBook,edit);
                printf("Enter the index of the contact to edit:\n");
                read_index(&index,addressBook);
                edit_choice(index,addressBook);                break;
            case 4:
                printf("Exiting search...\n");
                return;
            default:
                printf("Invalid choice,Please try again\n");
        }

    }
    while(choice>0 || choice>=3);
}
void deleteContactByIndex(AddressBook *addressBook, int index)
 {
    if (index < 0 || index >= addressBook->contactCount)
     {
        printf("Invalid index. Cannot delete contact.\n");
        return;
    }

    // Shift contacts to remove the contact at the specified index
    for (int i = index; i < addressBook->contactCount - 1; i++)
     {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully.\n");
}


void deleteContact(AddressBook *addressBook)
{
   // loadContactsFromFile(addressBook); // Load contacts from file before deleting a contact
	/* Define the logic for deletecontact */
    int choice,index;
    char search[50];
    do
    {
        /* code */
        printf("\n Choose method to delete contact:\n");
        printf("1. Delete by name\n");
        printf("2. Delete by phone number\n");
        printf("3. Delete by email\n");
        printf("4. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d",&choice);
        printf("Enter the delete term:\n");
        scanf("%s", search);
        switch(choice)
        {
            case 1:
                search_display_name(addressBook,search);
                printf("Enter the index of the contact to delete:\n");
                read_index(&index,addressBook);
                deleteContactByIndex(addressBook,index-1);
                break;
            case 2:
                search_display_phone(addressBook,search);
                printf("Enter the index of the contact to delete:\n");
                read_index(&index,addressBook);
                deleteContactByIndex(addressBook,index-1);
                break;
            case 3:
                search_display_email(addressBook,search);
                printf("Enter the index of the contact to delete:\n");
                read_index(&index,addressBook);
                deleteContactByIndex(addressBook,index-1);
                break;
            case 4:
                printf("Exiting delete...\n");
                return;
            default:
                printf("Invalid choice,Please try again\n");
        }
        
    } while (choice>0 && choice<5);
}
