#!/usr/bin/python
from forecastio import api

api_key = "ef446c5824f00f366016c2d608e4e288"
lat = 38.4634014
long = -76.9931073

forecast = api.load_forecast(api_key, lat, long)
cond = forecast.currently().icon
print cond

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
elif cond == 'partly-cloudy-day' or cond == 'partly-cloud-night':
    number = 7
else:
    number = 10

print number