from cs50 import get_float

while True:
    cents = get_float("Cents: ")
    if cents > 0:
        break
cents = round(cents*100)

countCoints = 0

# number of quarters
while cents >= 25:
    cents = cents - 25
    countCoints += 1

# number of dimes
while cents >= 10:
    cents = cents - 10
    countCoints += 1

# number of nickels
while cents >= 5:
    cents = cents - 5
    countCoints += 1

# number of pennies
while cents >= 1:
    cents = cents - 1
    countCoints += 1
print(f"cents: {countCoints}")
