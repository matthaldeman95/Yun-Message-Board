#!/usr/bin/python
from forecastio import api

api_key = "ef446c5824f00f366016c2d608e4e288"
lat = 38.4634014
long = -76.9931073

forecast = api.load_forecast(api_key, lat, long).daily()
forecastsummary = forecast.summary.split('.')
print forecastsummary[0].strip() + ", " + str(forecast.temp_min) + "-" + str(forecast.temp_max)