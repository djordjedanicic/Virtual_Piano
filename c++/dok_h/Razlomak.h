#pragma once
#include<iostream>

class Razlomak {
	int x;
	int y;
public:
	Razlomak(int xx, int yy) :x(xx), y(yy) {}
	friend Razlomak operator+(const Razlomak &r1, const Razlomak &r2) {
		return Razlomak(r1.x*r2.y + r2.x*r1.y, r1.y*r2.y);
	}
	friend bool operator>(const Razlomak &r1, const Razlomak &r2) {
		return r1.x*r2.y > r2.x*r1.y;
	}
	friend bool operator==(const Razlomak &r1, const Razlomak &r2) {
		return r1.x*r2.y == r2.x*r1.y;
	}
	int getBr() { return x; }
	int getIm() { return y; }
};
