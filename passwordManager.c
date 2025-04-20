#include <stdio.h>

int main(){
    FILE *fp;
    int c;
    int operand;

    printf("Choose an operation:\n ");
    printf("Type 1 to view stored creds:\n ");
    printf("Type 2 to add new creds:\n ");
    printf("Type 3 to delete existing creds:\n ");
    printf("Type 4 to search for creds:\n ");
    scanf("%d", &operand );
    switch (operand){
        case 1:
            fp = fopen("password.txt", "r");
            if (fp == NULL) {
                printf("File does not exist\n");
                break;
            }
            while ((c = fgetc(fp)) != EOF)
                printf("%c", c);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            printf("You did not choose a valid operation.\n");
    }   
    return 0;
}

