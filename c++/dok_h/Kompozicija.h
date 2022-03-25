#pragma once
#include<iostream>
#include<string>
#include<fstream>

#include "Razlomak.h"
#include "MapaNota.h"
#include"Ruka.h"
#include"Pauza.h"
#include"MIDIFormat.h"
#include"MusicXMLFormat.h"
#include"Nota.h"
#include"Akord.h"
#include"BMPFormat.h"
using namespace std;

class Kompozicija {
	Razlomak trajTakta;
	Ruka leva;
	Ruka desna;
	Razlomak tr4;
	Razlomak tr8;
	vector<char> deo;
	int signalTakt;
public:
	Kompozicija(Razlomak trTak) : trajTakta(trTak), leva(trTak), desna(trTak),
		tr4(1,4),tr8(1,8),signalTakt(0) {}

	void ucitajKompoziciju(string s, MapaNota &m);

	bool levaRuka(char &ch, MapaNota &m); //ispituje karakter kojoj oktavi pripada i koja ruka treba da je svira leva-true, desna-false

	void naprMidi(MapaNota &mapa);

	void naprXML(MapaNota &mapa);

	void naprBMP(MapaNota &mapa);

	void ispisi(MapaNota &mapa);

	void ispisiTajTakt(int rb, MapaNota &mapa);

	void ispisiNotu(int rbt, int rbn, MapaNota &mapa);

	void promeniTakt(Razlomak noviTakt, string s, MapaNota &mapa);

	void radiSaPovisicom(int rbt, int rbn, MapaNota &mapa);

	void promenaOktIVisine(char okt, char visina, int rbt, int rbn, MapaNota &mapa);
	
};
