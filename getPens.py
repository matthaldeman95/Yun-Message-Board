#!/usr/bin/python
import requests
import quickscraper
from timeout import timeout, TimeoutError
from datetime import datetime as dt


def get_next_game():
    html_file = requests.get('http://www.espn.com/nhl/team/_/name/pit/pittsburgh-penguins').content
    tree = quickscraper.create_tree(html_file)
    game_tree = tree.find_tag_with_attrs('div', {'class': "mod-container mod-no-footer mod-game current pre"})
    d = game_tree.get_by_address('h4/@text')
    d = d.split(",")[1].strip()
    m, d = d.split(" ")
    t = game_tree.get_by_address('h4/span/@text')
    t = t.split("ET")[0].strip()

    team1_tree = game_tree.find_tag_with_attrs('div', {'class': "team team-away"})
    team1 = team1_tree.get_by_address('div/h6/@text').strip()
    if team1.strip == "Pittsburgh":
        at_vs = "at"
        team2_tree = game_tree.find_tag_with_attrs('div', {'class': "team team-home"})
        team2 = team2_tree.get_by_address('div/h6/@text').strip
        opp = team2
    else:
        at_vs = "vs"
        opp = team1

    return d, m, t, at_vs, opp


if __name__ == "__main__":
    with timeout(seconds=20):
        try:
            date, month, time, atvs, opponent = get_next_game()
            today = dt.today()
            print "Penguins: ",
            if int(date) == today.day:
                print "Today, ",
            else:
                print "%s %s" % (month, date),
            print "%s %s" % (atvs, opponent)
        except TimeoutError:
            print ""
