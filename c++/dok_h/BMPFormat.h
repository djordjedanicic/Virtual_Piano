#pragma once
#include<iostream>
#include<fstream>
#include<map>

#include"MapaNota.h"
#include"Ruka.h"
using namespace std;

class BMP {
	map<string , pair<int, pair<int,int>>> noteRGB4;
	string nizTxtNota4[12] = {"C4","C#4","D4","D#4" ,"E4","F4","F#4" ,"G4","G#4" ,"A4","A#4" ,"B4" };
	int nizCrvene4[12] = { 255,255,255,127,0,0,0,0,0,127,255,255 };
	int nizZelene4[12] = { 0,127,255,255,255,255,255,127,0,0,0,0 };
	int nizPlave4[12] = { 0,0,0,0,0,127,255,255,255,255,255,127 };
	Razlomak tr4;
public:
	BMP():tr4(1,4) {}

	void ubaciRGB4() {
		for (int i = 0; i < 12; i++) {
			noteRGB4.insert(pair<string, pair<int, pair<int, int>>>(nizTxtNota4[i], pair<int, pair<int, int>>(nizCrvene4[i], pair<int, int>(nizZelene4[i], nizPlave4[i]))));
		}
	}
	string heksa(int n) {
		char hexaDeciNum[100];
		int i = 0;
		if (n == 0) { cout << '0'; }//vrednost ako je nula da ispise nulu
		while (n != 0) {
			int temp = 0;
			temp = n % 16;
			if (temp < 10) {
				hexaDeciNum[i] = temp + 48;
				i++;
			}
			else {
				hexaDeciNum[i] = temp + 55;
				i++;
			}
			n = n / 16;
		}
		string s;
		for (int j = i - 1; j >= 0; j--)
			s += hexaDeciNum[j];
		return s;
	}
	int odrediOktavu(string t) {
		int oktava;
		if (t[1] == '#') {
			oktava = t[2]-'0';
		}
		else {
			oktava = t[1] - '0';
		}
		return oktava;
	}

	int izracunajCrvenuBoju(int brO,string ton) {
		int rez;
		string k;
		for (auto i = noteRGB4.begin(); i != noteRGB4.end(); i++) {
			if (ton == odrediTon(i->first)) {
				k = i->first;
			}
		}
		map<string, pair<int, pair<int, int>>> ::iterator t = noteRGB4.find(k);
		if (brO == 2) {
			rez = t->second.first - ((t->second.first * 6) / 8);
		}
		else if (brO == 3) {
			rez = t->second.first - ((t->second.first * 3) / 8);
		}
		else if (brO == 5) {
			rez = t->second.first + ((255 - t->second.first) * 3 / 8);
		}
		else if (brO == 6) {
			rez = t->second.first - ((255 - t->second.first) * 6 / 8);
		}
		return rez;

	}
	int izracunajZelenuBoju(int brO, string ton) {
		int rez;
		string k;
		for (auto i = noteRGB4.begin(); i != noteRGB4.end(); i++) {
			if (ton == odrediTon(i->first)) {
				k = i->first;
			}
		}
		map<string, pair<int, pair<int, int>>> ::iterator t = noteRGB4.find(k);
		if (brO == 2) {
			rez = t->second.second.first - ((t->second.second.first * 6) / 8);
		}
		else if (brO == 3) {
			rez = t->second.second.first - ((t->second.second.first * 3) / 8);
		}
		else if (brO == 5) {
			rez = t->second.second.first + ((255 - t->second.second.first) * 3 / 8);
		}
		else if (brO == 6) {
			rez = t->second.second.first - ((255 - t->second.second.first) * 6 / 8);
		}
		return rez;
	
	}
	int izracunajPlavuBoju(int brO, string ton) {
		int rez;
		string k;
		for (auto i = noteRGB4.begin(); i != noteRGB4.end(); i++) {
			if (ton == odrediTon(i->first)) {
				k = i->first;
			}
		}
		map<string, pair<int, pair<int, int>>> ::iterator t = noteRGB4.find(k);
		if (brO == 2) {
			rez = t->second.second.second - ((t->second.second.second * 6) / 8);
		}
		else if (brO == 3) {
			rez = t->second.second.second - ((t->second.second.second * 3) / 8);
		}
		else if (brO == 5) {
			rez = t->second.second.second + ((255 - t->second.second.second) * 3 / 8);
		}
		else if (brO == 6) {
			rez = t->second.second.second - ((255 - t->second.second.second) * 6 / 8);
		}
		return rez;
	
	}
	string odrediTon(string s) {
		string novi;
		if (s[1] == '#') {
			novi += s[0];
			novi += s[1];
		}
		else {
			novi += s[0];
		}
		return novi;
	}
	void napraviBMP(Ruka &leva, Ruka &desna, MapaNota &mapa) {
		cout << "sirina:";
		int sirina;
		cin >> sirina;
		int visina;
		cout << "visina:";
		cin >> visina;
		ofstream dat("slika.txt");
		for (int i = 0; i < desna.dohvBrTaktova(); i++) {
			for (int j = 0; j < desna.dohvTajTakt(i).dohvBrSimbola(); j++) {
				auto simb = desna.dohvTajTakt(i).dohvTajSimbol(j);
				if (simb->tip() == 0) {
					if (trajanje1_4(simb->dohvTraj())) {
						cout<<heksa(255);
						cout<<heksa(255);
						cout<<heksa(255);
					}
				}
				else if (simb->tip() == 1) {
					string txt = mapa.dohvTxtNota(simb->dohvZnak());
					int brO = odrediOktavu(txt);
					string ton = odrediTon(txt);
					if (brO != 4) {
						cout<<heksa(izracunajCrvenuBoju(brO, ton));
						cout<<heksa(izracunajZelenuBoju(brO, ton));
						cout<<heksa(izracunajPlavuBoju(brO, ton));
					}
					else {
						map<string, pair<int, pair<int, int>>> ::iterator t = noteRGB4.find(txt);
						cout<<heksa(t->second.first);
						cout<<heksa(t->second.second.first);
						cout<<heksa(t->second.second.second);
					}

				}
				else if (simb->tip() == 2) {

				}
			}
		}
		for (int i = 0; i < leva.dohvBrTaktova(); i++) {
			for (int j = 0; j < leva.dohvTajTakt(i).dohvBrSimbola(); j++) {
				auto simb = leva.dohvTajTakt(i).dohvTajSimbol(j);
				if (simb->tip() == 0) {
					if (trajanje1_4(simb->dohvTraj())) {
						cout << heksa(255);
						cout << heksa(255);
						cout << heksa(255);
					}
				}
				else if (simb->tip() == 1) {
					string txt = mapa.dohvTxtNota(simb->dohvZnak());
					int brO = odrediOktavu(txt);
					string ton = odrediTon(txt);
					if (brO != 4) {
						cout << heksa(izracunajCrvenuBoju(brO, ton));
						cout << heksa(izracunajZelenuBoju(brO, ton));
						cout << heksa(izracunajPlavuBoju(brO, ton));
					}
					else {
						map<string, pair<int, pair<int, int>>> ::iterator t = noteRGB4.find(txt);
						cout << heksa(t->second.first);
						cout << heksa(t->second.second.first);
						cout << heksa(t->second.second.second);
					}

				}
				else if (simb->tip() == 2) {

				}
			}
		}

	}
	bool trajanje1_4(Razlomak trr) {
		if (trr == tr4)
			return true;
		return false;
	}
};

