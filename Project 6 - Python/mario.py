# prompt user for pyramid height between 1 and 8
while True:
    try:
        height = int(input("Height: "))
        if height >= 1 and height <= 8:
            break
    except ValueError:
        print("Error")

# print pyramid
for row in range(height):
    row += 1
    for spaces in range(height - row):
        print(" ", end="")
    for simbol in range(row):
        print("#", end="")
    print()