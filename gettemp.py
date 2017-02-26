#!/usr/bin/python
import json

with open("/mnt/sda1/data/weather.json") as infile:

    data = json.load(infile)

    temp = data['temperature']

print temp