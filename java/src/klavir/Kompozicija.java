package klavir;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class Kompozicija {
	
	
	
	private List<Simbol> nizSimb= new ArrayList<>();
	private List<Character> deo= new ArrayList<>();
	
	private static final Trajanje cetvrtina= new Trajanje(1,4);
	private static final Trajanje osmina= new Trajanje(1,8);
	
	
	
	//public void prikaziKompSlova(Kompozicija komp) {}
	//public void prikaziKompNota(Kompozicija komp) {}
	
	public void sredi(String parce) {
		int i=0;
		char ch;
		while(i<parce.length()) {
			ch=parce.charAt(i);
			while (ch != ' ' && ch != '|' && ch != '[' && i<parce.length()) {
				deo.add(ch);
				i++;
				if (i<parce.length())
					ch=parce.charAt(i);
			}
			if(deo.size()>0) {
				for (Character kar : deo) {
					Nota nota= new Nota(cetvrtina, kar);
					nizSimb.add(nota);
				}	
			}
			deo.clear();
			if (ch == ' ') {
				Pauza pauza= new Pauza(osmina, ch);
				nizSimb.add(pauza);
			}
			else if (ch == '|') {
				Pauza pauza= new Pauza(cetvrtina, ch);
				nizSimb.add(pauza);
			}
			else if (ch == '[') {
				i++;
				ch=parce.charAt(i);
				while (ch != ' ' && ch != ']'&& i<parce.length()) {
					deo.add(ch);
					i++;
					ch=parce.charAt(i);
				}
				if (ch == ' ') {
					while (ch != ']') {
						deo.add(ch);
						i++;
						ch=parce.charAt(i);
					}
					for (Character kar : deo) {
						Nota nota= new Nota(osmina, kar);
						if(kar!=' ') {
							nizSimb.add(nota);
						}
					}
				}
				else {
					Akord akord= new Akord(cetvrtina, deo);
					nizSimb.add(akord);
				}
			}
			i++;
			deo.clear();
		}
	}
	
	public void ucitajKompoziciju(File file) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(file));
			Stream<String> s = br.lines();
			nizSimb.clear();
			
			s.forEach(l->{
				sredi(l);
			});
			br.close();
		}catch (FileNotFoundException e) {
			System.err.println("Fajl nije pronadjen...");
		}catch (IOException e) {}
		
	}
	
	public List<Simbol> kompozicija (){
		return nizSimb;
	}

	public void ispisiKomp() {
		for (Simbol simb : nizSimb) {
			simb.ispis();
		}
	}

	
}
