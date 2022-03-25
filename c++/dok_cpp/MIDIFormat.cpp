#include"MIDIFormat.h"

int Midi :: odrediTrajanje(Razlomak trr) {
	if (trr == tr4)
		return 2;
	return 1;
}

void Midi :: napraviMidi(Ruka &leva, Ruka &desna, MapaNota &mapa) {
	MidiFile outputfile;
	outputfile.absoluteTicks();
	vector<uchar> midievent;
	midievent.resize(3);
	int tpq = 48;
	outputfile.setTicksPerQuarterNote(tpq);
	outputfile.addTrack(1);
	int i = 0;
	int actiontime = 0;
	midievent[2] = 64;


	for (int i = 0; i < desna.dohvBrTaktova(); i++) {
		for (int j = 0; j < desna.dohvTajTakt(i).dohvBrSimbola(); j++) {
			auto simb = desna.dohvTajTakt(i).dohvTajSimbol(j);
			if (simb->tip() == 0) {
				actiontime += tpq / 2 * odrediTrajanje(simb->dohvTraj());
			}
			else if (simb->tip() == 1) {
				if (simb->da_li_je_podeljen() && signal == 0) {
					signal = 1;
					midievent[0] = 0x90;
					midievent[1] = mapa.dohvMidi(simb->dohvZnak());
					outputfile.addEvent(0, actiontime, midievent);
					actiontime += tpq / 2 * 2;
					midievent[0] = 0x80;
					outputfile.addEvent(0, actiontime, midievent);
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {
					signal = 0;
				}
				else if (simb->da_li_je_podeljen() == false) {
					midievent[0] = 0x90;
					midievent[1] = mapa.dohvMidi(simb->dohvZnak());
					outputfile.addEvent(0, actiontime, midievent);
					actiontime += tpq / 2 * odrediTrajanje(simb->dohvTraj());
					midievent[0] = 0x80;
					outputfile.addEvent(0, actiontime, midievent);
				}

			}
			else if (simb->tip() == 2) {
				//	if(simb->proveraMidi()==0){
				if (simb->da_li_je_podeljen() && signal == 0) {
					signal = 1;
					int sactiontime = actiontime;
					sactiontime += tpq / 2 * 2;
					for (int br = 0; br < simb->dohvBrNota(); br++) {
						midievent[0] = 0x90;
						midievent[1] = mapa.dohvMidi(simb->dohvZnakNote(br));
						outputfile.addEvent(0, actiontime, midievent);
						midievent[0] = 0x80;
						outputfile.addEvent(0, sactiontime, midievent);
					}
					actiontime = sactiontime;
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {
					signal = 0;
				}
				//	}
				else if (simb->da_li_je_podeljen() == false) {
					int sactiontime = actiontime;
					sactiontime += tpq / 2 * odrediTrajanje(simb->dohvTraj());
					for (int br = 0; br < simb->dohvBrNota(); br++) {
						midievent[0] = 0x90;
						midievent[1] = mapa.dohvMidi(simb->dohvZnakNote(br));
						outputfile.addEvent(0, actiontime, midievent);
						midievent[0] = 0x80;
						outputfile.addEvent(0, sactiontime, midievent);
					}
					actiontime = sactiontime;
				}
			}
		}
	}

	actiontime = 0;
	for (int i = 0; i < leva.dohvBrTaktova(); i++) {
		for (int j = 0; j < leva.dohvTajTakt(i).dohvBrSimbola(); j++) {
			auto simb = leva.dohvTajTakt(i).dohvTajSimbol(j);
			if (simb->tip() == 0) {
				actiontime += tpq / 2 * odrediTrajanje(simb->dohvTraj());
			}
			else if (simb->tip() == 1) {
				if (simb->da_li_je_podeljen() && signal == 0) {
					signal = 1;
					midievent[0] = 0x90;
					midievent[1] = mapa.dohvMidi(simb->dohvZnak());
					outputfile.addEvent(1, actiontime, midievent);
					actiontime += tpq / 2 * 2;
					midievent[0] = 0x80;
					outputfile.addEvent(1, actiontime, midievent);
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {
					signal = 0;
				}
				else if (simb->da_li_je_podeljen() == false) {
					midievent[0] = 0x90;
					midievent[1] = mapa.dohvMidi(simb->dohvZnak());
					outputfile.addEvent(1, actiontime, midievent);
					actiontime += tpq / 2 * odrediTrajanje(simb->dohvTraj());
					midievent[0] = 0x80;
					outputfile.addEvent(1, actiontime, midievent);
				}

			}
			else if (simb->tip() == 2) {
				//if (simb->proveraMidi() == 0) {
				if (simb->da_li_je_podeljen() && signal == 0) {
					signal = 1;
					int sactiontime = actiontime;
					sactiontime += tpq / 2 * 2;
					for (int br = 0; br < simb->dohvBrNota(); br++) {
						midievent[0] = 0x90;
						midievent[1] = mapa.dohvMidi(simb->dohvZnakNote(br));
						outputfile.addEvent(1, actiontime, midievent);
						midievent[0] = 0x80;
						outputfile.addEvent(1, sactiontime, midievent);
					}
					actiontime = sactiontime;
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {
					signal = 0;
				}
				//	}
				else if (simb->da_li_je_podeljen() == false) {
					int sactiontime = actiontime;
					sactiontime += tpq / 2 * odrediTrajanje(simb->dohvTraj());
					for (int br = 0; br < simb->dohvBrNota(); br++) {
						midievent[0] = 0x90;
						midievent[1] = mapa.dohvMidi(simb->dohvZnakNote(br));
						outputfile.addEvent(1, actiontime, midievent);
						midievent[0] = 0x80;
						outputfile.addEvent(1, sactiontime, midievent);
					}
					actiontime = sactiontime;
				}
			}
		}
	}
	outputfile.sortTracks();
	outputfile.write("twinkle.mid");
}