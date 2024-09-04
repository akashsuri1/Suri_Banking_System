#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "encrypt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
typedef struct account
{
    char userName[60];
    char password[60];
    int balance;
    struct account *next;
} account;
bool checkuser(char *userName, char *getpasw)
{
    FILE *fptr = fopen("user.txt", "r");
    char usertemp[60];
    int balance;
    if (fptr != NULL)
    {
        while (fscanf(fptr, "%s %s %d", usertemp, getpasw, &balance) != EOF)
        {
            if (strcmp(usertemp, userName) == 0)
            {
                fclose(fptr);
                return true;
            }
        }
    }
    fclose(fptr);
    return false;
}
void adduser(char *userName, char *password)
{
    FILE *fptr = fopen("user.txt", "a");
    if (fptr != NULL)
    {
        time_t t;
        struct tm *tm_info;
        time(&t);
        tm_info = localtime(&t);
        char filename[110] = "logs/";
        strcat(filename, userName);
        strcat(filename, ".txt");
        FILE *fptr2 = fopen(filename, "a");
        if(fptr2==NULL){
            perror("tell the error");
        }
        fprintf(fptr2, "Created on %s\n", __DATE__);
        fclose(fptr2);
        fprintf(fptr, "%s %s %d\n", userName, password, 0);
    }
    fclose(fptr);
}
int getBalance(char *userName)
{
    FILE *fptr = fopen("user.txt", "r");
    int balance = 0;
    char usertemp[60];
    char password[60];
    if (fptr != NULL)
    {
        while (fscanf(fptr, "%s %s %d", usertemp, password, &balance) != EOF)
        {
            if (strcmp(usertemp, userName) == 0)
            {
                return balance;
            }
        }
    }
    return balance;
}
void addbalance(char *userName, int amount)
{
    if (amount <= 0)
    {
        printf("Incorrect Value\n");
        return;
    }
    FILE *fptr1 = fopen("user.txt", "r");
    account *head = NULL;
    account *head2 = head;
    int balance2 = 0;
    char usertemp[60];
    char password[60];
    int balance = 0;
    if (fptr1 != NULL)
    {
        while (fscanf(fptr1, "%s %s %d", usertemp, password, &balance) != EOF)
        {
            if (head == NULL)
            {
                head = (account *)malloc(sizeof(account));
                strcpy(head->userName, usertemp);
                strcpy(head->password, password);
                if (strcmp(userName, usertemp) == 0)
                {
                    balance2 = balance;
                    head->balance = balance + amount;
                }
                else
                {
                    head->balance = balance;
                }
                head->next = NULL;
                head2 = head;
            }
            else
            {
                account *temp = (account *)malloc(sizeof(account));
                strcpy(temp->userName, usertemp);
                strcpy(temp->password, password);
                if (strcmp(userName, usertemp) == 0)
                {
                    balance2 = balance;
                    temp->balance = balance + amount;
                }
                else
                {
                    temp->balance = balance;
                }
                temp->next = NULL;
                head2->next = temp;
                head2 = head2->next;
            }
        }
    }
    fclose(fptr1);
    fptr1 = fopen("user.txt", "w");
    if (fptr1 != NULL)
    {
        while (head != NULL)
        {
            account *temp = head;
            fprintf(fptr1, "%s %s %d\n", head->userName, head->password, head->balance);
            head = head->next;
            free(temp);
        }
    }
    fclose(fptr1);
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    char filename[110] = "logs/";
    strcat(filename, userName);
    strcat(filename, ".txt");
    FILE *fptr = fopen(filename, "a");
    fprintf(fptr, "Added %d  %02d-%02d-%04d %d %d\n", amount, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, balance2, balance2 + amount);
    fclose(fptr);
}
void withdraw(char *userName, int amount)
{
    if (amount <= 0)
    {
        printf("Incorrect Value\n");
        return;
    }
    FILE *fptr1 = fopen("user.txt", "r");
    char usertemp[60];
    char password[60];
    int balance = 0;
    account *head = NULL;
    account *head2 = head;
    if (fptr1 != NULL)
    {
        while (fscanf(fptr1, "%s %s %d", usertemp, password, &balance) != EOF)
        {
            if (head == NULL)
            {
                head = (account *)malloc(sizeof(account));
                strcpy(head->userName, usertemp);
                strcpy(head->password, password);
                if (strcmp(userName, usertemp) == 0)
                {
                    if (amount > balance)
                    {
                        printf("Insufficent Balance\n");
                        head->balance = balance;
                    }
                    else
                    {
                        head->balance = balance - amount;
                        time_t t;
                        struct tm *tm_info;
                        time(&t);
                        tm_info = localtime(&t);
                        char filename[110] = "logs/";
                        strcat(filename, userName);
                        strcat(filename, ".txt");
                        FILE *fptr = fopen(filename, "a");
                        fprintf(fptr, "Withdraw %d  %02d-%02d-%04d %d %d\n", amount, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, balance, balance - amount);
                        fclose(fptr);
                    }
                }
                else
                {
                    head->balance = balance;
                }
                head->next = NULL;
                head2 = head;
            }
            else
            {
                account *temp = (account *)malloc(sizeof(account));
                strcpy(temp->userName, usertemp);
                strcpy(temp->password, password);
                if (strcmp(userName, usertemp) == 0)
                {
                    if (amount > balance)
                    {
                        printf("Insufficent Balance\n");
                        temp->balance = balance;
                    }
                    else
                    {
                        temp->balance = balance - amount;
                        time_t t;
                        struct tm *tm_info;
                        time(&t);
                        tm_info = localtime(&t);
                        char filename[110] = "logs/";
                        strcat(filename, userName);
                        strcat(filename, ".txt");
                        FILE *fptr = fopen(filename, "a");
                        fprintf(fptr, "Withdraw %d  %02d-%02d-%04d %d %d\n", amount, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, balance, balance - amount);
                        fclose(fptr);
                    }
                }
                else
                {
                    temp->balance = balance;
                }
                temp->next = NULL;
                head2->next = temp;
                head2 = head2->next;
            }
        }
    }
    fclose(fptr1);
    fptr1 = fopen("user.txt", "w");
    if (fptr1 != NULL)
    {
        while (head != NULL)
        {
            account *temp = head;
            fprintf(fptr1, "%s %s %d\n", head->userName, head->password, head->balance);
            head = head->next;
            free(temp);
        }
    }
    fclose(fptr1);
}
void transfer(char *userName)
{
    char user2[60];
    char usertemp[60];
    char pass[60];
    printf("Enter the userName to transfer to: ");
    scanf("%s", user2);
    printf("%s\n", user2);
    int balance = 0;
    int balance2 = 0;
    account *head = NULL;
    account *head2 = head;
    FILE *fptr = fopen("user.txt", "r");
    bool flag = false;
    if (fptr != NULL)
    {

        while (fscanf(fptr, "%s %s %d", usertemp, pass, &balance) != EOF)
        {
            if (head == NULL)
            {

                head = (account *)malloc(sizeof(account));
                strcpy(head->userName, usertemp);
                strcpy(head->password, pass);
                if (strcmp(userName, usertemp) == 0)
                {
                    balance2 = balance;
                }
                if (strcmp(usertemp, user2) == 0)
                {
                    printf("yes\n");
                    flag = true;
                }
                head->balance = balance;
                head->next = NULL;
                head2 = head;
            }
            else
            {
                account *temp = (account *)malloc(sizeof(account));
                strcpy(temp->userName, usertemp);
                strcpy(temp->password, pass);
                if (strcmp(userName, usertemp) == 0)
                {
                    balance2 = balance;
                }
                if (strcmp(usertemp, user2) == 0)
                {
                    flag = true;
                }
                temp->balance = balance;
                temp->next = NULL;
                head2->next = temp;
                head2 = head2->next;
            }
        }
    }
    fclose(fptr);
    int amount = 0;
    bool flag2 = true;
    if (!flag)
    {
        printf("%s Doesn't Exist's\n", user2);
    }
    else
    {
        printf("Enter The Amount to Transfer: ");
        scanf("%d", &amount);
        getchar();
        if (amount <= 0)
        {
            printf("Incorrect Value\n");
            flag2 = false;
        }
        if (amount > balance2)
        {
            printf("Insufficent Fund To Transfer\n");
            flag2 = false;
        }
    }
    fptr = fopen("user.txt", "w");
    int balance3 = 0;
    if (fptr != NULL)
    {
        while (head != NULL)
        {
            account *temp = head;
            if (flag2 && (strcmp(head->userName, userName) == 0))
            {
                fprintf(fptr, "%s %s %d\n", head->userName, head->password, head->balance - amount);
            }
            else if (flag2 && strcmp(head->userName, user2) == 0)
            {
                balance3 = head->balance;
                fprintf(fptr, "%s %s %d\n", head->userName, head->password, head->balance + amount);
            }
            else
            {
                fprintf(fptr, "%s %s %d\n", head->userName, head->password, head->balance);
            }
            head = head->next;
            free(temp);
        }
    }
    fclose(fptr);
    if (flag && flag2)
    {
        time_t t;
        struct tm *tm_info;
        time(&t);
        tm_info = localtime(&t);
        char filename[110] = "logs/";
        strcat(filename, userName);
        strcat(filename, ".txt");
        fptr = fopen(filename, "a");
        fprintf(fptr, "TransFer %d  %02d-%02d-%04d %d %d\n", amount, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, balance2, balance2 - amount);
        fclose(fptr);
        strcpy(filename, "logs/");
        strcat(filename, user2);
        strcat(filename, ".txt");
        fptr = fopen(filename, "a");
        fprintf(fptr, "Receieved %d  %02d-%02d-%04d %d %d\n", amount, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, balance3, balance3 + amount);
        fclose(fptr);
    }
}
void printlogs(char *userName)
{
    printf("Logs of %s are : \n", userName);
    printf("----------------------------------------\n");
    char filename[110] = "logs/";
    strcat(filename, userName);
    strcat(filename, ".txt");
    FILE *fptr = fopen(filename, "r");
    char buffer[300];
    if (fptr != NULL)
    {
        while (fgets(buffer, 300, fptr) != NULL)
        {
            printf("%s\n", buffer);
        }
        printf("----------------------------------------\n");
        fclose(fptr);
    }
    else
    {
        printf("No Logs\n");
    }
}
int main()
{
    mode_t old_umask = umask(0);
    int choice = 1;
    printf("Welcome to Suri Banking system\n");
    printf("Today is: %s\n", __DATE__);
    do
    {
        sleep(1);
        printf("Press One of The following Keys: \n");
        printf("1 For Login\n");
        printf("2 For Sign Up\n");
        printf("3 To Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        getchar();
        char userName[60];
        char password[60];
        if (choice == 1)
        {
            sleep(1);
            printf("Hello user Please Enter The Following Details: \n");
            printf("UserName: ");
            scanf("%s", userName);
            char getpasw[60];
            if (checkuser(userName, getpasw))
            {
                printf("Password: ");
                scanf("%s", password);
                sleep(1);
                if (strcmp(password, getpasw) == 0)
                {
                    sleep(2);
                    int choice2 = 1;
                    do
                    {
                        printf("Login SuccessFull For %s\n", userName);
                        printf("Tell which operation you want to perform :\n");
                        printf("1 to add Balance\n");
                        printf("2 to Withdraw\n");
                        printf("3 to Transfer\n");
                        printf("4 to Check Balance\n");
                        printf("5 to Check Logs\n");
                        printf("6 to Exit\n");
                        scanf("%d", &choice2);
                        getchar();
                        if (choice2 == 1)
                        {
                            sleep(1);
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d", &amount);
                            getchar();
                            addbalance(userName, amount);
                        }
                        else if (choice2 == 2)
                        {
                            sleep(1);
                            int amount;
                            printf("Please Enter Amount: ");
                            scanf("%d", &amount);
                            getchar();
                            withdraw(userName, amount);
                        }
                        else if (choice2 == 3)
                        {
                            sleep(1);
                            transfer(userName);
                        }
                        else if (choice2 == 4)
                        {
                            sleep(1);
                            printf("The balance of the %s on %s : %d\n", userName, __DATE__, getBalance(userName));
                        }
                        else if (choice2 == 5)
                        {
                            sleep(2);
                            printlogs(userName);
                        }
                        else if (choice2 != 6)
                        {
                            printf("Please Enter correct value\n");
                        }
                    } while (choice2 != 6);
                }
                else
                {
                    printf("wrong password\n");
                }
            }
            else
            {
                sleep(1);
                printf("User Doesn't Exsist\n");
            }
        }
        else if (choice == 2)
        {
            sleep(1);
            printf("Enter the following Details to add User\n");
            printf("UserName: ");
            scanf("%s", userName);
            char getpasw[60];
            if (checkuser(userName, getpasw))
            {
                sleep(1);
                printf("Sorry user already Exist\n");
            }
            else
            {
                printf("Password: ");
                scanf("%s", password);
                adduser(userName, password);
            }
        }
        else if (choice != 3)
        {
            printf("Please Enter correct value\n");
        }
    } while (choice != 3);
    umask(old_umask);
    return 0;
}