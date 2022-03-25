package klavir;

import java.util.List;

import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Synthesizer;

public class MidiPlayer {
	
	private static final int DEFAULT_INSTRUMENT = 1;
	private MidiChannel channel;
	private boolean flag =true;
	
	
	public MidiPlayer() throws MidiUnavailableException {
		this(DEFAULT_INSTRUMENT);
	}
	
	public MidiPlayer(int instrument) throws MidiUnavailableException {
		channel = getChannel(instrument);
	}
	
	public void play(final int note) {
		channel.noteOn(note, 50);
	}
	
	public void release(final int note) {
		channel.noteOff(note, 50);
	}
	
	public void play(final int note, final long length) throws InterruptedException {
		play(note);
		Thread.sleep(length);
		release(note);
	}
	
	private static MidiChannel getChannel(int instrument) throws MidiUnavailableException {
		Synthesizer synthesizer = MidiSystem.getSynthesizer();
		synthesizer.open();
		return synthesizer.getChannels()[instrument];
	}
	
	public void radi(MidiPlayer player,MapaNota mapa, char znak,Trajanje t) throws Exception {
		int note;
			if(znak==' ' || znak == '|') {
				if(t.jednako(new Trajanje(1, 4))){
					Thread.sleep(400);
				}else {
					Thread.sleep(200);
				}
				
			}else {
				note = mapa.dohvMidi(znak);
				if(t.jednako(new Trajanje(1, 4))){
					player.play(note, 400);
				}else {
					player.play(note, 200);
				}
			}
	}
	
	public void radiAkord(MidiPlayer player,MapaNota mapa, List<Character> nizCh, Trajanje t) throws InterruptedException  {
		for (Character ch : nizCh) {
			int note = mapa.dohvMidi(ch);
			play(note);
		}
		Thread.sleep(400);
		for (Character ch : nizCh) {
			int note = mapa.dohvMidi(ch);
			release(note);
		}
	}
	
	
}
