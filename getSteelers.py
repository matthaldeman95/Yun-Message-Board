#!/usr/bin/python
from bs import BeautifulSoup, newurllib2
import datetime
Soup = BeautifulSoup.BeautifulSoup
response = newurllib2.urlopen('http://www.nfl.com/teams/pittsburghsteelers/schedule?team=PIT').read()
soup = Soup(response)

ranking = str(soup.find("p", attrs={"class": "team-overall-ranking"}).contents)


foo, rank, record = ranking.split("'")
rank = rank.strip()
foo, rec, bar = record.split("<")
foo, newrec = rec.split(">")
foo, newrec = newrec.split("(")
newrec, bar = newrec.split(")")


response = newurllib2.urlopen('http://www.sbnation.com/nfl/teams/pittsburgh-steelers').read()
soup = Soup(response)
soup = Soup(str(soup.find("div", attrs={"class": "sbn-pte-head-team-next-game"}).contents))
next = str(soup.find("p").contents)
foo, date, bar = next.split("        ")
date = date.strip()
date, bar = date.split("PM")
day, date, year, time = date.split(",")
day = day.strip()
date = date.strip()
m, d = date.split(" ")
d = int(d)

today = datetime.date.today()
today = today.day

print "Steelers (%s, %s) Next Game:" % (rank, newrec),
if (d == today):
    print "Today, %s" % time
else:
    print "%s, %s,%s PM" % (day, date, time)
