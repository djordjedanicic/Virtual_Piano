#include"Ruka.h"

Ruka :: Ruka(Razlomak trTak) :trajTakta(trTak) { nizTakt.push_back(trTak); brTaktova++; }

void Ruka :: dodajSimbol(Simbol &simb) {
	if (nizTakt.back().getPun() == false) {
		if (!nizTakt.back().dodajSimbol(simb.dohvTraj(), simb)) {
			simb.podeliTrajanje();
			nizTakt.back().dodajSimbol(simb.dohvTraj(), simb);
			nizTakt.push_back(trajTakta);
			brTaktova++;
			nizTakt.back().dodajSimbol(simb.dohvTraj(), simb);
		}
	}
	else if (nizTakt.back().getPun() == true) {
		nizTakt.push_back(trajTakta);
		brTaktova++;
		if (!nizTakt.back().dodajSimbol(simb.dohvTraj(), simb)) {
			simb.podeliTrajanje();
			nizTakt.back().dodajSimbol(simb.dohvTraj(), simb);
			nizTakt.push_back(trajTakta);
			brTaktova++;
			nizTakt.back().dodajSimbol(simb.dohvTraj(), simb);
		}
	}
}

void Ruka :: ispisi(MapaNota &mapa) {
	for (int i = 0; i < brTaktova; i++) {
		nizTakt[i].ispisi(mapa);
		cout << "|";
	}
}