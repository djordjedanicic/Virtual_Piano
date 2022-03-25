#pragma once
#include<iostream>
#include"Simbol.h"
class Pauza : public Simbol {
	bool podeljen;
	int p;
public:
	Pauza(Razlomak rr, char ch) :Simbol(rr, ch),podeljen(false),p(0) {}

	char dohvZnak()const override { return karakter; }

	int tip() const override { return 0; }

	Razlomak dohvTraj()const override { return trajanje; }

	void podeliTrajanje() override { 
		trajanje = Razlomak(1, 8); 
		podeljen = true;
	}

	Pauza* kopija()const& override { return new Pauza(*this); }
	
	void promenaOktIVIs(char okt, char visina,MapaNota &mapa) override { int k = 1; }

	int dohvBrNota()const override { return 0; }

	char dohvZnakNote(int br) override { return ' '; }

	bool da_li_je_podeljen() override { p = 1;
		return podeljen;
	}

	void radiSaPovisicom(MapaNota &mapa)override { int k = 1; }

	void ispisi(MapaNota &mapa) const override {
		if (dohvTraj() == Razlomak(1, 8)) {
			cout << "^";
		}
		else{ cout << " "; }
	}
};

