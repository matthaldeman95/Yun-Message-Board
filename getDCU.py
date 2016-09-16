#!/usr/bin/python
from bs import BeautifulSoup, newurllib2
import datetime

Soup = BeautifulSoup.BeautifulSoup
response = newurllib2.urlopen('http://www.dcunited.com/standings').read()
soup = Soup(response)
classes = Soup(str(soup.findAll('tr')))

for c in classes:
    c = Soup(str(c))
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
time, bar = time.split("PM")

if(m == "January"):
    m = "Jan"
    mon = 1
elif(m == "February"):
    m = "Feb"
    mon = 2
elif(m == "March"):
    m = "Mar"
    mon = 3
elif(m == "April"):
    m = "Apr"
    mon = 4
elif(m == "May"):
    m = "May"
    mon = 5
elif(m == "June"):
    m = "Jun"
    mon = 6
elif(m == "July"):
    m = "Jul"
    mon = 7
elif(m == "August"):
    m = "Aug"
    mon = 8
elif(m == "September"):
    m = "Sep"
    mon = 9
elif(m == "October"):
    m = "Oct"
    mon = 10
elif(m == "November"):
    m = "Nov"
    mon = 11
elif(m == "December"):
    m = "Dec"
    mon = 12

today = datetime.date.today()

print "DCU: (%s, %s-%s-%s) Next Match:" % (rank, w, l, t),
if int(d) == today.day and mon == today.month:
    print "Today, %s PM" % time
else:
    print "%s %s, %s PM" % (m, d, time)