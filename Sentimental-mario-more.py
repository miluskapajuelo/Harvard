from cs50 import get_int

# use method of CS50 to get type int  from prompt
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
# create the piramids based on #
for i in range(height):
    for j in range(height - (i + 1)):
        print(" ", end='')
    for k in range(i + 1):
        print("#", end='')
    print("  ", end='')
    for l in range(i + 1):
        print("#", end='')
    print("")
