#!/usr/bin/env python3

def get_fuel(mass):
    fuel = int(mass/3)-2
    tfuel = fuel
    while fuel > 0:
        fuel = int(fuel/3)-2
        if fuel > 0 : tfuel += fuel
    return tfuel

def main():
    # Open the file
    file = open("input.txt")

    # Calculate total_fuel
    total_fuel = 0
    for mass in file.readlines():
        total_fuel += get_fuel(int(mass))
    print('Total Fuel: %i' % total_fuel)

if __name__ == "__main__":
    main()