def main():

    # ask user for input
    while True:
        try:
            change = float(input("Change owed (in dollars): "))
            if change > 0:
                break
        except ValueError:
            print("please insert a number")

    # types of money and calculate how much is needed for each money type
    quarters = get_quarters(change)
    change = round(change - (quarters * 0.25), 2)

    dimes = get_dimes(change)
    change = round(change - (dimes * 0.10), 2)

    nickels = get_nickels(change)
    change = round(change - (nickels * 0.05), 2)

    pennies = get_pennies(change)
    change = round(change - (pennies * 0.01), 2)

    coins = quarters + dimes + nickels + pennies

    # print output
    print(f"{coins}")


# define function to get quarters
def get_quarters(change):
    quarters = 0
    while change >= 0.25:
        change = change - 0.25
        quarters += 1
    return quarters


# define function to get dimes
def get_dimes(change):
    dimes = 0
    while change >= 0.10:
        change = change - 0.10
        dimes += 1
    return dimes


# define function to get nickels
def get_nickels(change):
    nickels = 0
    while change >= 0.05:
        change = change - 0.05
        nickels += 1
    return nickels


# define function to get pennies
def get_pennies(change):
    pennies = 0
    while change >= 0.01:
        change = change - 0.01
        pennies += 1
    return pennies


main()