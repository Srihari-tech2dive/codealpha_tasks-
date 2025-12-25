#include <stdio.h>

struct bank {
    int accNo;
    char name[30];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    do {
        printf("\n\n--- BANK ACCOUNT MANAGEMENT SYSTEM ---");
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: printf("\nThank you for using the system!"); break;
            default: printf("\nInvalid choice!");
        }
    } while(choice != 5);

    return 0;
}


void createAccount() {
    FILE *fp = fopen("bank.dat", "ab");
    struct bank b;

    printf("\nEnter Account Number: ");
    scanf("%d", &b.accNo);
    printf("Enter Account Holder Name: ");
    scanf("%s", b.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &b.balance);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!");
}


void deposit() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct bank b;
    int acc;
    float amt;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);
    printf("Enter Deposit Amount: ");
    scanf("%f", &amt);

    while(fread(&b, sizeof(b), 1, fp)) {
        if(b.accNo == acc) {
            b.balance += amt;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("\nAmount Deposited Successfully!");
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("\nAccount Not Found!");
}


void withdraw() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct bank b;
    int acc;
    float amt;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);
    printf("Enter Withdraw Amount: ");
    scanf("%f", &amt);

    while(fread(&b, sizeof(b), 1, fp)) {
        if(b.accNo == acc) {
            if(b.balance >= amt) {
                b.balance -= amt;
                fseek(fp, -sizeof(b), SEEK_CUR);
                fwrite(&b, sizeof(b), 1, fp);
                printf("\nWithdrawal Successful!");
            } else {
                printf("\nInsufficient Balance!");
            }
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("\nAccount Not Found!");
}


void balanceEnquiry() {
    FILE *fp = fopen("bank.dat", "rb");
    struct bank b;
    int acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    while(fread(&b, sizeof(b), 1, fp)) {
        if(b.accNo == acc) {
            printf("\nAccount Holder: %s", b.name);
            printf("\nCurrent Balance: %.2f", b.balance);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("\nAccount Not Found!");
}
    