"""
输入任意一天，返回当天是星期几，已知2018年4月3日是星期二
原理:计算当天和2018年4月3日之间有多少天的差距，用7对天数求模，余数套为下面的列表的index
"""

import time
#标准点 2018年4月3日是星期二
WEEK = ["星期二","星期三","星期四","星期五","星期六","星期天","星期一"]

#校验当年是不是闰年
def isLeapYear(year):
    if (year%4==0 and year%100==0) or year%400==0:       
        return True
    else:
        return False



def calculate(year,month,day):

    standard = 31*2+28+3

    if type(year)!=int or type(month)!=int or type(day)!=int:
        return "日期必须为整数"
    
    if year<0:
        return "日期不合法"
    if month<1 or month>12:
        return "日期不合法"
    if day<1 or day>31:
        return "日期不合法"

    ##看日期是不是合适
    if day>28 and  month==2:
        if not isLeapYear(year):
            return "日期不合法"


    if month in [2,4,6,9,11] and day>30:
        return "日期不合法"
    

    subdays = 0
    if year>2018:
        for i in range(2019,year):
            if isLeapYear(i):
                subdays+=366
            else: 
                subdays+=365

    elif year<2018:
        for i in range(year,2017):
            if isLeapYear(i):
                subdays+=366
            else:
                subdays+=365
    days = 0

    for i in range(1,month):

        if i<=7 :
            if i%2==1:
                days+=31
            else:
                if i!=2:
                    days+=30
                else:
                    if isLeapYear(year):               
                        days+=29
                    else:
                        days +=28
        else:
            if i%2==0:
                days+=31
            else:
                days+=30

    days+=day#月份换算过来的天数加上本月天数

    if year>2018:
        target = subdays+days+365-standard     
        mo = target%7
        return WEEK[mo]

    elif year<2018:
        if isLeapYear(year):
            target = subdays+standard+366-days
        else:
            target = subdays+standard+365-days
        
        mo =  target%7
        
        return WEEK[0-mo]
    else:
        target = days-standard
        if target>=0:
            mo = target%7
            return WEEK[mo]
        else:
            mo = abs(target)%7
            return WEEK[0-mo]
                        
if __name__=="__main__":
    print(calculate(2018,2,28))
