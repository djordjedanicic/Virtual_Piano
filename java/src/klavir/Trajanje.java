package klavir;

public class Trajanje {
	private int x;
	private int y;
	public Trajanje(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public int getX() {
		return x;
	}
	public int getY() {
		return y;
	}
	/*public boolean veciOd(Trajanje t) {
		if((this.x * t.y) > (t.x * this.y))
			return true;
		return false;
	}*/
	
	public boolean jednako(Trajanje t) {
		if((this.x * t.y) == (t.x * this.y))
			return true;
		return false;
	}
	
}
