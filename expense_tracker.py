from datetime import datetime, timedelta

daily_expenses = []
monthly_expenses = []
categories = {}

try:
    with open("expenses.txt", "r") as f:
        for line in f:
            line = line.strip()

            if not line:
                continue

            if line.startswith("REMINDER"):
                continue

            elif line.startswith("MONTHLY"):
                _, amount = line.split(",")
                monthly_expenses.append(float(amount))

            else:
                day, amount, category = line.split(",")
                amount = float(amount)

                daily_expenses.append(amount)

                if category in categories:
                    categories[category].append(amount)
                else:
                    categories[category] = [amount]

except FileNotFoundError:
    print("expenses.txt not found. Run C program first.")
    exit()

# ---- OUTPUT ----

start_date = datetime(2026, 1, 1)

print("\nDaily Expenses (Day | Date | Amount):")
print("--------------------------------------")

for i, amt in enumerate(daily_expenses):
    date = (start_date + timedelta(days=i)).strftime("%Y-%m-%d")
    print(f"Day {i+1}\t|\t{date}\t|\t{amt}")

print("\nMonthly Expenses:")
print("------------------")
for i, amt in enumerate(monthly_expenses):
    print(f"Month {i+1}\t|\t{amt}")

print("\nCategory Averages:")
print("------------------")
for cat in categories:
    avg = sum(categories[cat]) / len(categories[cat])
    print(f"{cat}\t|\t{round(avg, 2)}")

# Totals
total_yearly = sum(monthly_expenses) if monthly_expenses else sum(daily_expenses)

print("\nTotal Yearly Expense:", total_yearly)

if monthly_expenses:
    print("Monthly Average:", round(total_yearly / len(monthly_expenses), 2))

if daily_expenses:
    print("Daily Average:", round(sum(daily_expenses) / len(daily_expenses), 2))