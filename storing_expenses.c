#include <stdio.h>
#include <string.h>

// Function to check if REMINDER exists
int checkReminder() {
    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) return 0;

    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "REMINDER:") != NULL) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int main() {
    FILE *fp = fopen("expenses.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int day;
    float amount;
    char category[50];

    // ---- Daily Entry ----
    printf("Enter day: ");
    scanf("%d", &day);

    printf("Enter amount: ");
    scanf("%f", &amount);

    printf("Enter category: ");
    scanf("%s", category);

    fprintf(fp, "%d,%.2f,%s\n", day, amount, category);
    fclose(fp);

    printf("Daily expense saved!\n");

    // ---- Check Reminder ----
    if (checkReminder()) {
        float monthly;

        printf("\n*** Month Ending Detected ***\n");
        printf("Enter total monthly expense: ");
        scanf("%f", &monthly);

        // Append monthly data
        fp = fopen("expenses.txt", "a");
        fprintf(fp, "MONTHLY,%.2f\n", monthly);
        fclose(fp);

        printf("Monthly expense saved!\n");

        // ---- Replace REMINDER with REMINDER_DONE ----
        FILE *readFile = fopen("expenses.txt", "r");
        FILE *writeFile = fopen("temp.txt", "w");

        char line[200];

        while (fgets(line, sizeof(line), readFile)) {
            if (strstr(line, "REMINDER:") != NULL) {
                fprintf(writeFile, "REMINDER_DONE\n");
            } else {
                fputs(line, writeFile);
            }
        }

        fclose(readFile);
        fclose(writeFile);

        // Replace original file
        remove("expenses.txt");
        rename("temp.txt", "expenses.txt");
    }

    return 0;
}
