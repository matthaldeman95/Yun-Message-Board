#!/usr/bin/python
import json

with open("/mnt/sda1/data/weather.json") as infile:

    data = json.load(infile)

print data['conditions'] + ', %d-%d' % (data['min_temp'], data['max_temp'])
