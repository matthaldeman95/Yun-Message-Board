#!/usr/bin/python
from timeout import timeout, TimeoutError
from datetime import datetime as dt
import datetime
import quickscraper
import requests
import os
import subprocess
import sys


def get_rank_record():

    infile = requests.get('http://www.nfl.com/teams/pittsburghsteelers/schedule?team=PIT').content
    tree = quickscraper.create_tree(infile)
    subtree = tree.find_tag_with_attrs('div', {'class': "team-info"})
    rk = subtree.get_by_address('p[0]/@text')
    rk = rk.split(" ")[0]
    if "st" in rk:
        rk = rk.split("s")[0]
    elif "nd" in rk:
        rk = rk.split("n")[0]
    elif "rd" in rk:
        rk = rk.split("r")[0]
    elif "th" in rk:
        rk = rk.split("th")[0]

    rec = subtree.get_by_address('p[0]/span[0]/@text')
    rec = (rec.split("(")[1]).split(")")[0]

    return rk, rec


def get_next_game():

    #infile = requests.get('http://www.sbnation.com/nfl/teams/pittsburgh-steelers').content
    #infile = os.system("curl http://www.sbnation.com/nfl/teams/pittsburgh-steelers")
    infile = subprocess.Popen("curl -s http://www.sbnation.com/nfl/teams/pittsburgh-steelers", shell=True,
                              stdout=subprocess.PIPE).communicate()[0]

    tree = quickscraper.create_tree(infile)
    subtree = tree.find_tag_with_attrs('div', {'class': "sbn-pte-head-team-next-game"})

    opp_tree = subtree.get_by_address('h4[0]/a[0]/@element')
    team1, team2 = opp_tree.text.split('  ')
    if "Steelers" in team1:
        opp = team2
    else:
        opp = team1
    at_vs = opp_tree.get_by_address('span/@text')
    if at_vs == "@":
        at_vs = "at"

    game_time = subtree.get_by_address('p[0]/@text').strip()
    day, d, y, t = game_time.split(",")
    m, d = d.strip().split(" ")
    t, ampm, tz = t.strip().split(" ")
    y, t = y.strip(), t.strip()

    # Create datetime object from extracted values, subtract timedelta for timezones
    game_time = m + ' ' + d + ' ' + y + ' ' + t + ' ' + ampm
    game_time = dt.strptime(game_time, '%b %d %Y %I:%M %p')
    timezone_adj = datetime.timedelta(hours=3)
    game_time -= timezone_adj

    d = game_time.day
    h = game_time.hour
    if h > 12:
        h -= 12
        ampm = 'PM'
    else:
        ampm = 'AM'
    min = game_time.strftime('%M')
    t = "%d:%s %s" % (h, min, ampm)

    return m, d, t, at_vs, opp



if __name__ == "__main__":
    with timeout(seconds=20):
        try:
            #rank, record = get_rank_record()
            try:
                month, date, time, atvs, opponent = get_next_game()
            except:
                sys.exit()
            #get_next_game()

            today = dt.today().day
            print "Steelers next game: ",
            if int(date) == today:
                print "Today,",
            elif int(date) == today + 1:
                print "Tomorrow,",
            else:
                print "%s %s, " % (month, date),
            print "%s %s %s" % (time, atvs, opponent)

        except TimeoutError:
            print ""
