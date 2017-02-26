#!/usr/bin/python
import json

with open("/mnt/sda1/data/weather.json") as infile:

    data = json.load(infile)
    cond = data['icon']

if cond == 'clear-day':
    number = 0
elif cond == 'clear-night':
    number = 1
elif cond == 'rain':
    number = 2
elif cond == 'snow' or cond == 'sleet':
    number = 3
elif cond == 'wind':
    number = 4
elif cond == 'fog':
    number = 5
elif cond == 'cloudy':
    number = 6
elif cond == 'partly-cloudy-day' or cond == 'partly-cloudy-night':
    number = 7
elif cond == 'thunderstorm':
    number = 8
else:
    number = 10

print number
