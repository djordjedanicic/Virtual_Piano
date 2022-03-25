package klavir;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Akord extends Simbol{
	private List<Character> nizKar = new ArrayList<>();

	public Akord(Trajanje traj,List<Character> nizAk) {
		super(traj);
		for (Character elemNizAk : nizAk) {
			nizKar.add(elemNizAk);
		}
	}
	@Override
	public void ispis() {
		System.out.print('[');
		for (Character kar : nizKar) {
			System.out.print(kar);
		}
		System.out.print(']');
	}
	@Override
	public Panel delicCrteza() {
		for (Character ch : nizKar) {
			
		}
		return null;
	}
	@Override
	public int dohvPomeraj() {
		// TODO Auto-generated method stub
		return 92;
	}
	@Override
	public char dohvKar() {
		return '?';
	}
	@Override
	public List<Character> dohvNizKar() {
		return nizKar;
	}

}
