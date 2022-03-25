#pragma once
#include<iostream>

#include"Simbol.h"
#include"MapaNota.h"
using namespace std;

class Takt {
	vector<Simbol*> nizSimb;
	Razlomak trajTakta;
	Razlomak kap;
	int brSimbola;
	bool Pun;
public:
	Takt(Razlomak tr) :trajTakta(tr), kap(0, 1), Pun(false),brSimbola(0) {}

	bool dodajSimbol(Razlomak trajSimb, const Simbol &simb);

	bool getPun()const { return Pun; }

	int dohvBrSimbola()const { return brSimbola; }

	Simbol* dohvTajSimbol(int br);

	void ispisi(MapaNota &mapa);
	
};
