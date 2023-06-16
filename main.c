#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include "management.h"
#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 100

int main (){
    char c;
    acc accounts[MAX_ACCOUNTS];
    int total_accounts = 0;
    FILE *total = fopen("total_accounts.txt","r");
    FILE *fptr_accounts;
    FILE *fptr_accindex;


    if(total == NULL){
        fclose(total);
        total = fopen("total_accounts.txt", "w");
        if(total==NULL){
         printf ("Something went wrong. Exiting...");
         exit(0);
        }
        fptr_accounts = fopen("accinfo.txt" , "w");
        if(fptr_accounts == NULL){
         printf ("Something went wrong. Exiting...");
         exit(0);
        }
        //-------------------------------------------------------
        fptr_accindex = fopen ("accindex.txt", "w");
        if(fptr_accindex == NULL){
         printf ("Something went wrong. Exiting");
         exit(0);
        }

        fprintf (fptr_accindex, "%d",0);
        fclose(fptr_accindex);

        fprintf(fptr_accounts , "All Bank Accounts\n");
        fprintf(fptr_accounts , "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
        fclose (fptr_accounts);
        total_accounts = 0;
        fprintf (total, "%d" ,total_accounts);
        fclose(total);
    }else{
        fscanf(total, "%d", &total_accounts);
    }

    WelcomeMessage();
    printf("\nPress any key to continue to the program\n");
    fflush(stdin);
    scanf (" %c",&c);

    openingWindow();

    return 0;
}
