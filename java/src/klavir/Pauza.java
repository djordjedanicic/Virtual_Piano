package klavir;

import java.awt.*;
import java.util.List;

public class Pauza extends Simbol{
	private char kar;
	private int pomeraj;
	public Pauza(Trajanje traj, char pauzKar) {
		super(traj);
		kar=pauzKar;
	}
	@Override
	public void ispis() {
		System.out.print(kar);
	}
	@Override
	public Panel delicCrteza() {
		Panel panel =new Panel();
		if (traj.jednako(new Trajanje(1,4))) {
			panel.setSize(92, 40);
			panel.setName(""+kar);
			panel.setBackground(Color.RED);
			pomeraj=92;
		}
		else {
			panel.setSize(46, 40);
			panel.setName(""+kar);
			panel.setBackground(Color.GREEN);
			pomeraj=46;
		}
		return panel;
	}
	@Override
	public int dohvPomeraj() {
		if(traj.jednako(new Trajanje(1, 4))) {
			return 92;
		}
		return 46;
	}
	@Override
	public char dohvKar() {
		return kar;
	}
	@Override
	public List<Character> dohvNizKar() {
		return null;
	}
	
}
