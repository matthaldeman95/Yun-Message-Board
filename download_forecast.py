#!/usr/bin/python
import requests
from datetime import datetime as dt
import json
import pprint

requests.packages.urllib3.disable_warnings()

api_key = "ef446c5824f00f366016c2d608e4e288"
lat = 37.3133548
lng = -121.9772077

url = 'https://api.darksky.net/forecast/%s/%s,%s' \
              '?units=auto' % (api_key, lat, lng)

data = {}

data['last_updated'] = str(dt.today())

forecast = requests.get(url).content
forecast = json.loads(forecast)

temp = int(forecast['currently']['temperature'])
data['temperature'] = temp

icon = forecast['currently']['icon']
data['icon'] = icon

cond = forecast['hourly']['summary']
data['conditions'] = cond

today = forecast['daily']['data'][0]
mintemp = int(today['temperatureMin'])
maxtemp = int(today['temperatureMax'])
data['min_temp'] = mintemp
data['max_temp'] = maxtemp

with open('/mnt/sda1/data/weather.json', 'w') as outfile:

    json.dump(data, outfile)
