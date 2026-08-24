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
                for(int i=0;i<addressBook->contactCount-1;i++)
                {
                    for(int j=i+1;j<addressBook->contactCount-1;j++)
                    {
                        if(strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name)>0)
                        {
                            Contact temp=addressBook->contacts[i];
                            addressBook->contacts[i]=addressBook->contacts[j];
                            addressBook->contacts[j]=temp;
                        }
                    }
                }
                printf("Sl.no\tName\tPhone Number\tEmail\n");
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
                break;
            case 2:
                for(int i=0;i<addressBook->contactCount-1;i++)
                {
                    for(int j=i+1;j<addressBook->contactCount-1;j++)
                    {
                        if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)>0)
                        {
                            Contact temp=addressBook->contacts[i];
                            addressBook->contacts[i]=addressBook->contacts[j];
                            addressBook->contacts[j]=temp;
                        }
                    }
                }
                printf("Sl.no\tName\tPhone Number\tEmail\n");
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
                break;
            case 3:
                for(int i=0;i<addressBook->contactCount-1;i++)
                {
                    for(int j=i+1;j<addressBook->contactCount-1;j++)
                    {
                        if(strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email)>0)
                        {
                            Contact temp=addressBook->contacts[i];
                            addressBook->contacts[i]=addressBook->contacts[j];
                            addressBook->contacts[j]=temp;
                        }
                    }
                }
                printf("Sl.no\tName\tPhone Number\tEmail\n");
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
                break;
            case 4:
                return;
                break;
            default:
                printf("Invalid choice,Please try again\n");
        }
        /* code */
    } while (choice>0 && choice<4);
    return;
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
    int choice;
    printf("1. Search by name\n");
    printf("2. Search by phone number\n");  
    printf("3. Search by email\n");
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
                if(strstr(addressBook->contacts[i].name,search)!=0)
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
                if(strstr(addressBook->contacts[i].phone,search)!=0)
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
                if(strstr(addressBook->contacts[i].email,search)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    break;
                }
            }
            break;
        default:
            printf("Invalid choice,Please try again\n");

    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice,index;
    char edit[50];
    printf("\nchoose the method to edit:\n");
    printf("1. Edit by name\n");
    printf("2. Edit by phone number\n");    
    printf("3. Edit by email\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    printf("Enter what you want to edit:");
    scanf("%s",edit);
    switch(choice)
    {
        case 1:
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].name,edit)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            printf("Enter the index of the contact to edit:");
            index_a:
            scanf("%d",&index);
            if(index<1 || index>addressBook->contactCount)
            {
                printf("Invalid index,Please re-enter:");
                goto index_a;
            }
           else
           {
                printf("Enter new name:");
                name:
                scanf("%s",addressBook->contacts[index-1].name);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(i!=index-1 && strcmp(addressBook->contacts[i].name,addressBook->contacts[index-1].name)==0)
                    {
                        printf("Name already exists,Please re-enter:");
                        goto name;
                    }
                }
                for(int i=0;i<addressBook->contacts[index-1].name[i]!=0;i++)
                {
                    if(isalnum(addressBook->contacts[index-1].name[i])==0)
                    {
                        printf("Re-enter the valid name:");
                        goto name;
                    }  
                }
           }
            break;
        case 2:
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].phone,edit)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            printf("Enter the index of the contact to edit:");
            index_b:
            scanf("%d",&index);
            if(index<1 || index>addressBook->contactCount)
            {
                printf("Invalid index,Please re-enter:");
                goto index_b;
            }
            else
            {
                printf("Enter new phone number:");
                phone_number:
                scanf("%s",addressBook->contacts[index-1].phone);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(i!=index-1 && strcmp(addressBook->contacts[i].phone,addressBook->contacts[index-1].phone)==0)
                    {
                        printf("Phone number already exists,Please re-enter:");
                        goto phone_number;
                    }
                }
                for(int i=0;i<addressBook->contacts[index-1].phone[i]!=0;i++)
                {
                    if(isdigit(addressBook->contacts[index-1].phone[i])==0)
                    {
                        printf("Re-enter the valid phone number:");
                        goto phone_number;
                    }
                }
                if(strlen(addressBook->contacts[index-1].phone)!=10 || addressBook->contacts[index-1].phone[0]<'6')
                {
                    printf("Re-enter the valid phone number:");
                    goto phone_number;
                }
            }
            break;
        case 3:
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].email,edit)!=0)
                {
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            printf("Enter the index of the contact to edit:");
            index_c:
            scanf("%d",&index);
            if(index<1 || index>addressBook->contactCount)
            {
                printf("Invalid index,Please re-enter:");
                goto index_c;
            }
            else
            {
                printf("Enter new email:");
                email:
                scanf("%s",addressBook->contacts[index-1].email);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(i!=index-1 && strcmp(addressBook->contacts[i].email,addressBook->contacts[index-1].email)==0)
                    {
                        printf("Email already exists,Please re-enter:");
                        goto email;
                    }
                }
                int at_count=0,at_pos;
                for(int i=0;i<addressBook->contacts[index-1].email[i]!=0;i++)
                {
                    if(addressBook->contacts[index-1].email[0]=='@' || addressBook->contacts[index-1].email[i]==' ' || isupper(addressBook->contacts[index-1].email[i])!=0)
                    {
                        printf("Re-enter the valid email:");
                        goto email;
                    }
                    if(addressBook->contacts[index-1].email[i]=='@')
                    {
                        at_count++;
                        at_pos=i;
                    }
                }
                int email_length=strlen(addressBook->contacts[index-1].email);
                if(at_count!=1 || (email_length-4)-at_pos<2)
                {
                    printf("Re-enter the valid email:");
                    goto email;
                }
                if(strcmp(&addressBook->contacts[index-1].email[email_length-4], ".com")!=0)
                {
                    printf("Re-enter the valid email:");
                    goto email;
                }
            }
            break;
            default:
                printf("Invalid choice,Please try again\n");
    }    
printf("Contact edited successfully.\n");
}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice,index;
        printf("1. Delete by name\n");
        printf("2. Delete by phone number\n");  
        printf("3. Delete by email\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                char name[50];
                printf("Enter the name to delete:");
                scanf("%s", name);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strstr(addressBook->contacts[i].name,name)!=0)
                    {
                        printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
                printf("Enter the index of the contact to delete:");
                index_a:
                scanf("%d",&index);
                if(index<1 || index>addressBook->contactCount)
                {
                    printf("Invalid index,Please re-enter:");
                    goto index_a;
                }
                else
                {
                    for(int j=index-1;j<addressBook->contactCount-1;j++)
                    {
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully.\n");
                }
                break;
            case 2:
                char phone[20];
                printf("Enter the phone number to delete:");
                scanf("%s", phone);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strstr(addressBook->contacts[i].phone,phone)!=0)
                    {
                        printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
                printf("Enter the index of the contact to delete:");
                index_b:
                scanf("%d",&index);
                if(index<1 || index>addressBook->contactCount)
                {
                    printf("Invalid index,Please re-enter:");
                    goto index_b;
                }
                else
                {
                    for(int j=index-1;j<addressBook->contactCount-1;j++)
                    {
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully.\n");
                }
                break;
            case 3:
                char email[50];
                printf("Enter the email to delete:");
                scanf("%s", email);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strstr(addressBook->contacts[i].email,email)!=0)
                    {
                        printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
                printf("Enter the index of the contact to delete:");
                index_c:
                scanf("%d",&index);
                if(index<1 || index>addressBook->contactCount)
                {
                    printf("Invalid index,Please re-enter:");
                    goto index_c;
                }
                else
                {
                    for(int j=index-1;j<addressBook->contactCount-1;j++)
                    {
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully.\n");
                }
                break;
        }
}
