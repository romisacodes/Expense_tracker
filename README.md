# Expense Tracker

This project is a simple multi-language expense tracking system built using C, Java, and Python. The idea is to handle different parts of the workflow using different languages while keeping the data shared through a single file.

1.The C program is used for entering and storing daily expenses. It handles basic input and writes everything into a text file so that the data persists.
2.The Java program is responsible for monthly reminders. It checks and appends reminder messages so that the user does not forget to review expenses at the end of the month.
3.The Python script reads the stored data and performs analysis. It processes the file and provides insights like totals and categorized summaries.

All programs are connected through a common file named expenses.txt. This keeps the system simple and avoids the need for databases.
To run the project, each part needs to be executed separately. First compile and run the C program to enter data. Then run the Java program if you want reminder functionality. Finally run the Python script to analyze the stored expenses.

C program:
gcc storing_expenses.c -o tracker
tracker

Java program:
javac MonthlyReminder.java
java MonthlyReminder

Python script:
python expense_tracker.py

The project demonstrates how multiple languages can be used together in a single workflow while keeping the design straightforward and file-based.
