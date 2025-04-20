#include <stdio.h>
#include <string.h>
int main(){
    FILE *fp;
    FILE *tmp;
    int c;
    int operand;
    char str[100];
    char keyword[100];
    char line[256];
    int skip = 0;

    printf("Choose an operation:\n ");
    printf("Type 1 to view stored creds:\n ");
    printf("Type 2 to add new creds:\n ");
    printf("Type 3 to delete existing creds:\n ");
    printf("Type 4 to search for creds:\n ");
    scanf("%d", &operand );
    getchar();
    switch (operand){
        case 1:
            fp = fopen("password.txt", "r"); // open the password.txt file in Read mode to view the contents
            if (fp == NULL) {
                printf("File does not exist\n");
                break;
            }
            while ((c = fgetc(fp)) != EOF){ // goes through until EOF and prints all characters using a while loop
                printf("%c", c);
            }
            fclose(fp);
            break;
        case 2:
            fp = fopen("password.txt", "a"); // opens password.txt in append mode, and then prompts user input
            if (fp == NULL) {
                printf("File does not exist\n");
                break;
            }
            printf("Enter site: ");
            fgets(str, sizeof(str), stdin);
            fprintf(fp, "Site: %s", str);

            printf("Enter Username: ");
            fgets(str, sizeof(str), stdin);
            fprintf(fp, "Username: %s", str);

            printf("Enter Password: ");
            fgets(str, sizeof(str), stdin);
            fprintf(fp, "Password: %s\n", str);

            fclose(fp);
            break;
        case 3:
            fp = fopen("password.txt", "r"); // Creates a tmp file named tmp.txt, finds a keyword in password.txt, skips that line and two below,writes rest to tmp file and renames it 
            tmp = fopen("tmp.txt", "w");
            printf("Enter the site name to delete: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = 0;

            while (fgets(line, sizeof(line), fp)) {
                if (!skip && strstr(line, keyword)){
                    skip = 3;
                    continue;
                }
                if (skip > 0) {
                    skip--;
                    continue;
                }
                fputs(line, tmp);
            }
            fclose(fp);
            fclose(tmp);

            remove("password.txt");
            rename("tmp.txt", "password.txt");
            

            break;
        case 4:
            fp = fopen("password.txt", "r");
            if (fp == NULL) {
                perror("Failed to open file");
                break;
            }
        
            printf("Enter the site name to search: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = 0;
        
            int found = 0;
            skip = 0;
        
            while (fgets(line, sizeof(line), fp)) {
                if (!skip && strstr(line, keyword)) {
                    skip = 3;
                    found = 1;
                    printf("\n Match found for \"%s\":\n", keyword);
                    printf("-----------------------------------\n");
                    printf("%s", line);
                    continue;
                }
                if (skip > 0) {
                    skip--;
                    printf("%s", line);
                }
            }
        
            if (!found) {
                printf("\n No entry found for \"%s\".\n", keyword);
            } else {
                printf("-----------------------------------\n");
            }
        
            fclose(fp);
            break;
        
        default:
            printf("You did not choose a valid operation.\n");
    }   
    return 0;
}

