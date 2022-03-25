#pragma once
#include<iostream>
#include"Simbol.h"
#include"Nota.h"
#include"MapaNota.h"
class Akord : public Simbol {
	vector<Nota> nizNota;
	int brNota;
	bool podeljen;
	int p;
	int m;
public:
	Akord() : Simbol(Razlomak(1,4), '?'),brNota(0) ,p(0),m(0),podeljen(false){}

	char dohvZnak()const override { return karakter; }

	Razlomak dohvTraj()const override { return trajanje; }

	void podeliTrajanje() override {
		trajanje = Razlomak(1, 8);
		podeljen = true;
		for (auto i = nizNota.begin(); i != nizNota.end(); i++) {
			i->podeliTrajanje();
		}
	}

	void dodajNotu(Nota &n) {
		nizNota.push_back(n);
		brNota++;
	}

	int dohvBrNota()const override { return brNota; }

	char dohvZnakNote(int br) override{ return nizNota[br].dohvZnak(); }

	Akord* kopija()const& override { return new Akord(*this); }

	int tip() const override {	return 2; }

	bool da_li_je_podeljen() override { return podeljen; }

	void promenaOktIVIs(char okt, char visina, MapaNota &mapa) override { m = 1; }

	void radiSaPovisicom(MapaNota &mapa)override { int k = 1; }
	
	void ispisi(MapaNota &mapa) const override {
		cout << '[';
		for (int i = 0; i < dohvBrNota(); i++)
		{
			string txt = mapa.dohvTxtNota(nizNota[i].dohvZnak());
			if (dohvTraj() == Razlomak(1, 8)) {
				txt[0] += '0';
			}
			cout << txt;
		}
		cout << ']';
	}
};

