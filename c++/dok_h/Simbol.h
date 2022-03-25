#pragma once
#include<iostream>
#include"Razlomak.h"
#include"MapaNota.h"

class Simbol {
protected:
	Razlomak trajanje;
	char karakter;
public:
	Simbol(Razlomak rr, char ch) :trajanje(rr), karakter(ch) {}
	virtual char dohvZnak()const = 0;
	virtual Razlomak dohvTraj()const = 0;
	virtual void podeliTrajanje() = 0;
	virtual Simbol* kopija()const& = 0;
	virtual void ispisi(MapaNota &mapa) const = 0;
	virtual int tip() const = 0;
	virtual int dohvBrNota() const = 0;
	virtual char dohvZnakNote(int br) = 0;
	virtual bool da_li_je_podeljen() = 0;
	virtual void radiSaPovisicom(MapaNota &mapa) = 0;
	virtual void promenaOktIVIs(char okt, char visina, MapaNota &mapa) = 0;
};


