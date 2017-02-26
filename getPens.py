#!/usr/bin/python
import json

with open('/mnt/sda1/data/pens.json') as infile:

    data = json.load(infile)
    output = data['data']

print output