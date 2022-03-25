#include"Kompozicija.h"

void Kompozicija :: ucitajKompoziciju(string s, MapaNota &m) {
	if (signalTakt == 1) {
		signalTakt = 0;
		desna.promeniTakt(trajTakta);
		leva.promeniTakt(trajTakta);
	}
	ifstream dat;
	dat.open(s);
	if (dat.is_open()) {
		char ch;
		dat.get(ch);
		while (!dat.eof()) {
			while (ch != ' ' && ch != '|' && ch != '[' && !dat.eof()) {
				if (ch != '\n') { //ignorise prelazak u novi red
					deo.push_back(ch);
				}
				dat.get(ch);
			}
			if (deo.size() > 0) {
				Pauza pauza(tr4, '|');
				for (auto i = deo.begin(); i != deo.end(); i++) {
					Nota nota(tr4, *i);
					if (levaRuka(*i, m)) {
						leva.dodajSimbol(nota);
						desna.dodajSimbol(pauza);
					}
					else {
						desna.dodajSimbol(nota);
						leva.dodajSimbol(pauza);
					}
				}
			}
			deo.clear();
			if (ch == ' ') {
				Pauza pauza(tr8, ch);
				leva.dodajSimbol(pauza);
				desna.dodajSimbol(pauza);
			}
			else if (ch == '|') {
				Pauza pauza = Pauza(tr4, ch);
				leva.dodajSimbol(pauza);
				desna.dodajSimbol(pauza);
			}
			else if (ch == '[') {
				dat.get(ch);
				while (ch != ' ' && ch != ']') {
					if (ch != '\n') { //ignorise prelazak u novi red
						deo.push_back(ch);
					}
					dat.get(ch);
				}
				if (ch == ' ') {
					while (ch != ']') {
						if (ch != '\n') {//ignorise prelazak u novi red
							deo.push_back(ch);
						}
						dat.get(ch);
					}
					for (auto i = deo.begin(); i != deo.end(); i++) {
						if (*i != ' ') {
							Nota nota(tr8, *i);
							Pauza pauza(tr8, ' ');
							if (levaRuka(*i, m)) {
								leva.dodajSimbol(nota);
								desna.dodajSimbol(pauza);
							}
							else {
								desna.dodajSimbol(nota);
								leva.dodajSimbol(pauza);
							}
						}
					}
				}
				else {
					int lp = 0;
					int dp = 0;
					Akord akordL;
					Akord akordD;
					for (auto i = deo.begin(); i != deo.end(); i++) {
						if (levaRuka(*i, m)) {
							Nota nleva(tr4, *i);
							akordL.dodajNotu(nleva);
							lp = 1;
						}
						else {
							Nota ndesna(tr4, *i);
							akordD.dodajNotu(ndesna);
							dp = 1;
						}
					}
					Pauza pauza(tr4, '|');
					if (lp == 1 && dp == 0) {
						leva.dodajSimbol(akordL);
						desna.dodajSimbol(pauza);
					}
					else if (lp == 0 && dp == 1) {
						desna.dodajSimbol(akordD);
						leva.dodajSimbol(pauza);
					}
					else if (lp == 1 && dp == 1) {
						leva.dodajSimbol(akordL);
						desna.dodajSimbol(akordD);
					}
				}
			}
			dat.get(ch);
			deo.clear();
		}
		dat.close();
	}
	else { cout << "Niste uneli ispravnu putanju do datoteke, nije se otvorila" << endl; }
}

bool Kompozicija::levaRuka(char &ch, MapaNota &m) //ispituje karakter kojoj oktavi pripada i koja ruka treba da je svira leva-true, desna-false
{
	string nota;
	if (ch != ' ' && ch != '|') {
		nota = m.dohvTxtNota(ch);
		int oktava;
		if (nota[1] == '#') {
			oktava = nota[2] - '0';
		}
		else
		{
			oktava = nota[1] - '0';
		}
		if (oktava > 3) {
			return false;
		}
		else {
			return true;
		}
	}
}
void Kompozicija :: naprMidi(MapaNota &mapa) {
	Midi m;
	m.napraviMidi(leva, desna, mapa);
}

void Kompozicija :: naprXML(MapaNota &mapa) {
	MusicXML xml;
	xml.napraviXML(leva, desna, mapa);
}

void Kompozicija :: naprBMP(MapaNota &mapa) {
	BMP bmp;
	bmp.ubaciRGB4();
	bmp.napraviBMP(leva, desna, mapa);
}

void Kompozicija :: ispisi(MapaNota &mapa) {
	desna.ispisi(mapa);
	cout << endl;
	leva.ispisi(mapa);
	cout << endl;
}

void Kompozicija :: ispisiTajTakt(int rb, MapaNota &mapa) {
	desna.ispisiTajTakt(rb, mapa);
	cout << endl;
	leva.ispisiTajTakt(rb, mapa);
	cout << endl;
}

void Kompozicija :: ispisiNotu(int rbt, int rbn, MapaNota &mapa) {
	desna.ispisiNotu(rbt, rbn, mapa);
	cout << endl;
	leva.ispisiNotu(rbt, rbn, mapa);
	cout << endl;
}

void Kompozicija :: promeniTakt(Razlomak noviTakt, string s, MapaNota &mapa) {
	signalTakt = 1;
	trajTakta = noviTakt;
	ucitajKompoziciju(s, mapa);
}

void Kompozicija :: radiSaPovisicom(int rbt, int rbn, MapaNota &mapa) {
	desna.radiSaPovisicom(rbt, rbn, mapa);
	leva.radiSaPovisicom(rbt, rbn, mapa);
}

void Kompozicija :: promenaOktIVisine(char okt, char visina, int rbt, int rbn, MapaNota &mapa) {
	desna.promeniOktIVis(okt, visina, rbt, rbn, mapa);
	leva.promeniOktIVis(okt, visina, rbt, rbn, mapa);
}
