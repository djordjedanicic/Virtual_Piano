#pragma once
#include<iostream>
#include<string>
#include<map>
#include<regex>
#include<fstream>

using namespace std;

class MapaNota {
	map<char, pair<string, int>> mapa;
public:

	MapaNota() {}

	void mapirajNote(string s);

	int dohvMidi(char k);

	char dohvChar(string s);

	string dohvTxtNota(char k);
};

