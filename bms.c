#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Account{
    int acc_no;
    char name[100];
    char acc_type[10];
    float balance;
    int passwd;
};
int get_acc_no();
void NewAcc();
void ViewAcc();
void Deposit();
void Withdraw();
int main(){
    int n;
    printf("\n");
    printf("\t\t\t\t WELCOME TO BANK MANAGEMENT SYSTEM \n");
    printf("\n");

    printf("1.Create New Account\n2.View Account Details\n3.Deposit Money\n4.Withdraw Money\n5.Balance Enquiry\n6.Transaction History\n7.Fund Transfer\n8.Delete Account\n9.Exit\n");
    
    printf("\n");

    printf("Enter your choice:");
    scanf("%d",&n);

    if (n==1){
        NewAcc();
    }
    else if (n==2){
        ViewAcc();
    }
    else if(n==3){
        Deposit();
    }
    return 0;
}
int get_acc_no(){
    FILE *fptr;
    int last_acc_no=0;
    fptr =fopen("acc_no.dat","rb");
    if(fptr){
        fread(&last_acc_no,sizeof(int),1,fptr);
        fclose(fptr);
    }
    last_acc_no++;
    fptr =fopen("acc_no.dat","wb");
    fwrite(&last_acc_no,sizeof(int),1,fptr);
    fclose(fptr);
    return last_acc_no;
}
void NewAcc(){
    struct Account acc;
    FILE *fptr;
    fptr =fopen("bms.dat","ab");
    if (!fptr) {
        printf("Error opening file!\n");
        return;
    }
    acc.acc_no = get_acc_no();
    printf("Enter Account Holder's Name: ");
    scanf("%s",acc.name);
    char ch;
    printf("Enter Account Type (s for Savings / c for Current): ");
    getchar();
    ch = getchar();
    if (ch=='s'){
        strcpy(acc.acc_type,"Savings");
    }
    else if (ch=='c'){
        strcpy(acc.acc_type,"Current");
    }
    else{
        printf("Enter Valid Output\n");
        return;
    }
    printf("Enter Initial Deposit:");
    scanf("%f",&acc.balance);

    srand(time(0));
    acc.passwd = ((rand()%9000) +1000);
    printf("Your password is %d \n",acc.passwd);
    printf("Kindly keep it to yourself and stay safe.\n");
    fwrite(&acc,sizeof(struct Account),1,fptr);
    fclose(fptr);
}
void ViewAcc(){
    struct Account acc;
    int acc_no, acc_passwd;
    printf("\nEnter your account number:");
    scanf("%d",&acc_no);
    printf("\nEnter your account passwd:");
    scanf("%d",&acc_passwd);

    FILE *fptr;
    fptr=fopen("bms.dat","rb");
    if (!fptr){
        printf("Error, File Not Found\n");
        return;
    }
    while(fread(&acc ,sizeof(struct Account),1,fptr)){
        if (acc.acc_no == acc_no && acc.passwd ==acc_passwd){
            printf("\t\t\t\t\tACCOUNT DETAILS\n");
            printf("Account Number: %d\n",acc.acc_no);
            printf("Account Holder's Name: %s\n",acc.name);
            printf("Account Type: %s\n",acc.acc_type);
            printf("Current Balance: %f\n",acc.balance);
        }
    }
}
void Deposit(){
    struct Account acc;
    int acc_no, acc_passwd;
    printf("\nEnter your account number:");
    scanf("%d",&acc_no);
    printf("\nEnter your account passwd:");
    scanf("%d",&acc_passwd);

    FILE *fptr;
    fptr=fopen("bms.dat","r+b");
    if (!fptr){
        printf("Error, File Not Found\n");
        return;
    }
    float deposit;
    while(fread(&acc ,sizeof(struct Account),1,fptr)){
        if (acc.acc_no == acc_no && acc.passwd ==acc_passwd){
            printf("Enter Amount for Deposit:");
            scanf("%f",&deposit);
            if (deposit <=0){
                printf("Invalid Deposit!!!");
                return;
            }
            else{
                acc.balance+=deposit;
                printf("New Balance Amount: %f",acc.balance);
            }
            long pos = ftell(fptr)- sizeof(struct Account);
            fseek(fptr,pos,SEEK_SET);
            fwrite(&acc,sizeof(struct Account),1,fptr);
            fclose(fptr);
        }
    }
}
void Withdraw(){

}
