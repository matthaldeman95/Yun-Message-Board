#!/usr/bin/python
import requests
import sys
from datetime import datetime as dt

requests.packages.urllib3.disable_warnings()

api_key = "ef446c5824f00f366016c2d608e4e288"
lat = 38.4634014
lng = -76.9931073

url = 'https://api.darksky.net/forecast/%s/%s,%s' \
              '?units=auto' % (api_key, lat, lng)

outfile = open("weather.csv", 'w')
sys.stdout = outfile

date_time = dt.today()
print "last updated,",
print date_time.date(),
print date_time.time()

forecast = requests.get(url).content
currently = forecast.split('currently":')[1]
currently, minutely = currently.split(',"minutely":')

temp = int(float((currently.split('temperature":')[1]).split(",")[0].strip()))
print "temperature,", temp
icon = (currently.split('icon":"')[1].split('","')[0]).strip()
print "icon,", icon

minutely, hourly = minutely.split(',"hourly":')
cond = (hourly.split('summary":"')[1]).split('.","')[0]
print "conditions,", cond

hourly, daily = hourly.split(',"daily":')


mintemp = str(int(float((daily.split('"temperatureMin":')[1]).split(',"')[0].strip())))
maxtemp = str(int(float((daily.split('"temperatureMax":')[1]).split(',"')[0].strip())))
temp_range = mintemp + '-' + maxtemp
print "range,", temp_range

outfile.close()
