package klavir;

import java.awt.*;
import java.util.List;

public abstract class Simbol{
	
	protected Trajanje traj;

	public Simbol(Trajanje traj) {
		this.traj = traj;
	}
	public abstract Panel delicCrteza();
	public abstract void ispis();
	public abstract char dohvKar();
	public abstract int dohvPomeraj();
	public Trajanje dohvTraj() {
		return traj;
	}
	public abstract List<Character> dohvNizKar();
}
