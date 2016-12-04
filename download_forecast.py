#!/usr/bin/python
import requests
import sys
from datetime import datetime as dt

requests.packages.urllib3.disable_warnings()

api_key = "ef446c5824f00f366016c2d608e4e288"
lat = 37.3133548
lng = -121.9772077

url = 'https://api.darksky.net/forecast/%s/%s,%s' \
              '?units=auto' % (api_key, lat, lng)

outfile = open("/mnt/sda1/weather.csv", 'w')

date_time = dt.today()
outfile.write("last updated, %s %s \n" % (str(date_time.date()), str(date_time.time())))

forecast = requests.get(url).content
currently = forecast.split('currently":')[1]
currently, minutely = currently.split(',"minutely":')

temp = str(int(float((currently.split('temperature":')[1]).split(",")[0].strip())))
outfile.write("temperature, %s \n" % temp)
icon = (currently.split('icon":"')[1].split('","')[0]).strip()
outfile.write("icon, %s \n" % icon)

minutely, hourly = minutely.split(',"hourly":')
cond = (hourly.split('summary":"')[1]).split('.","')[0]
outfile.write("conditions, %s \n" % cond)

hourly, daily = hourly.split(',"daily":')


mintemp = str(int(float((daily.split('"temperatureMin":')[1]).split(',"')[0].strip())))
maxtemp = str(int(float((daily.split('"temperatureMax":')[1]).split(',"')[0].strip())))
temp_range = mintemp + '-' + maxtemp
outfile.write("range, %s \n" % temp_range)

outfile.close()
