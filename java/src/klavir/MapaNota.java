package klavir;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;

public class MapaNota {
	private Map<Character,MapaNota> mapa = new HashMap<>();
	private Collection<MapaNota> podaciMapa = mapa.values();
	private char znak;
	private String nota; 
	private int midi;
	
	public MapaNota() { }
	
	public MapaNota(char znak, String nota, int midi) {
		this.znak = znak;
		this.nota = nota;
		this.midi = midi;
	}
	
	public static MapaNota parsiraj(String s) {
		MapaNota map=null;
		Pattern p = Pattern.compile("^(.*),(.*),(.*)$");
		Matcher m = p.matcher(s);
		if(m.matches()) {
			char znak = m.group(1).charAt(0);
			String nota = m.group(2);
			int midi = Integer.parseInt(m.group(3));
			
			map = new MapaNota(znak, nota, midi);
		}
		return map;
	}
	
	public void ucitajMapu(File file) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(file));
			Stream<String> s = br.lines();
			
			s.forEach(l->{
				MapaNota redMape = MapaNota.parsiraj(l);
				mapa.put(redMape.dohvZnak(), redMape);
			});
			br.close();
		}catch (FileNotFoundException e) {
			System.err.println("Fajl nije pronadjen...");
		}catch (IOException e) {}
	}
	
	public Character dohvZnak() {
		return znak;
	}
	public String dohvNotu() {
		return nota;
	}
	public int dohvMidi() {
		return midi;
	}
	
	public int dohvMidi(Character ch) {
		return mapa.get(ch).dohvMidi();
		
		/*for (MapaNota mN : podaciMapa) {
			if(mN.dohvZnak()==ch) {
				return mN.dohvMidi();
			}
		}
		return 0;*/
	}
	public String dohvNotu(Character ch) {
		return mapa.get(ch).dohvNotu();
				
		/*for (MapaNota mN : podaciMapa) {
			if(mN.dohvZnak()==ch) {
				return mN.dohvNotu();
			}
		}
		return null;*/
	}
	
	
	public void ispisiMapu() {
		System.out.println();
		mapa.values().stream().forEach(System.out::println);
	}
	
	@Override
	public String toString() {
		return  znak + nota +midi;
	}


}
