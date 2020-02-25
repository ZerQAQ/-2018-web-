#include<bits/stdc++.h>
using namespace std;

typedef string Date;

int parseInt(string s){
	int len = s.length();
	int ret = 0;
	for(int i = 0; i < len; i++){
		ret *= 10;
		ret += s[i] - '0';
	}
	return ret;
}

string toString(int i, int l){
	l -= to_string(i).length();
	string ret = "";
	for(int k = 0; k < l; k++) ret += "0";
	ret += to_string(i);
	return ret;
}

struct MyDate{
	const int n_month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int s_month_days[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int Year, Month, Day, Hour, Minus, Second;

	MyDate(Date v){
		Year = parseInt(v.substr(0, 4));
		Month = parseInt(v.substr(5, 2));
		Day = parseInt(v.substr(8, 2));
		Hour = parseInt(v.substr(11, 2));
		Minus = parseInt(v.substr(14, 2));
		Second = parseInt(v.substr(17, 2));
	}
	void add_fix(){
		if(Second >= 60){
			Minus += Second / 60;
			Second %= 60;
		}
		if(Minus >= 60){
			Hour += Minus / 60;
			Minus %= 60;
		}
		if(Hour >= 24){
			Day += Hour / 24;
			Hour %= 24;
		}
		while(Month <= 12 && Day >= (Year % 4 == 0? s_month_days[Month]: n_month_days[Month])){
			Day -= Year % 4 == 0? s_month_days[Month]: n_month_days[Month];
			Month++;
			if(Month == 13){
				Year++;
				Month = 1;
			}
		}
		if(Month > 12){
			Year += (Month - 1) / 12;
			Month = (Month - 1) % 12 + 1;
		}
	}
	void sub_fix(){
		if(Second < 0){
			Minus += (Second + 1) / 60 - 1;
			Second %= 60;
			if(Second < 0) Second += 60;
		}
		if(Minus < 0){
			Hour += (Minus + 1) / 60 - 1;
			Minus %= 60;
			if(Minus < 0) Minus += 60;
		}
		if(Hour < 0){
			Day += (Hour + 1) / 24 - 1;
			Hour %= 24;
			if(Hour < 0) Hour += 24;
		}
		if(Day <= 0){
			while(Day <= 0){
				int lm = Month == 1? 12: Month - 1;
				Day += Year % 4 == 0? s_month_days[lm]: n_month_days[lm];
				Month--;
				if(!Month){
					Year--;
					Month = 12;
				}
			}
		}
		if(Month <= 0){
			Year += (Month + 1) / 12 - 1;
			Month -= ((Month + 1) / 12 - 1) * 12;
			if(Month <= 0) Month += 12;
		}
	}
	MyDate nextYear(){
		MyDate ret = *this;
		ret.Year++;
		ret.add_fix();
		return ret;
	}
	MyDate lastYear(){
		MyDate ret = *this;
		ret.Year--;
		ret.sub_fix();
		return ret;
	}
	MyDate nextMonth(){
		MyDate ret = *this;
		ret.Month++;
		ret.add_fix();
		return ret;
	}
	MyDate lastMonth(){
		MyDate ret = *this;
		ret.Month--;
		ret.sub_fix();
		return ret;
	}
	MyDate nextDay(){
		MyDate ret = *this;
		ret.Day++;
		ret.add_fix();
		return ret;
	}
	MyDate lastDay(){
		MyDate ret = *this;
		ret.Day--;
		ret.sub_fix();
		return ret;
	}
	MyDate nextMinus(){
		MyDate ret = *this;
		ret.Minus++;
		ret.add_fix();
		return ret;
	}
	MyDate lastMinus(){
		MyDate ret = *this;
		ret.Minus--;
		ret.sub_fix();
		return ret;
	}
	MyDate nextSecond(){
		MyDate ret = *this;
		ret.Second++;
		ret.add_fix();
		return ret;
	}
	MyDate lastSecond(){
		MyDate ret = *this;
		ret.Second--;
		ret.sub_fix();
		return ret;
	}
	MyDate yearsLater(int v){
		MyDate ret = *this;
		ret.Year += v;
		ret.add_fix();
		return ret;
	}
	MyDate monthsLater(int v){
		MyDate ret = *this;
		ret.Month += v;
		ret.add_fix();
		return ret;
	}
	MyDate daysLater(int v){
		MyDate ret = *this;
		ret.Day += v;
		ret.add_fix();
		return ret;
	}
	MyDate hoursLater(int v){
		MyDate ret = *this;
		ret.Hour += v;
		ret.add_fix();
		return ret;
	}
	MyDate minusLater(int v){
		MyDate ret = *this;
		ret.Minus += v;
		ret.add_fix();
		return ret;
	}
	MyDate secondsLater(int v){
		MyDate ret = *this;
		ret.Second += v;
		ret.add_fix();
		return ret;
	}
	MyDate yearsAgo(int v){
		MyDate ret = *this;
		ret.Year -= v;
		ret.sub_fix();
		return ret;
	}
	MyDate monthsAgo(int v){
		MyDate ret = *this;
		ret.Month -= v;
		ret.sub_fix();
		return ret;
	}
	MyDate daysAgo(int v){
		MyDate ret = *this;
		ret.Day -= v;
		ret.sub_fix();
		return ret;
	}
	MyDate hoursAgo(int v){
		MyDate ret = *this;
		ret.Hour -= v;
		ret.sub_fix();
		return ret;
	}
	MyDate minusAgo(int v){
		MyDate ret = *this;
		ret.Minus -= v;
		ret.sub_fix();
		return ret;
	}
	MyDate secondsAgo(int v){
		MyDate ret = *this;
		ret.Second -= v;
		ret.sub_fix();
		return ret;
	}
	Date toNaiveDate(){
		return to_string(Year) + "/" + toString(Month, 2) + "/" + toString(Day, 2) + " " + toString(Hour, 2) 
		+ ":" + toString(Minus, 2) + ":" + toString(Second, 2);
	}
};

int main(){
	Date d("2020/02/05 15:52:00");
	MyDate md(d);
	cout << md.toNaiveDate() << endl;
	cout << md.nextYear().lastMonth().secondsLater(130).toNaiveDate() << endl;
	cout << md.daysLater(365).secondsAgo(2).toNaiveDate() <<endl;
	cout << md.monthsLater(366).daysAgo(25582).minusLater(24656167).secondsAgo(367514).toNaiveDate() << endl;
	return 0;X
}
