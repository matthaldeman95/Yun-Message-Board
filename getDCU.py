#!/usr/bin/python
from bs import BeautifulSoup, newurllib2
from timeout import timeout, TimeoutError
from datetime import datetime as dt
from calendar import getMonth

Soup = BeautifulSoup.BeautifulSoup


def getRankRecord():
    response = newurllib2.urlopen('http://www.dcunited.com/standings').read()
    soup = Soup(response)

    classes = Soup(str(soup.findAll('tr')))
    for c in classes:
        c = Soup(str(c))
        data = c.find("td", attrs={"data-title": "Club"})
        if data:
            data = data.contents
            foo, data, bar = str(data).split("'")
            if data == "D.C. United":
                break
            else:
                continue

    r = str(c.find("td", attrs={"data-title": "Rank"}).contents)
    r = r.split("'")[1]
    w = str(c.find("td", attrs={"data-title": "Wins"}).contents)
    w = w.split("'")[1]
    l = str(c.find("td", attrs={"data-title": "Losses"}).contents)
    l = l.split("'")[1]
    t = str(c.find("td", attrs={"data-title": "Ties"}).contents)
    t = t.split("'")[1]

    return r, w, l, t


def getNextMatchInfo():

    response = newurllib2.urlopen('http://www.dcunited.com/schedule').read()
    soup = Soup(response)

    upc = Soup(str(soup.find("li", attrs={"class": "last"})))
    date = str(upc.find("div", attrs={"class": "match_details upcoming"}).contents)
    date = date.split("'")[1]
    date = date.split(", ")[1]
    m, d = date.split(" ")
    d = d.split("t")[0]
    t = Soup(str(upc.find("div", attrs={"class": "timing"})))
    t = str(t.find("div", attrs={"class": "match_info"}).contents)
    t = t.split("'")[1]
    t = t.split("PM")[0]

    opp = str(upc.find("div", attrs={"class": "club_container clubtwo"}).contents)
    opp = opp.split('title="')[1]
    opp = opp.split('"')[0]

    m_name, m_number = getMonth(m)

    return d, m_name, m_number, t, opp


if __name__ == "__main__":
    with timeout(seconds=5):
        try:
            rank, wins, losses, ties = getRankRecord()
            day, month_name, month_number, time, opponent = getNextMatchInfo()
            today = dt.today()
            print "DCU: (%s, %s-%s-%s):" % (rank, wins, losses, ties),
            if int(day) == today.day and month_number == today.month:
                print "Today, %s" % time,
            else:
                print "%s %s, %s" % (month_name, day, time),
            print "vs", opponent
        except TimeoutError:
            print ""
