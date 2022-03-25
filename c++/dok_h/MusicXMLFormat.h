#include<iostream>
#include<string>
#include<fstream>

#include"Ruka.h"
#include"MapaNota.h"

using namespace std;

class MusicXML {
	Razlomak tr4;
	Razlomak tr8;
	int signal;

public:
	MusicXML():tr4(1,4),tr8(1,8),signal(0){}

	void napraviXML(Ruka &leva, Ruka &desna, MapaNota &mapa);

	char odrediTrajanje(Razlomak tr);

};


