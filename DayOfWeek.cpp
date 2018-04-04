// DayOfWeek.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include<stdio.h>
#include <string>
#include <iostream>
#include <locale>
using namespace std;

//以2018年4月3日为星期二当作基准点
string WEEK[7] = { "Tuesday","Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday" };

//判断是不是闰年
BOOL isLeapYear(int year)
{
	if (year % 4 == 0 && year % 100 != 0)
		return TRUE;
	if (year % 400 == 0)
		return TRUE;

	return FALSE;
}

string toTheWeek(int year, int month, int day)
{
	if (year < 0)
		return "not support BC";
	if (month < 1 || month>12)
		return "Month illegal";
	if (day < 1 || day>31)
		return "Day illegal";
	if (day > 28 && month == 2)
	{
		if (!isLeapYear(year))
			return "not lear year，maxmium 29 days int Febrary";
	}
	if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return "Maxmium 30 days this month";
	}

	int standard = 31 * 2 + 28 + 3;
	//开始计算天数距离标准天的差距
	int subdays = 0;
	if (year > 2018)
	{
		for (int i = 2019; i < year; i++)
		{
			if (isLeapYear(i))
				subdays += 366;
			else
				subdays += 365;
		}
	}
	else if (year < 2018)
	{
		for (int i = year; i < 2017; i++)
		{
			if (isLeapYear(i))
				subdays += 366;
			else
				subdays += 365;
		}
	}

	int days = 0;
	for (int i = 1; i < month; i++)
	{
		if (i <= 7)
		{
			if (i % 2 == 1)
				days += 31;
			else
			{
				if (i != 2)
					days += 30;
				else
				{
					if (isLeapYear(year))
						days += 29;
					else
						days += 28;
				}
			}
		}
		else
		{
			if (i % 2 == 0)
				days += 31;
			else
				days += 30;
		
		}
		
	}


	days += day;
	int index = 0, target = 0;
	if (year > 2018)
	{
		target = subdays + days + 365 - standard;
		index = target % 7;
		return WEEK[index];
	}
	else if (year < 2018)
	{
		if (isLeapYear(year))
			target = subdays + standard + 366 - days;
		else
			target = subdays + standard + 365 - days;
		index = target % 7;
		return WEEK[0 - index];
	
	}
	else
	{
		target = days - standard;
		if (target >= 0)
		{
			index = target % 7;
			return WEEK[index];
		}
		else
		{
			index = abs(target) % 7;
			return WEEK[0 - index];
		}
	}
	return "Unexpected Exception";
}


int main()
{
	wcout.imbue(locale("chs"));
	int year = 2019;
	int month = 11;
	int day = 3;
	cout << toTheWeek(year, month, day) << endl;

	system("pause");
    return 0;
}

