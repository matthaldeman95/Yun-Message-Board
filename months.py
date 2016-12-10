
def getmonth(m):

    if m == "January" or "Jan" in m:
        month = "Jan"
        month_number= 1
    elif m == "February" or "Feb" in m:
        month = "Feb"
        month_number= 2
    elif m == "March" or "Mar" in m:
        month = "Mar"
        month_number= 3
    elif m == "April" or "Apr" in m:
        month = "Apr"
        month_number= 4
    elif m == "May" or "May" in m:
        month = "May"
        month_number= 5
    elif m == "June" or "Jun" in m:
        month = "Jun"
        month_number= 6
    elif m == "July" or "Jul" in m:
        month = "Jul"
        month_number= 7
    elif m == "August" or "Aug" in m:
        month = "Aug"
        month_number= 8
    elif m == "September" or "Sep" in m:
        month = "Sep"
        month_number= 9
    elif m == "October" or "Oct" in m:
        month = "Oct"
        month_number= 10
    elif m == "November" or "Nov" in m:
        month = "Nov"
        month_number= 11
    elif m == "December" or "Dec" in m:
        month = "Dec"
        month_number= 12

    return month, month_number
