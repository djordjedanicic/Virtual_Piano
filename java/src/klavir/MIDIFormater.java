package klavir;
import java.io.*;
import javax.sound.midi.*;

public class MIDIFormater extends Formater{

	private int tr=0;
	public void napraviFajl(String nazivFajla, MapaNota mapa) {
		try {
			Sequence s = new Sequence(javax.sound.midi.Sequence.PPQ,24);
			Track t = s.createTrack();
			
			byte[] b = {(byte)0xF0, 0x7E, 0x7F, 0x09, 0x01, (byte)0xF7};
			SysexMessage sm = new SysexMessage();
			sm.setMessage(b, 6);
			MidiEvent me = new MidiEvent(sm,(long)0);
			t.add(me);
			
			MetaMessage mt = new MetaMessage();
	        byte[] bt = {0x02, (byte)0x00, 0x00};
			mt.setMessage(0x51 ,bt, 3);
			me = new MidiEvent(mt,(long)0);
			t.add(me);
			
			mt = new MetaMessage();
			String TrackName = new String("midifile track");
			mt.setMessage(0x03 ,TrackName.getBytes(), TrackName.length());
			me = new MidiEvent(mt,(long)0);
			t.add(me);
			
			ShortMessage mm = new ShortMessage();
			mm.setMessage(0xB0, 0x7D,0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);
			
			mm = new ShortMessage();
			mm.setMessage(0xB0, 0x7F,0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);

			mm = new ShortMessage();
			mm.setMessage(0xC0, 0x00, 0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);

			for(Simbol simb : kreiranaKomp) {
					if(simb.dohvKar()=='?') {
						for(Character ch : simb.dohvNizKar()) {
							mm = new ShortMessage();
							mm.setMessage(0x90,mapa.dohvMidi(ch),0x60);
							me = new MidiEvent(mm,(long)tr);
							t.add(me);
						}
					}else if(simb.dohvKar()!=' ' && simb.dohvKar()!='|'){
						mm = new ShortMessage();
						mm.setMessage(0x90,mapa.dohvMidi(simb.dohvKar()),0x60);
						me = new MidiEvent(mm,(long)tr);
						t.add(me);
					}	
					
					if(simb.dohvTraj().jednako(new Trajanje(1, 4))) {
						tr+=80;
					}else {
						tr+=40;
					}
					
					if(simb.dohvKar()=='?') {
						for(Character ch : simb.dohvNizKar()) {
							mm = new ShortMessage();
							mm.setMessage(0x80,mapa.dohvMidi(ch),0x40);
							me = new MidiEvent(mm,(long)tr);
							t.add(me);
						}
					}else if(simb.dohvKar()!=' ' && simb.dohvKar()!='|'){
						mm = new ShortMessage();
						mm.setMessage(0x80,mapa.dohvMidi(simb.dohvKar()),0x40);
						me = new MidiEvent(mm,(long)tr);
						t.add(me);
					}
			}
		
			
			mt = new MetaMessage();
	        byte[] bet = {}; // empty array
			mt.setMessage(0x2F,bet,0);
			me = new MidiEvent(mt, (long)140);
			t.add(me);

			File f = new File("data1/"+nazivFajla+".mid");
			MidiSystem.write(s,1,f);
			
		} catch(Exception e){
			System.out.println("Exception caught " + e.toString());
		} 
		
	}
		

}
