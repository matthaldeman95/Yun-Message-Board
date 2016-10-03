#!/usr/bin/python
from timeout import timeout, TimeoutError
from datetime import datetime as dt
import quickscraper
import requests


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

    infile = requests.get('http://www.sbnation.com/nfl/teams/pittsburgh-steelers').content
    tree = quickscraper.create_tree(infile)
    subtree = tree.find_tag_with_attrs('div', {'class': "sbn-pte-head-team-next-game"})
    opp_tree = subtree.get_by_address('h4[0]/a[0]/@element')
    opp = opp_tree.text.split(' ')[2]
    at_vs = opp_tree.get_by_address('span/@text')
    if at_vs == "@":
        at_vs = "at"

    game_time = subtree.get_by_address('p[0]/@text').strip()
    day, d, y, t = game_time.split(",")
    m, d = d.strip().split(" ")
    t = t.split("PM")[0].strip()

    return m, d, t, at_vs, opp


if __name__ == "__main__":
    with timeout(seconds=20):
        try:
            rank, record = get_rank_record()
            month, date, time, atvs, opponent = get_next_game()
            today = dt.today().day
            print "Steelers (%s, %s):" % (rank, record),
            if int(date) == today:
                print "Today, %s" % time,
            else:
                print "%s %s, %s" % (month, date, time),
            print "%s %s" % (atvs, opponent)
        except TimeoutError:
            print ""
