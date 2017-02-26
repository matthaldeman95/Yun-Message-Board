#!/usr/bin/python
import requests
from datetime import datetime as dt
import json

requests.packages.urllib3.disable_warnings()

api_key = "ef446c5824f00f366016c2d608e4e288"
lat = 37.3133548
lng = -121.9772077

url = 'https://api.darksky.net/forecast/%s/%s,%s' \
              '?units=auto' % (api_key, lat, lng)

data = {}

date_time = str(dt.today())
data['last_updated'] = date_time

forecast = requests.get(url).content
currently = forecast.split('currently":')[1]
currently, minutely = currently.split(',"minutely":')
temp = int(float((currently.split('temperature":')[1]).split(",")[0].strip()))
data['temperature'] = temp

icon = (currently.split('icon":"')[1].split('","')[0]).strip()
data['icon'] = icon

minutely, hourly = minutely.split(',"hourly":')
cond = (hourly.split('summary":"')[1]).split('.","')[0]
data['conditions'] = cond

hourly, daily = hourly.split(',"daily":')

mintemp = int(float((daily.split('"temperatureMin":')[1]).split(',"')[0].strip()))
maxtemp = int(float((daily.split('"temperatureMax":')[1]).split(',"')[0].strip()))
data['min_temp'] = mintemp
data['max_temp'] = maxtemp

with open('/mnt/sda1/data/weather.json', 'w') as outfile:

    json.dump(data, outfile)
