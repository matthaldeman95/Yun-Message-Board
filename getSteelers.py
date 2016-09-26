#!/usr/bin/python
from bs import BeautifulSoup, newurllib2
from timeout import timeout, TimeoutError
from datetime import datetime as dt

Soup = BeautifulSoup.BeautifulSoup

def getRankRecord():
    response = newurllib2.urlopen('http://www.nfl.com/teams/pittsburghsteelers/schedule?team=PIT').read()
    soup = Soup(response)

    ranking = str(soup.find("p", attrs={"class": "team-overall-ranking"}).contents)

    rk = (ranking.split("'")[1].strip()).split(" ")[0][0]
    rec = ranking.split("'")[2].strip()
    rec = (rec.split("(")[1]).split(")")[0].strip()

    return rk, rec

def getNextGame():
    response = newurllib2.urlopen('http://www.sbnation.com/nfl/teams/pittsburgh-steelers').read()
    soup = Soup(response)
    soup = Soup(str(soup.find("div", attrs={"class": "sbn-pte-head-team-next-game"}).contents))

    next = str(soup.find("p").contents)
    date = ((next.split('        ')[1]).strip()).split("PM")[0].strip()
    t = date.split(',')[3].strip()
    date = date.split(',')[1].strip()
    m, d = date.split(" ")
    d = int(d)

    teams = str(soup.find("h4").contents)
    team1 = (teams.split(">")[1].split("<")[0])
    team2 = (teams.split(">")[3].split("<")[0])
    if team1.strip() == "Pittsburgh Steelers":
        opp = team2.strip()
    else:
        opp = team1.strip()

    words = opp.split(" ")
    if len(words) == 3:
        opp = words[2]
    else:
        opp = words[1]

    return m, d, t, opp


if __name__ == "__main__":
    with timeout(seconds=5):
        try:
            rank, record = getRankRecord()
            month, day, time, opponent = getNextGame()
            today = dt.today().day
            print "Steelers (%s, %s):" % (rank, record),
            if day == today:
                print "Today, %s" % time
            else:
                print "%s %s, %s vs %s" % (month, day, time, opponent)

        except TimeoutError:
            print ""
