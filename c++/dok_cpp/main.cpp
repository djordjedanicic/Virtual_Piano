#include<iostream>
#include<string>

#include"MapaNota.h"
#include"Razlomak.h"
#include"Kompozicija.h"
using namespace std;

int main() {
	MapaNota mapa;
	string putanjaMapiranja;
	cout << "Putanja do fajla za mapiranje nota: ";
	cin >> putanjaMapiranja;
	mapa.mapirajNote(putanjaMapiranja);
	string putanjaKompozicije;
	cout << "Putanja do fajla gde se nalazi kompozicija: ";
	cin >> putanjaKompozicije;
	cout << "Duzina takta (br/im): ";
	int x; int y;
	cin >> x >> y;
	Razlomak trTakta(x, y);
	Kompozicija komp(trTakta);
	komp.ucitajKompoziciju(putanjaKompozicije, mapa);
	while (true) {
		cout << "1.Ispisivanje podataka o kompoziciji" << endl;
		cout << "2.Iteriranje kroz kompoziciju" << endl;
		cout << "3.Izmena takta kompozicije" << endl;
		cout << "4.Pomeranje kompozicije" << endl;
		cout << "5.Izaberi format" << endl;
		cout << "0.Kraj" << endl;
		cout << "broj: ";
		int broj;
		cin >> broj;
		switch (broj)
		{
		case 1:
		{
			komp.ispisi(mapa);
			break;
		}

		case 2:
		{
			cout << "Redni broj takta: ";
			int rbt;
			cin >> rbt;
			int broj2 = -1;
			komp.ispisiTajTakt(rbt, mapa);
			while (broj2 != 0) {
				cout << "1.Prelazak na sledeci takt" << endl;
				cout << "2.Povratak na prethodni takt" << endl;
				cout << "3.Zapocni iteriranje kroz note" << endl;
				cout << "0.Izadji" << endl;
				cout << "broj: ";
				cin >> broj2;
				switch (broj2)
				{
				case 1:
				{
					rbt++;
					komp.ispisiTajTakt(rbt, mapa);
					break;
				}

				case 2:
				{
					rbt--;
					komp.ispisiTajTakt(rbt, mapa);
					break;
				}
				case 3:
				{
					cout << "Redni broj note: ";
					int rbn;
					cin >> rbn;
					komp.ispisiNotu(rbt, rbn, mapa);
					int broj23 = -1;
					while (broj23 != 0) {
						cout << "1.Prelazak na sledecu notu" << endl;
						cout << "2.Povratak na prethodnu notu" << endl;
						cout << "3.Menjanje oktave i visine note" << endl;
						cout << "4.Dodavanje ili uklanjanje povisica" << endl;
						cout << "0.Izadji" << endl;
						cout << "broj: ";
						cin >> broj23;
						switch (broj23)
						{
						case 1:
						{
							rbn++;
							komp.ispisiNotu(rbt, rbn, mapa);
							break;
						}

						case 2:
						{
							rbn--;
							komp.ispisiNotu(rbt, rbn, mapa);
							break;
						}
						case 3:
						{
							cout << "Oktava: ";
							char okt;
							cin >> okt;
							cout << "Visina: ";
							char visina;
							cin >> visina;
							komp.promenaOktIVisine(okt, visina, rbt, rbn, mapa);
							break;
						}
						case 4:
						{
							komp.radiSaPovisicom(rbt, rbn, mapa);
							break;
						}
						}
					}
					break;
				}
			}
		}
			break;
		}

		case 3:
		{
			cout << "Takt: ";
			int x;
			int y;
			cin >> x;
			cin >> y;
			Razlomak takt(x, y);
			trTakta = takt;
			komp.promeniTakt(takt,putanjaKompozicije,mapa);
			break;
		}

		case 4:
		{
			break;
		}
		case 5:
		{
			cout << "1.MIDI format" << endl;
			cout << "2.MusicXML format" << endl;
			cout << "3.BMP format" << endl;
			cout << "broj: ";
			int broj5;
			cin >> broj5;
			switch (broj5)
			{
			case 1: 
			{
				komp.naprMidi(mapa);
				break;
			}
			case 2:
			{
				komp.naprXML(mapa);
				break;
			}
			case 3:
			{
				komp.naprBMP(mapa);
				break;
			}
			}
			break;
		}
		case 0:
		{
			exit(1);
			break;
		}
		}

	}
}