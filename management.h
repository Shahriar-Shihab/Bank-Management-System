#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 100
#define MAX_ACCOUNT_LENGTH 200
#define MAX_PASSWORD_LENGTH 100
#define MAX_LINE_LENGTH 200

char original_filename[] = "accinfo.txt";
char temp_filename[] = "temporary_accounts.txt";

typedef struct BankAccount {
    int account_number;
    char name[50];
    char address[100];
    char email[20];
    float balance;
    char password[30];
} acc;

acc accounts[MAX_ACCOUNTS];


/*variables*/
char key;
char user;
char emp_username[]="admin";
char emp_password[]="admin";




void clrbuffer(void)                                                            //0
{
    int c;
    while(getchar() != '\n' && getchar() != EOF){

    }
}




void openingWindow(){                                                            // 1
    clear_screen();
    printf ("\nChoose what suits you best\n\n");
    printf ("Press 1 if Employee\n");
    printf ("Press 2 if Customer\n");
    int err=0;
    do{
        fflush(stdin);
        scanf("%c",&key);
        system ("cls");
        switch(key){
            case '1' :
                user = 'E';
                emplogin();
            break;
            case '2':
                user = 'C';
                customer_register_and_login();
            break;
            default :
                printf("Invalid\nPlease Enter 1 or 2\n");
                if(err==4){
                  clear_screen();
                  printf ("\n\nTried too much. Do you want to exit..?\n");
                  printf ("Press 0 to Exit\n");
                  printf ("Press any key to continue.");
                  fflush(stdin);
                  scanf("%c", &key);
                  if(key=='0'){
                     exiting();
                  }
                  else
                     err = 0;
                }
        }
        err++;
    }while(key != '1' && key != '2');

}





void emplogin() {                                                                    //2            Initial
    char user_name[20], password[20];
    int err=0;
    do {
        printf("Username: ");
        fflush(stdin);
        scanf("%19s", user_name);
        fflush(stdin);
        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';  // Remove trailing newline    strcspn() is used to get the index of '\n' in password string. Then the '\n' character is replaced by '\0' character.

        if (strcmp(user_name, emp_username) != 0 || strcmp(password, emp_password) != 0) {
            printf("Invalid password or user name. Please try again\t\t%d times left\n", (3-err));
            if(err==3){
               clear_screen();
               printf ("You have tried too much. Going to main menu");
               fflush(stdout);
               for(int x = 0 ; x < 3 ; x++){
               printf(".");
               fflush(stdout);
               sleep(1);
            }
               openingWindow();
            }
        }
        err++;
    } while (strcmp(user_name, "admin") != 0 || strcmp(password, "admin") != 0);
    empmenu();
}





void empmenu(){                                                                      //3
    clear_screen();
    printf ("Enter your choice\n\n");
    printf ("1. Sum of all account deposits.\n");
    printf ("2. Show all bank accounts by account number\n");               //acc no  balance address  email
    printf ("3. Sort bank accounts in ascending order by balance, from lowest to highest\n");
    printf ("4. Sort bank accounts in descending order by balance, from highest to lowest\n");
    printf ("5. Account Search by Account Number\n");
    printf ("6. Account Search by Balance\n");
    printf ("7. Log out\n");
    printf ("Press any other key to exit...\n");
    scanf (" %c",&key);
    clear_screen();
    switch(key){
        case '1' : balance_sum(accounts);
        break;
        case '2' : display_all_accounts(accounts);
        break;
        case '3' : Display_Accounts_In_Asceneing_Order(accounts);
        break;
        case '4' : Display_Accounts_In_Descending_Order(accounts);
        break;
        case '5' : account_search_customer(accounts);
        break;
        case '6' : Account_search_by_balance(accounts);
        break;
        case '7' : openingWindow();
        break;
        default :
        clear_screen();
        exiting();
    }
}





void cstmenu() {
    clear_screen();
    fflush(stdin);
    printf("Enter your choice\n\n");
    printf("1. Fund Deposit\n");
    printf("2. Fund Withdraw\n");
    printf("3. Current Balance\n");
    printf("4. Fund Transfer\n");
    printf("5. Close Account\n");
    printf("6. Display Account Details\n");
    printf("7. Update Account Details\n");
    printf("8. Log Out\n");
    printf("Enter any other key to exit...");

    char key;
    scanf(" %c", &key);
    getchar();  // Consume newline character

    clear_screen();
    switch (key) {
        case '1':
            deposit(accounts);
            break;
        case '2':
            withdraw(accounts);
            break;
        case '3':
            display_balance(accounts);
            break;
        case '4':
            transfer(accounts);
            break;
        case '5':
            delete_account(accounts);
            break;
        case '6':
            account_search_customer(accounts);
            break;
        case '7':
            update(accounts);
            break;
        case '8':
            logOut();
            break;
        default:
            exitOrMenu();
            break;
    }
    exitOrMenu();
}




void customer_register_and_login(){                                                                     //7
    fflush (stdin);
    printf ("Enter your choice\n\n");
    printf ("1. login.\n");
    printf ("2. Register a new account\n");
    printf ("3. Return to Opening Menu\n");
    fflush (stdin);
    scanf (" %c", &key);
    fflush(stdin);
    clear_screen();
    switch (key){
    case '1' :  login();
        break;
    case '2':   create_account(accounts);
        break;
    case '3':   openingWindow();
        break;
    default: printf ("Invalid");

    }

}





void logOut(){                                                                       //15
    if(user=='E'){
      emplogin();
    }
    else if(user == 'C')
    {
        customer_register_and_login();
    }

    else{
       printf ("Something went wrong.\n");
       exiting();
    }
}





void exitOrMenu(){                                                                   //16
    printf("\nPress 1 to return to previous menu...\n");
    printf ("Press any other key to exit...\n");
    fflush(stdin);
    scanf (" %c", &key);
    if(key == '1'){
        if(user=='E'){
            empmenu();
        }else{
            cstmenu();
        }
    }else{
        exiting();
    }
    clear_screen();
    printf ("Are you sure you want to exit?\n");
    printf ("Press 1 to confirm\n");
    printf ("Back\n");
    fflush (stdin);
    scanf (" %c", &key);
    if(key == '1'){
        exiting();
    }
}






void exiting(){
   clear_screen();
        printf ("\n\n\n\n\n\n\t\t\t\tExiting");
        fflush(stdout);
         for(int x = 0 ; x < 3 ; x++){
            printf(".");
            fflush(stdout);
            sleep(1);
         }
        exit(0);
}





void clear_screen(){
   printf("\033[H\033[J");
}





void fprint_time(FILE *ptr){
   time_t current;
    time(&current);
    fprintf (ptr, "%s\n", ctime(&current));
}





void create_account(acc accounts[])
{
    int index;

    FILE *fptr_accindex = fopen("accindex.txt", "r");
    fscanf(fptr_accindex, "%d", &index);
    fclose(fptr_accindex);

    fopen("accindex.txt", "w");
    fprintf(fptr_accindex, "%d", index + 1);
    fclose(fptr_accindex);

    FILE *fptr_total_accounts = fopen("total_accounts.txt", "w");
    fprintf(fptr_total_accounts, "%d", index + 1);
    fclose(fptr_total_accounts);

    accounts[index].account_number = 1000 + index;
    FILE *fptr_accinfo = fopen("accinfo.txt", "a");
    printf("Your auto generated account number is: %d\n", accounts[index].account_number);

    printf("Account Holder's Name: ");
    fgets(accounts[index].name, sizeof(accounts[index].name), stdin);

    printf("House Address: ");
    fgets(accounts[index].address, sizeof(accounts[index].address), stdin);

    printf("E-Mail Address: ");
    fgets(accounts[index].email, sizeof(accounts[index].email), stdin);
    fflush(stdin);

    printf("Initial Deposit: ");
    scanf("%f", &accounts[index].balance);
    getchar();

    printf("Account Password: ");
    fgets(accounts[index].password, sizeof(accounts[index].password), stdin);

    fprintf(fptr_accinfo, "Account Number: %d\n", accounts[index].account_number);
    fprintf(fptr_accinfo, "Account Holder's Name: %s\n", accounts[index].name);
    fprintf(fptr_accinfo, "House Address: %s\n", accounts[index].address);
    fprintf(fptr_accinfo, "E-Mail: %s\n", accounts[index].email);
    fprintf(fptr_accinfo, "Balance: $ %.0f\n", accounts[index].balance);
    fprintf(fptr_accinfo, "Password: %s\n", accounts[index].password);
    clear_screen();
    printf("Account created successfully!");

    fclose(fptr_accinfo);

    printf ("\nPress 0 to login\n");
    printf ("press 1 to go to main menu\n");
    printf ("Press any other key to exit..\n");
    fflush(stdin);
    scanf (" %c", &key);
    switch (key){
        case '0' : login();
        break;
        case '1' : openingWindow();
        break;
        default: exiting();
    }
}





void deposit(acc accounts[])
{
    int account_number;

    printf("Enter account number: ");
    scanf("%d", &account_number);

    int index = account_number - 1000;
    float deposit_amount;
    int total_elements;
    int i;

    printf("Enter deposit amount: ");
    scanf("%f", &deposit_amount);
    getchar();

    FILE *fptr_accinfo, *fptr_temp, *fptr_total_accounts;

    fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    fptr_accinfo = fopen(original_filename, "r");
    fptr_temp = fopen(temp_filename, "w");

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[i].password);

        if (i != index)
        {
            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
            fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
            fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
            fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
        }
        else if (i == index)
        {
            accounts[i].balance += deposit_amount;
            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
            fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
            fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
            fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
        }

    }

    fclose(fptr_accinfo);
    fclose(fptr_temp);

    remove(original_filename);
    rename(temp_filename, original_filename);

    printf("Funds deposited successfully!\n");
}







void withdraw(acc accounts[])
{
    int account_number;

    printf("Enter account number: ");
    scanf("%d", &account_number);
    getchar();

    int index = account_number - 1000;
    float withdrawal_amount;
    int total_elements;
    int i;

    printf("Enter withdrawal amount: ");
    scanf("%f", &withdrawal_amount);
    getchar();

    FILE *fptr_accinfo, *fptr_temp, *fptr_total_accounts;

    fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    fptr_accinfo = fopen(original_filename, "r");
    fptr_temp = fopen(temp_filename, "w");

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[i].password);

        if (i != index)
        {
            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
            fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
            fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
            fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
        }
        else if (i == index)
        {
            if(withdrawal_amount > accounts[i].balance)
            {
                printf("Insufficient funds. Current Balance: %.2f", accounts[i].balance);
            }
            else
            {
                accounts[i].balance -= withdrawal_amount;
                fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
                fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
                fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
                fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
                fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
                fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
            }

        }
    }

    fclose(fptr_accinfo);
    fclose(fptr_temp);

    remove(original_filename);
    rename(temp_filename, original_filename);

    printf("Funds withdrawn successfully!\n");
}





void proto_transfer(acc accounts[], int sender_account_number, int receiver_account_number, float transfer_amount)
{

    int total_elements;
    int i;

    int sender_index = sender_account_number - 1000;
    int receiver_index = receiver_account_number - 1000;

    FILE *fptr_accinfo, *fptr_temp, *fptr_total_accounts;

    fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    fptr_accinfo = fopen(original_filename, "r");
    fptr_temp = fopen(temp_filename, "w");

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &(accounts[i].balance));
        fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[i].password);

        if (i == sender_index)
        {
            if (transfer_amount > accounts[i].balance)
            {
                printf("Current Balance: %.2f. Insufficient funds!\n", accounts[i].balance);
                fclose(fptr_accinfo);
                fclose(fptr_temp);
                remove(temp_filename);
                return;
            }
            else
            {
                accounts[i].balance -= transfer_amount;
                fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
                fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
                fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
                fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
                fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
                fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
            }
        }
        else if (i == receiver_index)
        {
            accounts[i].balance += transfer_amount;
            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
            fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
            fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
            fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
        }
        else
        {
            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
            fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
            fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
            fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
        }
    }

    fclose(fptr_accinfo);
    fclose(fptr_temp);

    remove(original_filename);
    rename(temp_filename, original_filename);

    printf("Funds transferred successfully!\n");
}






void transfer(acc accounts[])
{
    int sender_account_number, receiver_account_number;
    float transfer_amount;

    printf("Your account number: ");
    scanf("%d", &sender_account_number);

    printf("Recipient's account number: ");
    scanf("%d", &receiver_account_number);

    printf("Fund transfer amount: ");
    scanf("%f", &transfer_amount);

    proto_transfer(accounts, sender_account_number, receiver_account_number, transfer_amount);
}






void display_balance(acc accounts[])
{
    int account_number;
    float current_balance;

    printf("Enter account number: ");
    scanf("%d", &account_number);
    getchar();

    int index = account_number - 1000;

    FILE *fptr_accinfo = fopen("accinfo.txt", "r");

    if (fptr_accinfo == NULL)
    {
        printf("Error opening account information file.\n");
        return;
    }
    else
    {
        for(int i = 0; i <= index; i++)
        {
            fscanf(fptr_accinfo, "Account Number: %*d\n");
            fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[index].name);
            fscanf(fptr_accinfo, "House Address: %*[^\n]\n");
            fscanf(fptr_accinfo, "E-Mail: %*[^\n]\n");
            fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[index].balance);
            fscanf(fptr_accinfo, "Password: %*[^\n]\n");
        }

    fclose(fptr_accinfo);

    printf("Account Holder: %s\n", accounts[index].name);
    printf("Current Balance: $%.2f\n", accounts[index].balance);
    }
}





void account_search_customer(acc accounts[])
{
    int account_number;

    printf("Enter account number: ");
    scanf("%d", &account_number);
    getchar();
    printf("\n\n");

    int index = account_number - 1000;

    FILE *fptr_accinfo = fopen("accinfo.txt", "r");

    if (fptr_accinfo == NULL)
    {
        printf("Error opening account information file.\n");
        return;
    }
    else
    {
        for (int i = 0; i <= index; i++)
        {
            fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[index].account_number);
            fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[index].name);
            fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[index].address);
            fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[index].email);
            fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[index].balance);
            fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[index].password);
        }

        if (user == 'C')
        {
            printf("Account Number: %d   |   Account Holder: %s  |   Address: %s    |   E-Mail: %s   |   Current Balance: $ %.2f   |   Password: %s\n\n\n", accounts[index].account_number, accounts[index].name, accounts[index].address, accounts[index].email, accounts[index].balance, accounts[index].password);
        }
        else if (user == 'E')
        {
            printf("Account Number: %d   |   Account Holder: %s  |   Address: %s    |   E-Mail: %s   |   Current Balance: $ %.2f\n\n\n", accounts[index].account_number, accounts[index].name, accounts[index].address, accounts[index].email, accounts[index].balance);
        }
    }

    fclose(fptr_accinfo);
    exitOrMenu();
}







void delete_account(acc accounts[])
{
    int account_number;
    int total_elements;

    printf("Enter account number to delete: ");
    scanf("%d", &account_number);
    getchar();

    int index = account_number - 1000;

    FILE *fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    FILE *fptr_accinfo = fopen("accinfo.txt", "r");
    FILE *fptr_temp = fopen("temp.txt", "w");

    if (fptr_accinfo == NULL)
    {
        printf("Error opening account information file.\n");
        return;
    }
    else
    {
        for (int i = 0; i < total_elements; i++)
        {
            fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
            fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
            fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
            fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
            fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
            fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[i].password);

            if (i == index)
            {

            }
            else
            {
                fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
                fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
                fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
                fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
                fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
                fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
            }


        }
    }

    fclose(fptr_accinfo);
    fclose(fptr_temp);

    remove("accinfo.txt");
    rename("temp.txt", "accinfo.txt");

    // Update the total_accounts value
    total_elements--;
    fptr_total_accounts = fopen("total_accounts.txt", "w");
    fprintf(fptr_total_accounts, "%d", total_elements);
    fclose(fptr_total_accounts);

    printf("Account deletion completed.\n");
    printf("Remaining funds withdrawn automatically..");
}






void update(acc accounts[])
{
    int account_number;
    int index;
    int total_elements;
    int i;

    printf("Enter account number: ");
    scanf("%d", &account_number);
    getchar();

    index = account_number - 1000;

    FILE *fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    FILE *fptr_accinfo = fopen(original_filename, "r");
    FILE *fptr_temp = fopen(temp_filename, "w");

    int found = 0;

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[i].password);

        if (i != index)
        {
            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);
            fprintf(fptr_temp, "Account Holder's Name: %s\n", accounts[i].name);
            fprintf(fptr_temp, "House Address: %s\n", accounts[i].address);
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);
            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);
            fprintf(fptr_temp, "Password: %s\n", accounts[i].password);
        }
        else if (i == index)
        {
            found = 1;

            fprintf(fptr_temp, "Account Number: %d\n", accounts[i].account_number);

            printf("New Account Holder's Name: ");
            fgets(accounts[i].name, sizeof(accounts[i].name), stdin);
            fprintf(fptr_temp, "Account Holder's Name: %s", accounts[i].name);

            printf("New House Address: ");
            fgets(accounts[i].address, sizeof(accounts[i].address), stdin);
            fprintf(fptr_temp, "House Address: %s", accounts[i].address);

            printf("New E-Mail Address: ");
            fgets(accounts[i].email, sizeof(accounts[i].email), stdin);
            accounts[i].email[strcspn(accounts[i].email, "\n")] = '\0';
            fprintf(fptr_temp, "E-Mail: %s\n", accounts[i].email);

            fprintf(fptr_temp, "Balance: $ %.2f\n", accounts[i].balance);

            printf("New Account Password: ");
            fgets(accounts[i].password, sizeof(accounts[i].password), stdin);
            accounts[i].password[strcspn(accounts[i].password, "\n")] = '\0';
            fprintf(fptr_temp, "Password: %s", accounts[i].password);
        }
    }

    fclose(fptr_accinfo);
    fclose(fptr_temp);

    remove(original_filename);
    rename(temp_filename, original_filename);

    if (found)
    {
        printf("Account information updated successfully!\n");
        printf("Updated Account Information:\n");
        printf("Account Number: %d\n", accounts[index].account_number);
        printf("Account Holder's Name: %s\n", accounts[index].name);
        printf("House Address: %s\n", accounts[index].address);
        printf("E-Mail: %s\n", accounts[index].email);
        printf("Balance: $ %.2f\n", accounts[index].balance);
        printf("Password: %s\n", accounts[index].password);
    }
    else
    {
        printf("Invalid account number. Account information not updated.\n");
    }
}




void balance_sum(acc accounts[])
{

    int total_elements;
    int i;
    float sum = 0;

    FILE *fptr_accinfo, *fptr_total_accounts;

    fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    fptr_accinfo = fopen(original_filename, "r");

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %*d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %*[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %*[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %*[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %*[^\n]\n", accounts[i].password);

        sum += accounts[i].balance;
    }

    printf("Total Deposit in Bank: $ %.2f\n\n\n", sum);

    fclose(fptr_accinfo);
    exitOrMenu();
}





void login() {
    int account_number;
    char password[MAX_PASSWORD_LENGTH];
    int total_elements;
    int i;
    int result1, result2;
    int match_found = 0;  // Flag variable to track matching account

    printf("Enter your account number: ");
    scanf("%d", &account_number);
    getchar();  // Consume newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    FILE *fptr_accinfo, *fptr_total_accounts;

    fptr_total_accounts = fopen("total_accounts.txt", "r");
    fscanf(fptr_total_accounts, "%d", &total_elements);
    fclose(fptr_total_accounts);

    fptr_accinfo = fopen(original_filename, "r");

    for (i = 0; i < total_elements; i++) {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %*c%[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %*c%[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %*c%[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %*f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %[^\n]\n", accounts[i].password);

        result1 = account_number - accounts[i].account_number;
        result2 = strcmp(password, accounts[i].password);

        if (result1 == 0 && result2 == 0) {
            match_found = 1;  // Set the flag for matching account
            break;  // Exit the loop since a match is found
        }
    }

    fclose(fptr_accinfo);

    if (match_found) {
        clear_screen();
        cstmenu();
    }
    else
    {
        clear_screen();

        int choice;
        printf("Press 1: Try again\n");
        printf("\nPress 2: Return to previous menu.");
        scanf("%d", &choice);
        clear_screen();

        if(choice == 1)
        {
            printf("Invalid account number or password. Try again\n");
            login();
        }
        else if(choice == 2)
        {
            customer_register_and_login();
        }
    }
}






void display_all_accounts(acc accounts[])
{
   int i,j,swap,total_elements;
   acc temp;
   FILE *fptr_accinfo, *fptr_total_accounts;

   fptr_accinfo = fopen(original_filename, "r");

   fptr_total_accounts=fopen("total_accounts.txt","r");

   fscanf(fptr_total_accounts,"%d",&total_elements);

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %*[^\n]\n", accounts[i].password);
    }

   printf("--------------------Information of all accounts--------------------\n");
   printf("-------------------------------------------------------------------\n\n\n");
   for(i=0; i<total_elements;i++){
      printf("Account Number: %d | Account Holder's Name: %s | House Address: %s | E-Mail: %s | Balance: $ %.2f\n", accounts[i].account_number, accounts[i].name, accounts[i].address, accounts[i].email, accounts[i].balance);
      printf("\n\n");
   }
   printf("-------------------------------------------------------------------\n");

   fclose(fptr_accinfo);
   fclose(fptr_total_accounts);
   exitOrMenu();
}





void Display_Accounts_In_Asceneing_Order(acc accounts[])
{
   int i,j,swap,total_elements;
   acc temp;
   FILE *fptr_accinfo, *fptr_total_accounts;

   fptr_accinfo = fopen(original_filename, "r");

   fptr_total_accounts=fopen("total_accounts.txt","r");

   fscanf(fptr_total_accounts,"%d",&total_elements);

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %*[^\n]\n", accounts[i].password);
    }
    for(i=0; i<total_elements-1;i++){
      swap=0;
      for(j=0;j<total_elements-i-1;j++){
         if(accounts[j].balance>accounts[j+1].balance){
            acc temp = accounts[j];
            accounts[j] = accounts[j+1];
            accounts[j+1]= temp;
            swap =1;
         }
      }
      if (swap==0){
         break;
      }
   }

   printf("--------------------Accounts Information from Lowest to Highest Balance--------------------\n\n\n");
   for(i=0; i<total_elements;i++){
      printf("Account Number: %d | Account Holder's Name: %s | Current Balance: $ %.2f\n", accounts[i].account_number, accounts[i].name, accounts[i].balance);
      printf("\n\n");
   }
   fclose(fptr_accinfo);
   fclose(fptr_total_accounts);
   exitOrMenu();
}





void Display_Accounts_In_Descending_Order(acc accounts[])
{
   int i,j,swap,total_elements;
   acc temp;
   FILE *fptr_accinfo, *fptr_total_accounts;

   fptr_accinfo = fopen(original_filename, "r");

   fptr_total_accounts=fopen("total_accounts.txt","r");

   fscanf(fptr_total_accounts,"%d",&total_elements);

    for (i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %*[^\n]\n", accounts[i].password);
    }
    for(i=0; i<total_elements-1;i++){
      swap=0;
      for(j=0;j<total_elements-i-1;j++){
         if(accounts[j].balance<accounts[j+1].balance){
            acc temp = accounts[j];
            accounts[j] = accounts[j+1];
            accounts[j+1]= temp;
            swap =1;
         }
      }
      if (swap==0){
         break;
      }
   }
   printf("--------------------Accounts Information from Highest to Lowest Balance--------------------\n\n\n");
   for(i=0; i<total_elements;i++){
      printf("Account Number: %d | Account Holder's Name: %s | Current Balance: $ %.2f\n", accounts[i].account_number, accounts[i].name, accounts[i].balance);
      printf("\n\n");
   }
   fclose(fptr_accinfo);
   fclose(fptr_total_accounts);
   exitOrMenu();
}








// Function to add a delay
void delay(int milliseconds) {
    Sleep(milliseconds);
}

// Function to print animated welcome message
void WelcomeMessage() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\tWelcome\n\n");
    delay(500);

    printf("\t\t\t\tProject: Bank Management System\n\n");
    delay(500);

    printf("\t\t\t\tCourse Name: Programming Language I Lab\n\n");
    printf("\t\t\t\tCourse Code: CSE 115L\n");
    delay(500);

    printf("\n\t\t\t\tProgrammers:\n");
    printf("\t\t\t\t1. Touhidul Islam Shihab\t\t ID: 2312717042\n");
    delay(500);

    printf("\t\t\t\t2. Junaidur Rahman Shafi\t\t ID: 2312048642\n");
    delay(500);

    printf("\t\t\t\t3. Samina Islam Mim\t\t\t ID: 2311943042\n");
    delay(500);

    printf("\n\t\t\t\tInstructors:\n");
    printf("\t\t\t\tFaculty: Md. Shahriar Hussain (HSM)\n");
    delay(500);

    printf("\t\t\t\tLab Instructor: Farzana Islam\n");
    delay(500);

    delay(500);

    delay(500);

    delay(500);
    delay(500);
}









void Account_search_by_balance(acc accounts[])
{
    int choice;
    printf("Press 1 to search account less than certain amount\n");
    printf("Press 2 to search account greater than certain amount\n");
    printf("Enter your option: ");
    scanf("%d", &choice);
    clear_screen();

    switch(choice)
    {
        case 1: account_less_than_certain_amount(accounts);
                break;

        case 2: account_greater_than_certain_amount(accounts);
                break;

        default:    printf("Invalid\n Please enter 1 or 2\n");
    }
}





void account_less_than_certain_amount(acc accounts[])
{   int i,total_elements;
   FILE *fptr_accinfo, *fptr_total_accounts;

   fptr_accinfo = fopen(original_filename, "r");

   fptr_total_accounts=fopen("total_accounts.txt","r");

   fscanf(fptr_total_accounts,"%d",&total_elements);

    float amount;
    printf("Enter the amount: ");
    scanf("%f", &amount);
    clear_screen();

    printf("--------------------INFORMATION OF RELEVANT ACOUNTS--------------------\n");
    printf("-----------------------------------------------------------------------\n\n");
    for(i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %*[^\n]\n", accounts[i].password);
    }

   for(i=0; i<total_elements;i++)
   {
       if(accounts[i].balance < amount)
       {
            printf("Account Number: %d  |   Account Holder: %s  |   Current Balance: $ %.2f", accounts[i].account_number, accounts[i].name, accounts[i].balance);
            printf("\n\n");
       }
   }
    printf("-----------------------------------------------------------------------\n\n\n\n\n");

    fclose(fptr_accinfo);
    fclose(fptr_total_accounts);
    exitOrMenu();
}






void account_greater_than_certain_amount(acc accounts[])
{   int i,total_elements;
   FILE *fptr_accinfo, *fptr_total_accounts;

   fptr_accinfo = fopen(original_filename, "r");

   fptr_total_accounts=fopen("total_accounts.txt","r");

   fscanf(fptr_total_accounts,"%d",&total_elements);

    float amount;
    printf("Enter the amount: ");
    scanf("%f", &amount);
    clear_screen();

    printf("--------------------INFORMATION OF RELEVANT ACOUNTS--------------------\n");
    printf("-----------------------------------------------------------------------\n\n");
    for(i = 0; i < total_elements; i++)
    {
        fscanf(fptr_accinfo, "Account Number: %d\n", &accounts[i].account_number);
        fscanf(fptr_accinfo, "Account Holder's Name: %[^\n]\n", accounts[i].name);
        fscanf(fptr_accinfo, "House Address: %[^\n]\n", accounts[i].address);
        fscanf(fptr_accinfo, "E-Mail: %[^\n]\n", accounts[i].email);
        fscanf(fptr_accinfo, "Balance: $ %f\n", &accounts[i].balance);
        fscanf(fptr_accinfo, "Password: %*[^\n]\n", accounts[i].password);
    }

   for(i=0; i<total_elements;i++)
   {
       if(accounts[i].balance >= amount)
       {
            printf("Account Number: %d  |   Account Holder: %s  |   Current Balance: $ %.2f", accounts[i].account_number, accounts[i].name, accounts[i].balance);
            printf("\n\n");
       }
   }
    printf("-----------------------------------------------------------------------\n\n\n\n\n");

    fclose(fptr_accinfo);
    fclose(fptr_total_accounts);
    exitOrMenu();
}











