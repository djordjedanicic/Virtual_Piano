package klavir;

import java.awt.*;
import java.util.List;

public class Nota extends Simbol{
	private char kar;
	private int pomeraj;
	public Nota(Trajanje traj, char notaKar) {
		super(traj);
		kar=notaKar;
	}
	@Override
	public void ispis() {
		System.out.print(kar);
	}
	@Override
	public Panel delicCrteza() {
		Panel panel =new Panel(new BorderLayout());
		//Label lab = new Label(kar+"",Label.CENTER);
		if (traj.jednako(new Trajanje(1,4))) {
			panel.setSize(92, 40);
			panel.setBackground(Color.RED);
		//	panel.add(lab,"Center");
			pomeraj=92;
		}
		else {
			panel.setSize(46, 40);
			//panel.add(lab,"Center");
			panel.setBackground(Color.GREEN);
			pomeraj=46;
		}
		panel.setForeground(Color.BLACK);
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
