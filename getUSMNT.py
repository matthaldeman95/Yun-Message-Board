#!/usr/bin/python
from bs import BeautifulSoup, newurllib2
import datetime
Soup = BeautifulSoup.BeautifulSoup

response = newurllib2.urlopen('http://www.ussoccer.com/mens-national-team/schedule-tickets').read()
soup = Soup(response)


soup = soup.find("tr", attrs={"class": "year-2016 team-MNT"})
#print soup.prettify()

dt = str(soup.find("time").contents)
foo, date, bar = dt.split("'")
date, year = date.split(',')
m, day = date.split(" ")
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
    m = "Sept"
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

teams = soup.findAll("span", attrs={"itemprop": "competitor"})
comp = str(teams[1].find("span", attrs={"itemprop": "name"}).contents)
foo, opp, bar = comp.split("'")

print "USMNT Next Match: ",
if mon == today.month & int(day) == today.day:
    print "Today vs",
else:
    print "%s %s vs" % (m, day),
print opp
