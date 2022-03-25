#include "MidiFile.h"
#include "Ruka.h"
#include "Akord.h"
#include "MapaNota.h"
#include <iostream>
using namespace std;
using namespace smf;

class Midi {
	Razlomak tr4;
	Razlomak tr8;
	int signal;
	int acc_p;
public:
	Midi():tr4(1,4),tr8(1,8),signal(0),acc_p(0){}

	int odrediTrajanje(Razlomak trr);
	
	void napraviMidi(Ruka &leva, Ruka &desna, MapaNota &mapa);

};


