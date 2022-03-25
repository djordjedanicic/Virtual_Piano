#include"MusicXMLFormat.h"

void MusicXML :: napraviXML(Ruka &leva, Ruka &desna, MapaNota &mapa) {
	ofstream dat;
	dat.open("skica.musicxml");
	dat << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	dat << "<!DOCTYPE score-partwise PUBLIC" << endl;
	dat << "    \"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"" << endl;
	dat << "    \"http://www.musicxml.org/dtds/partwise.dtd" << "\">" << endl;
	dat << "<score-partwise version=\"3.1\">" << endl;
	dat << "  <part-list>" << endl;
	dat << "    <score-part id=\"Right\"></score-part>" << endl;
	dat << "    <score-part id=\"Left\"></score-part>" << endl;
	dat << "  </part-list>" << endl;
	//DESNA
	dat << "  <part id=\"Right\">" << endl;
	dat << "    <measure>" << endl;
	dat << "      <attributes>" << endl;
	dat << "        <divisions>2</divisions>" << endl;
	dat << "        <time>" << endl;
	dat << "          <beats>";
	dat << desna.dohvTrTakta().getBr();
	dat << "</beats>" << endl;
	dat << "          <beat-type>";
	dat << desna.dohvTrTakta().getIm();
	dat << "</beat-type>" << endl;
	dat << "        </time>" << endl;
	dat << "        <clef>" << endl;
	dat << "          <sign>G</sign>" << endl;
	dat << "          <line>2</line>" << endl;
	dat << "        </clef>" << endl;
	dat << "      </attributes>" << endl << endl;
	signal = 0;
	for (int i = 0; i < desna.dohvBrTaktova(); i++) {
		for (int j = 0; j < desna.dohvTajTakt(i).dohvBrSimbola(); j++) {
			auto simb = desna.dohvTajTakt(i).dohvTajSimbol(j);
			if (simb->tip() == 0) {
				dat << "      <note>" << endl;
				dat << "        <rest/>" << endl;
				dat << "        <duration>";
				dat << odrediTrajanje(simb->dohvTraj());
				dat << "</duration>" << endl;
				dat << "      </note>" << endl;
			}
			else if (simb->tip() == 1) {
				string txt = mapa.dohvTxtNota(simb->dohvZnak());
				dat << "      <note>" << endl;
				dat << "        <pitch>" << endl;
				dat << "          <step>";
				dat << txt[0];
				dat << "</step>" << endl;
				dat << "          <octave>";
				if (txt[1] == '#')
					dat << txt[2];
				else dat << txt[1];
				dat << "</octave>" << endl;
				if (txt[1] == '#') {
					dat << "          <alter>1</alter>" << endl;
				}
				dat << "        </pitch>" << endl;
				dat << "        <duration>";
				dat << odrediTrajanje(simb->dohvTraj());
				dat << "</duration>" << endl;
				if (simb->da_li_je_podeljen() && signal == 0) {
					signal = 1;
					dat << "        <tie type=\"start\"/>" << endl;
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {
					signal = 0;
					dat << "        <tie type=\"end\"/>" << endl;
				}
				dat << "      </note>" << endl;
			}
			else if (simb->tip() == 2) {
				string txt = mapa.dohvTxtNota(simb->dohvZnakNote(0));
				dat << "      <note>" << endl;
				dat << "        <pitch>" << endl;
				dat << "          <step>";
				dat << txt[0];
				dat << "</step>" << endl;
				dat << "          <octave>";
				if (txt[1] == '#')
					dat << txt[2];
				else dat << txt[1];
				dat << "</octave>" << endl;
				if (txt[1] == '#') {
					dat << "          <alter>1</alter>" << endl;
				}
				dat << "        </pitch>" << endl;
				dat << "        <duration>";
				dat << odrediTrajanje(simb->dohvTraj());
				dat << "</duration>" << endl;
				if (simb->da_li_je_podeljen() && signal == 0) {

					dat << "        <tie type=\"start\"/>" << endl;
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {

					dat << "        <tie type=\"end\"/>" << endl;
				}
				dat << "      </note>" << endl;				if (simb->da_li_je_podeljen()) {					if (simb->dohvBrNota() == 1 && signal == 0) {						signal = 1;					}					else if (simb->dohvBrNota() == 1 && signal == 1) {						signal = 0;					}				}				for (int br = 1; br < simb->dohvBrNota(); br++) {
					string txt = mapa.dohvTxtNota(simb->dohvZnakNote(br));
					dat << "      <note>" << endl;
					dat << "          <chord/>" << endl;
					dat << "        <pitch>" << endl;
					dat << "          <step>";
					dat << txt[0];
					dat << "</step>" << endl;
					dat << "          <octave>";
					if (txt[1] == '#')
						dat << txt[2];
					else dat << txt[1];
					dat << "</octave>" << endl;
					if (txt[1] == '#') {
						dat << "          <alter>1</alter>" << endl;
					}
					dat << "        </pitch>" << endl;
					dat << "        <duration>";
					dat << odrediTrajanje(simb->dohvTraj());
					dat << "</duration>" << endl;

					if ((br + 1) < simb->dohvBrNota() && signal == 0 && simb->da_li_je_podeljen()) {
						dat << "        <tie type=\"start\"/>" << endl;
					}
					else if ((br + 1) == simb->dohvBrNota() && signal == 0 && simb->da_li_je_podeljen()) {
						signal = 1;
						dat << "        <tie type=\"start\"/>" << endl;
					}
					else if ((br + 1) < simb->dohvBrNota() && signal == 1 && simb->da_li_je_podeljen()) {
						dat << "        <tie type=\"end\"/>" << endl;
					}
					else if ((br + 1) == simb->dohvBrNota() && signal == 1 && simb->da_li_je_podeljen()) {
						signal = 0;
						dat << "        <tie type=\"end\"/>" << endl;
					}
					dat << "      </note>" << endl;
				}
			}
		}
		dat << "    </measure>" << endl;
		if ((i + 1) != desna.dohvBrTaktova())
			dat << "    <measure>" << endl;
	}
	dat << "  </part>" << endl << endl;


	//LEVA

	dat << "  <part id=\"Left\">" << endl;
	dat << "    <measure>" << endl;
	dat << "      <attributes>" << endl;
	dat << "        <divisions>2</divisions>" << endl;
	dat << "        <time>" << endl;
	dat << "          <beats>";
	dat << leva.dohvTrTakta().getBr();
	dat << "</beats>" << endl;
	dat << "          <beat-type>";
	dat << leva.dohvTrTakta().getIm();
	dat << "</beat-type>" << endl;
	dat << "        </time>" << endl;
	dat << "        <clef>" << endl;
	dat << "          <sign>F</sign>" << endl;
	dat << "          <line>4</line>" << endl;
	dat << "        </clef>" << endl;
	dat << "      </attributes>" << endl << endl;
	signal = 0;
	for (int k = 0; k < leva.dohvBrTaktova(); k++) {
		for (int p = 0; p < leva.dohvTajTakt(k).dohvBrSimbola(); p++) {
			auto simb = leva.dohvTajTakt(k).dohvTajSimbol(p);
			if (simb->tip() == 0) {
				dat << "      <note>" << endl;
				dat << "        <rest/>" << endl;
				dat << "        <duration>";
				dat << odrediTrajanje(simb->dohvTraj());
				dat << "</duration>" << endl;
				dat << "      </note>" << endl;
			}
			else if (simb->tip() == 1) {
				string txt = mapa.dohvTxtNota(simb->dohvZnak());
				dat << "      <note>" << endl;
				dat << "        <pitch>" << endl;
				dat << "          <step>";
				dat << txt[0];
				dat << "</step>" << endl;
				dat << "          <octave>";
				if (txt[1] == '#')
					dat << txt[2];
				else dat << txt[1];
				dat << "</octave>" << endl;
				if (txt[1] == '#') {
					dat << "          <alter>1</alter>" << endl;
				}
				dat << "        </pitch>" << endl;
				dat << "        <duration>";
				dat << odrediTrajanje(simb->dohvTraj());
				dat << "</duration>" << endl;
				if (simb->da_li_je_podeljen() && signal == 0) {
					signal = 1;
					dat << "        <tie type=\"start\"/>" << endl;
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {
					signal = 0;
					dat << "        <tie type=\"end\"/>" << endl;
				}
				dat << "      </note>" << endl;
			}
			else if (simb->tip() == 2) {
				string txt = mapa.dohvTxtNota(simb->dohvZnakNote(0));
				dat << "      <note>" << endl;
				dat << "        <pitch>" << endl;
				dat << "          <step>";
				dat << txt[0];
				dat << "</step>" << endl;
				dat << "          <octave>";
				if (txt[1] == '#')
					dat << txt[2];
				else dat << txt[1];
				dat << "</octave>" << endl;
				if (txt[1] == '#') {
					dat << "          <alter>1</alter>" << endl;
				}
				dat << "        </pitch>" << endl;
				dat << "        <duration>";
				dat << odrediTrajanje(simb->dohvTraj());
				dat << "</duration>" << endl;
				if (simb->da_li_je_podeljen() && signal == 0) {

					dat << "        <tie type=\"start\"/>" << endl;
				}
				else if (simb->da_li_je_podeljen() && signal == 1) {

					dat << "        <tie type=\"end\"/>" << endl;
				}
				dat << "      </note>" << endl;				if (simb->da_li_je_podeljen()) {					if (simb->dohvBrNota() == 1 && signal == 0) {						signal = 1;					}					else if (simb->dohvBrNota() == 1 && signal == 1) {						signal = 0;					}				}				for (int br = 1; br < simb->dohvBrNota(); br++) {
					string txt = mapa.dohvTxtNota(simb->dohvZnakNote(br));
					dat << "      <note>" << endl;
					dat << "          <chord/>" << endl;
					dat << "        <pitch>" << endl;
					dat << "          <step>";
					dat << txt[0];
					dat << "</step>" << endl;
					dat << "          <octave>";
					if (txt[1] == '#')
						dat << txt[2];
					else dat << txt[1];
					dat << "</octave>" << endl;
					if (txt[1] == '#') {
						dat << "          <alter>1</alter>" << endl;
					}
					dat << "        </pitch>" << endl;
					dat << "        <duration>";
					dat << odrediTrajanje(simb->dohvTraj());
					dat << "</duration>" << endl;

					if ((br + 1) < simb->dohvBrNota() && signal == 0 && simb->da_li_je_podeljen()) {
						dat << "        <tie type=\"start\"/>" << endl;
					}
					else if ((br + 1) == simb->dohvBrNota() && signal == 0 && simb->da_li_je_podeljen()) {
						signal = 1;
						dat << "        <tie type=\"start\"/>" << endl;
					}
					else if ((br + 1) < simb->dohvBrNota() && signal == 1 && simb->da_li_je_podeljen()) {
						dat << "        <tie type=\"end\"/>" << endl;
					}
					else if ((br + 1) == simb->dohvBrNota() && signal == 1 && simb->da_li_je_podeljen()) {
						signal = 0;
						dat << "        <tie type=\"end\"/>" << endl;
					}
					dat << "      </note>" << endl;
				}
			}
		}
		dat << "    </measure>" << endl;
		if ((k + 1) != leva.dohvBrTaktova())
			dat << "    <measure>" << endl;
	}
	dat << "  </part>" << endl;
	dat << "</score-partwise>";



	dat.close();
}

char MusicXML :: odrediTrajanje(Razlomak tr) {
	if (tr == tr4)
		return '2';
	else return '1';
}