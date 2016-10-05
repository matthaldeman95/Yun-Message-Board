#!/usr/bin/python

with open("weather.csv") as infile:
    for line in infile:
        if "conditions" in line:
            cond = line.split(",")[1].strip()
        elif "range" in line:
            range = line.split(",")[1].strip()

print cond + ", " + range
