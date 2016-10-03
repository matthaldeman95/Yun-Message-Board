#!/usr/bin/python
from timeout import timeout, TimeoutError
from datetime import datetime as dt
from months import getmonth
import requests
import quickscraper


def get_rank_record():
    infile = requests.get('http://www.dcunited.com/standings').content
    tree = quickscraper.create_tree(infile)
    dcu_found = False
    index = 1
    subtree = tree.find_tag_with_attrs('table', {'class': "standings_table"})
    subtree = subtree.get_by_address('tbody/@element')
    while not dcu_found:
        team_line = subtree.get_by_address('tr[%d]/td[1]/@text' % index)
        if "United" in team_line:
            dcu_found = True
        else:
            index += 1

    dcu_tree = subtree.get_by_address('tr[%d]/@element' % index)
    r = dcu_tree.find_tag_with_attrs('td', {'data-title': "Rank"}).text
    w = dcu_tree.find_tag_with_attrs('td', {'data-title': "Wins"}).text
    l = dcu_tree.find_tag_with_attrs('td', {'data-title': "Losses"}).text
    t = dcu_tree.find_tag_with_attrs('td', {'data-title': "Ties"}).text

    return r, w, l, t


def get_next_match_info():

    infile = requests.get('http://www.dcunited.com/schedule').content
    tree = quickscraper.create_tree(infile)
    subtree = tree.find_tag_with_attrs('li', {'class': "last"})
    subtree = subtree.find_tag_with_attrs('article', {'class': "match_item featured clb-sec twoclub"})
    date = subtree.get_by_address('div[0]/div[0]/div[0]/@text')
    date = date.split(", ")[1]
    m, d = date.split(" ")
    m_name, m_number = getmonth(m)
    if "st" in d:
        d = d.split("s")[0]
    elif "nd" in d:
        d = d.split("n")[0]
    elif "rd" in d:
        d = d.split("r")[0]
    elif "th" in d:
        d = d.split("t")[0]

    t = subtree.get_by_address('div[0]/div[1]/div[0]/@text')
    t = t.split(' ')[0].strip()

    team1 = subtree.find_tag_with_attrs('div', {'class': "club_container"})
    team1 = team1.get_by_address('img/@element')
    team1_name = team1.attributes['title']
    if "United" in team1_name:
        team2 = subtree.find_tag_with_attrs('div', {'class': "club_container clubtwo"})
        team2 = team2.get_by_address('img/@element')
        opp = team2.attributes['title']
        vs_at = "vs"
    else:
        opp = team1_name
        vs_at = "at"

    return d, m_name, m_number, t, opp, vs_at


if __name__ == "__main__":

    with timeout(seconds=10):
        try:
            rank, wins, losses, ties = get_rank_record()
            day, month_name, month_number, time, opponent, vs = get_next_match_info()
            today = dt.today()
            print "DCU: (%s, %s-%s-%s):" % (rank, wins, losses, ties),
            if int(day) == today.day and month_number == today.month:
                print "Today, %s" % time,
            else:
                print "%s %s, %s" % (month_name, day, time),
            print "vs", opponent
        except TimeoutError:
            print ""
