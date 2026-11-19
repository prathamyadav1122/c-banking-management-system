#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Account {
    int accNo;
    char name[50];
    float balance;
    int accType; 
};


void createAccount(struct Account *accList, int *count);
void depositMoney(struct Account *accList, int count);
void withdrawMoney(struct Account *accList, int count);
void checkBalance(struct Account *accList, int count);
void calculateInterest(struct Account *accList, int count);
void displayAll(struct Account *accList, int count);

int main() {
    int maxAccounts = 100;
    int count = 0;
    int choice;

    
    struct Account *accList = (struct Account *)malloc(maxAccounts * sizeof(struct Account));

    if (accList == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    do {
        printf("\n=== BANK MANAGEMENT SYSTEM ===\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Calculate Simple Interest (Savings)\n");
        printf("6. Display All Accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(accList, &count);
                break;
            case 2:
                depositMoney(accList, count);
                break;
            case 3:
                withdrawMoney(accList, count);
                break;
            case 4:
                checkBalance(accList, count);
                break;
            case 5:
                calculateInterest(accList, count);
                break;
            case 6:
                displayAll(accList, count);
                break;
            case 7:
                printf("\nExiting program. Thank you!\n");
                free(accList); 
                break;
            default:
                printf("\nInvalid choice! Please choose 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}


void createAccount(struct Account *accList, int *count) {
    int index = *count;

    printf("\n--- Create Account ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accList[index].accNo);

    printf("Enter Name: ");
    scanf("%s", accList[index].name);

    printf("Enter Account Type (1 for Savings, 2 for Current): ");
    scanf("%d", &accList[index].accType);

    printf("Enter Initial Deposit: ");
    scanf("%f", &accList[index].balance);

    *count = *count + 1; 
    printf("Account created successfully!\n");
}


void depositMoney(struct Account *accList, int count) {
    int accNo, found = 0;
    float amount;

    if (count == 0) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    for (int i = 0; i < count; i++) {
        if (accList[i].accNo == accNo) {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            if (amount > 0) {
                accList[i].balance += amount;
                printf("Amount deposited successfully! New Balance: %.2f\n", accList[i].balance);
            } else {
                printf("Invalid amount!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}


void withdrawMoney(struct Account *accList, int count) {
    int accNo, found = 0;
    float amount;

    if (count == 0) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    for (int i = 0; i < count; i++) {
        if (accList[i].accNo == accNo) {
            found = 1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > accList[i].balance) {
                printf("Insufficient balance! Current Balance: %.2f\n", accList[i].balance);
            } else if (amount <= 0) {
                printf("Invalid amount!\n");
            } else {
                accList[i].balance -= amount;
                printf("Amount withdrawn successfully! Remaining Balance: %.2f\n", accList[i].balance);
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}


void checkBalance(struct Account *accList, int count) {
    int accNo, found = 0;

    if (count == 0) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    for (int i = 0; i < count; i++) {
        if (accList[i].accNo == accNo) {
            found = 1;
            printf("\n--- Account Details ---\n");
            printf("Account Number : %d\n", accList[i].accNo);
            printf("Name           : %s\n", accList[i].name);
            printf("Account Type   : %s\n", accList[i].accType == 1 ? "Savings" : "Current");
            printf("Balance        : %.2f\n", accList[i].balance);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}


void calculateInterest(struct Account *accList, int count) {
    int accNo, found = 0;
    float rate, time, interest;

    if (count == 0) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    for (int i = 0; i < count; i++) {
        if (accList[i].accNo == accNo) {
            found = 1;

            if (accList[i].accType != 1) {
                printf("Interest calculation is only applicable for Savings Account.\n");
                return;
            }

            printf("Enter Annual Rate of Interest (%%): ");
            scanf("%f", &rate);
            printf("Enter Time (in years): ");
            scanf("%f", &time);

            interest = (accList[i].balance * rate * time) / 100.0;
            printf("\nCalculated Interest: %.2f\n", interest);
            printf("Total Amount after %.1f years: %.2f\n", time, accList[i].balance + interest);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}


void displayAll(struct Account *accList, int count) {
    if (count == 0) {
        printf("\nNo accounts to show!\n");
        return;
    }

    printf("\n--- All Customer Accounts ---\n");
    for (int i = 0; i < count; i++) {
        printf("Acc No: %d | Name: %s | Type: %s | Balance: %.2f\n",
               accList[i].accNo,
               accList[i].name,
               accList[i].accType == 1 ? "Savings" : "Current",
               accList[i].balance);
    }
}