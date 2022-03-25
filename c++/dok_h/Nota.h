#pragma once
#include<iostream>
#include"Simbol.h"
class Nota : public Simbol {
	bool podeljen;
	int p;
public:
	Nota(Razlomak rr, char ch) :Simbol(rr, ch),p(0),podeljen(false) {}

	char dohvZnak()const override { return karakter; }

	Razlomak dohvTraj()const override { return trajanje; }

	void podeliTrajanje() override { 
		trajanje = Razlomak(1, 8); 
		podeljen = true;
	}

	Nota* kopija()const& override { return new Nota(*this); }
	
	int tip() const override { return 1; }
	
	bool da_li_je_podeljen() override {
		p = 1;
		return podeljen;
	}

	void promenaOktIVIs(char okt, char visina,MapaNota &mapa) override { 
		string txt = mapa.dohvTxtNota(dohvZnak());
		txt[0] = visina;
		if (txt[1] == '#') {
			txt[2] = okt;
		}
		else {
			txt[1] = okt;
		}
		char ch = mapa.dohvChar(txt);
		karakter = ch;
	}

	void radiSaPovisicom(MapaNota &mapa)override {
		string txt = mapa.dohvTxtNota(dohvZnak());
		string novi;
		string taraba = "#";
		if (txt[0] != 'E' && txt[0] != 'B') {
			if (txt[1] == '#') {
				novi = txt[0];
				novi += txt[2];
			}
			else {
				novi += txt[0];
				novi += taraba;
				novi += txt[1];

			}
			karakter = mapa.dohvChar(novi);
		}
		else {
			cout << "Ta nota ne moze da se povisi" << endl;
		}
	}

	int dohvBrNota()const override { return 1; }

	char dohvZnakNote(int br) override { return 'n'; }

	void ispisi(MapaNota &mapa) const override {
		string txt = mapa.dohvTxtNota(dohvZnak());
		if (dohvTraj() == Razlomak(1, 8)) {
			txt[0] = txt[0] +'0';
		}
		cout << txt ;
	}

};

