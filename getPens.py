#!/usr/bin/python
import requests
import quickscraper
from timeout import timeout, TimeoutError
from datetime import datetime as dt


def get_rank_record(in_tree):
    record_string = in_tree.find_tag_with_attrs('div', {'class': "sub-title"}).text
    rec, rk = record_string.split(', ')
    rk = rk.split(' ')[0].strip()

    if "st" in rk:
        rk = rk.split("s")[0]
    elif "nd" in rk:
        rk = rk.split("n")[0]
    elif "rd" in rk:
        rk = rk.split("r")[0]
    elif "th" in rk:
        rk = rk.split("th")[0]

    return rec, rk


def get_next_game(in_tree):
    game_tree = in_tree.find_tag_with_attrs('div', {'class': "mod-container mod-no-footer mod-game current pre"})
    d = game_tree.get_by_address('h4/@text')
    d = d.split(",")[1].strip()
    m, d = d.split(" ")
    t = game_tree.get_by_address('h4/span/@text')
    t = t.split("ET")[0].strip()

    team1_tree = game_tree.find_tag_with_attrs('div', {'class': "team team-away"})
    team1 = team1_tree.get_by_address('div/h6/@text').strip()
    if "Pittsburgh" in team1:
        team2_tree = game_tree.find_tag_with_attrs('div', {'class': "team team-home"})
        team2 = team2_tree.get_by_address('div/h6/@text')
        opp = team2.strip()
    else:
        opp = team1

    at_vs = game_tree.find_tag_with_attrs('div', {'class': "symbol"}).text

    return d, m, t, at_vs, opp


if __name__ == "__main__":
    with timeout(seconds=20):
        try:

            html_file = requests.get('http://www.espn.com/nhl/team/_/name/pit/pittsburgh-penguins').content
            tree = quickscraper.create_tree(html_file)
            record, rank = get_rank_record(tree)
            date, month, time, atvs, opponent = get_next_game(tree)
            today = dt.today()
            print "Penguins (%s, %s):" % (rank, record),
            if int(date) == today.day:
                print "Today,",
            else:
                print "%s %s" % (month, date),
            print "%s %s %s" % (time, atvs, opponent)

        except TimeoutError:
            print ""
