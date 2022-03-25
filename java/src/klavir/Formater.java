package klavir;

import java.util.List;
import java.util.ArrayList;

public abstract class Formater {
	protected List<Simbol> kreiranaKomp = new ArrayList<>();
	
	
	public void ubaciKomp(List<Simbol> kop) {
		for(Simbol simb : kop) {
			kreiranaKomp.add(simb);
		}
		while(kreiranaKomp.get(0).dohvKar()=='|' || kreiranaKomp.get(0).dohvKar()==' ') {
			kreiranaKomp.remove(0);
		}
		while(kreiranaKomp.get(kreiranaKomp.size()-1).dohvKar()=='|' || kreiranaKomp.get(kreiranaKomp.size()-1).dohvKar()==' ') {
			kreiranaKomp.remove(kreiranaKomp.size()-1);
		}
		
	
	}
	
	
	
	
}
