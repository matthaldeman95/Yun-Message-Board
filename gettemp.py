#!/usr/bin/python

with open("weather.csv") as infile:
    for line in infile:
        if "temperature" in line:
            temp = line.split(",")[1].strip()

print temp