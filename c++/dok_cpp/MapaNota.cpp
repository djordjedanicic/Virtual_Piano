#include"MapaNota.h"

void MapaNota::mapirajNote(string s){
	ifstream dat;
	dat.open(s);
	if (dat.is_open())
	{
		string red;
		regex rx("(.*),(.*),(.*)");
		while (getline(dat, red)) {
			smatch rez;
			if (regex_match(red, rez, rx))
			{
				char ch = rez.str(1)[0];
				string n = rez.str(2);
				int midi = atoi(rez.str(3).c_str());
				mapa.insert(pair< char, pair<string, int> >(ch, pair<string, int>(n, midi)));

			}
		}
		dat.close();
	}
	else
	{
		cout << "Niste uneli ispravnu putanju do datoteke, nije se otvorila" << endl;
	}
}

int MapaNota :: dohvMidi(char k) {
	map<char, pair<string, int>>::iterator t = mapa.find(k);
	return t->second.second;
}

char MapaNota :: dohvChar(string s) {
	for (auto i = mapa.begin(); i != mapa.end(); i++) {
		if (i->second.first == s) {
			return i->first;
		}
	}
}

string MapaNota :: dohvTxtNota(char k) {
	map<char, pair<string, int>>::iterator t = mapa.find(k);
	return t->second.first;
}