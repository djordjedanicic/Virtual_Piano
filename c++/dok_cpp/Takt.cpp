#include"Takt.h"

bool Takt :: dodajSimbol(Razlomak trajSimb, const Simbol &simb) {
	if ((kap + trajSimb) > trajTakta) {
		return false;
	}
	else if ((kap + trajSimb) == trajTakta) {
		kap = kap + trajSimb;
		nizSimb.push_back(simb.kopija());
		brSimbola++;
		Pun = true;
		return true;
	}
	else {
		kap = kap + trajSimb;
		nizSimb.push_back(simb.kopija());
		brSimbola++;
		return true;
	}

}

Simbol* Takt :: dohvTajSimbol(int br) {
	if (br < 0)
		return nizSimb[0];
	if (br < brSimbola)
		return nizSimb[br];
	else return nizSimb[brSimbola - 1];

}

void Takt :: ispisi(MapaNota &mapa) {
	for (int i = 0; i < brSimbola ; i++) {
		nizSimb[i]->ispisi(mapa);
	}
}