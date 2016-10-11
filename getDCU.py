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
    subtree = tree.find_tag_with_attrs('table', {'class': "standings_table"})[0]
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

    infile = requests.get('http://www.espnfc.us/club/dc-united/193/fixtures').content
    tree = quickscraper.create_tree(infile)
    subtree = tree.find_tag_with_attrs('div', {'class': "next-match"})

    date = subtree.get_by_address('h3[0]/span[0]/@text')
    date = (date.split('-')[1]).split(',')[0].strip()
    m, d = date.split(' ')

    team1 = subtree.get_by_address('div[0]/div[0]/div[0]/div[0]/div[0]/span[0]//img[0]/@text')
    team2 = subtree.get_by_address('div[0]/div[0]/div[0]/div[0]/div[1]/span[0]//img[0]/@text')
    if "United" in team1:
        opp = team2
    else:
        opp = team1

    t = subtree.find_tag_with_attrs('span', {'class': "time gmt-time"}).text
    hr, t = t.split(':')
    hr = str(int(hr)-4)
    t = hr+':'+t
    t = t.split(' ')[0]+t.split(' ')[1]

    return d, m, t, opp


if __name__ == "__main__":

    with timeout(seconds=20):
        try:
            rank, wins, losses, ties = get_rank_record()
            day, month, time, opponent= get_next_match_info()
            today = dt.today()
            print "DCU: (%s, %s-%s-%s):" % (rank, wins, losses, ties),
            if int(day) == today.day:
                print "Today, %s" % time,
            else:
                print "%s %s, %s" % (month, day, time),
            print "vs", opponent
        except TimeoutError:
            print ""
