#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---- Existing Reminder Check ----
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

// ---- View Expenses ----
void viewExpenses() {
    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("No data found.\n");
        return;
    }

    char line[200];
    printf("\n--- All Expenses ---\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

// ---- Delete Expense ----
void deleteExpense() {
    int day;
    printf("Enter day to delete: ");
    scanf("%d", &day);

    FILE *fp = fopen("expenses.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[200];
    int deleted = 0;

    while (fgets(line, sizeof(line), fp)) {
        int fileDay;
        if (sscanf(line, "%d,", &fileDay) == 1) {
            if (fileDay == day) {
                deleted = 1;
                continue;
            }
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");

    if (deleted)
        printf("Expense deleted.\n");
    else
        printf("Day not found.\n");
}

// ---- Total Spending ----
void totalSpending() {
    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) return;

    char line[200];
    float total = 0;

    while (fgets(line, sizeof(line), fp)) {
        float amt;
        if (sscanf(line, "%*d,%f", &amt) == 1) {
            total += amt;
        }
    }

    fclose(fp);
    printf("Total Spending: %.2f\n", total);
}

// ---- Report ----
void report() {
    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) return;

    char line[200];
    int count = 0;
    float total = 0;

    while (fgets(line, sizeof(line), fp)) {
        float amt;
        if (sscanf(line, "%*d,%f", &amt) == 1) {
            total += amt;
            count++;
        }
    }

    fclose(fp);

    printf("\n--- Report ---\n");
    printf("Total Entries: %d\n", count);
    printf("Total Spending: %.2f\n", total);
    if (count > 0)
        printf("Average Spending: %.2f\n", total / count);
}

// ---- MAIN ----
int main() {
    int choice;

    while (1) {
        printf("\n--- Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Delete Expense\n");
        printf("4. Total Spending\n");
        printf("5. Report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            FILE *fp = fopen("expenses.txt", "a");

            int day;
            float amount;
            char category[50];

            printf("Enter day: ");
            scanf("%d", &day);

            printf("Enter amount: ");
            scanf("%f", &amount);

            printf("Enter category: ");
            scanf("%s", category);

            fprintf(fp, "%d,%.2f,%s\n", day, amount, category);
            fclose(fp);

            printf("Expense added!\n");

            // ---- Existing Reminder Logic (UNCHANGED) ----
            if (checkReminder()) {
                float monthly;

                printf("\n*** Month Ending Detected ***\n");
                printf("Enter total monthly expense: ");
                scanf("%f", &monthly);

                fp = fopen("expenses.txt", "a");
                fprintf(fp, "MONTHLY,%.2f\n", monthly);
                fclose(fp);

                printf("Monthly expense saved!\n");
            }
        }

        else if (choice == 2) viewExpenses();
        else if (choice == 3) deleteExpense();
        else if (choice == 4) totalSpending();
        else if (choice == 5) report();
        else if (choice == 6) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}