#!/usr/bin/python
from bs import BeautifulSoup, newurllib2
import datetime

Soup = BeautifulSoup.BeautifulSoup
response = newurllib2.urlopen('http://www.dcunited.com/standings').read()
soup = Soup(response)
classes = Soup(str(soup.findAll('tr')))

for c in classes:
    c = Soup(str(c))
    #print c.prettify()
    data = c.find("td", attrs={"data-title": "Club"})
    if data:
        data = data.contents
        foo, data, bar = str(data).split("'")
        if data=="D.C. United":
            break
        else: continue

rank = str(c.find("td", attrs={"data-title": "Rank"}).contents)
foo, rank, bar = rank.split("'")
w = str(c.find("td", attrs={"data-title": "Wins"}).contents)
foo, w, bar = w.split("'")
l = str(c.find("td", attrs={"data-title": "Losses"}).contents)
foo, l, bar = l.split("'")
t = str(c.find("td", attrs={"data-title": "Ties"}).contents)
foo, t, bar = t.split("'")

response = newurllib2.urlopen('http://www.dcunited.com/schedule').read()
soup = Soup(response)

upc = Soup(str(soup.find("li", attrs={"class": "last"})))
date = str(upc.find("div", attrs={"class": "match_details upcoming"}).contents)
foo, date, bar = date.split("'")
day, date = date.split(", ")
m, d = date.split(" ")
d, bar = d.split("t")
time = Soup(str(upc.find("div", attrs={"class": "timing"})))
time = str(time.find("div", attrs={"class": "match_info"}).contents)
foo, time, bar = time.split("'")

today = datetime.date.today()
today = today.day

print "DCU: (%s, %s-%s-%s) Next Match:" % (rank, w, l, t),
if d == today:
    print "Today, %s PM" % time
else:
    print "%s %s, %s" % (m, d, time)