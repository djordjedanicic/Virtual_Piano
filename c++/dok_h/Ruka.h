#pragma once
#include<iostream>

#include"Simbol.h"
#include"Takt.h"
using namespace std;

class Ruka {
	vector<Takt> nizTakt;
	Razlomak trajTakta;
	int brTaktova;
public:
	Ruka(Razlomak trTak);

	void dodajSimbol(Simbol &simb);

	Razlomak dohvTrTakta() { return trajTakta; }

	void promeniTakt(Razlomak noviTakt) {
		brTaktova = 0;
		trajTakta = noviTakt;
		nizTakt.clear();
		nizTakt.push_back(noviTakt);
	}

	int dohvBrTaktova()const { return brTaktova; }

	Takt dohvTajTakt(int br) { return nizTakt[br]; }

	void ispisi(MapaNota &mapa);

	void ispisiTajTakt(int br,MapaNota &mapa) {
		cout << '|';
		nizTakt[br].ispisi(mapa);
		cout << '|';
	}

	void promeniOktIVis(char okt, char visina, int rbt, int rbn, MapaNota &mapa) {
		if (nizTakt[rbt].dohvTajSimbol(rbn)->tip() == 1) {
			nizTakt[rbt].dohvTajSimbol(rbn)->promenaOktIVIs(okt, visina,mapa);
		}
	}

	void radiSaPovisicom(int rbt, int rbn, MapaNota &mapa) {
		if (nizTakt[rbt].dohvTajSimbol(rbn)->tip() == 1) {
			nizTakt[rbt].dohvTajSimbol(rbn)->radiSaPovisicom( mapa);
		}
	}

	void ispisiNotu(int rbt,int rbn, MapaNota &mapa) {
		if(nizTakt[rbt].dohvTajSimbol(rbn)->tip()!=0)
			nizTakt[rbt].dohvTajSimbol(rbn)->ispisi(mapa);
		//else {
			//cout << "nije nota";
		//}*/
	}
};

