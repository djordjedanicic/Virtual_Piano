package klavir;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.TextEvent;
import java.awt.event.TextListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;




public class Piano{
	private Frame pro;
	private List<Button> dgmNiz = new ArrayList<>();
	private List<String> nizIgra = new ArrayList<>();
	private Map<String,Button> dirke = new HashMap<>();
	private Map<String,Color> ime_i_boja = new HashMap<>();
	private Button dgm;
	private String povisice[]= {"!","@","$","%","^","*","(","Q","W","E","T","Y","I","O","P","S","D","G","H","J","L","Z","C","V","B"};
	private String obicneNote[]= {"1","2","3","4","5","6","7","8","9","0","q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n"};
	private Kompozicija komp = null;
	private MapaNota mapa;
	private Crte platno = new Crte();
	private KarakteriKomp obnoviKomp = new KarakteriKomp();
	private String nazivKomp;
	private String trenOdluka;
	private MidiPlayer player;
	private boolean flag=false;
	private boolean flagZaSviranje = false;
	private boolean flagIgra = false;
	private boolean flagZaPocetakIgre = false;
	private ZaSviranje noviZaSviranje = null;
	private ZaAutomatSviranje noviZaAutomatskoSviranje = null;
	private ZaDirku noviZaDirku = null;
	private boolean flagZaDirku = false;
	private String nazivFajla;
	private Button pocniSnimanje = new Button("Snimaj");
	private Button zaustaviSnimanje = new Button("Kraj");
	private boolean pocetakSnimanja=false;
	private ZaSnimanje noviZaSnimanje = null;
	private TXTFormater txtForm = new TXTFormater();
	private MIDIFormater midiForm = new MIDIFormater();
	private List<Simbol> kreiranaKomp = new ArrayList<>();
	private String trenOdlukaSnimanja;
	
	//KONSTRUKTOR
	private Piano() {
		pro = new Frame ("Klavir");
		pro.setBounds(0,0,2000,1040);
		
		pro.setLayout(null);
		WindowListener osl =new Osluskivac();
		pro.addWindowListener(osl);
		mapa = new MapaNota();
		mapa.ucitajMapu(new File("data/map.csv"));
		pro.setMenuBar(new Traka());
		pro.add(platno);
		platno.setBounds(0,250,2000,150);
		try {
			player = new MidiPlayer();
		}catch (Exception e) {}
		pro.add(obnoviKomp);
		obnoviKomp.setBounds(0,0,2000,250);
		
		
		
		int jj=34;
		int z=0;
		int br=0;
		for(int i=0;i<34;i++) {
			if(z==7) {
				z=0;
			}
			if(z!=2 && z!=6) {
				dgm = new Button(povisice[br]);
				dgm.setForeground(Color.WHITE);
				dgm.setFocusable(false);
				pro.add(dgm);
				dgm.setBounds(jj,400,40,150);
				dgm.setBackground(Color.BLACK);
				dgmNiz.add(dgm);
				dirke.put(povisice[br], dgm);
				br++;
			}
			z++;
			jj+=55;
		}
		int j=0;
		for(int i=0;i<35;i++) {
			dgm = new Button(obicneNote[i]);
			dgm.setFocusable(false);
			pro.add(dgm);
			dgm.setBounds(j,400,54,300);
			dgmNiz.add(dgm);
			dirke.put(obicneNote[i], dgm);
			j+=55;
		}
		
		for(Button btn : dgmNiz) {
			
			btn.addMouseListener(new MouseListener() {
				
				@Override
				public void mouseReleased(MouseEvent e) {
					noviZaDirku.pustiDirku(); 
					flagZaDirku = false;
					btn.setBackground(noviZaDirku.boja());
					if(flagZaPocetakIgre) {
						nizIgra.add(btn.getLabel());
						if(!flagIgra){
							noviZaSviranje.flagIgraTrue();
						}
					}
					if(pocetakSnimanja) {
						nizIgra.add(btn.getLabel());
					}
				}
				
				@Override
				public void mousePressed(MouseEvent e) {
					noviZaDirku = new ZaDirku(btn.getLabel(),btn.getBackground());
					noviZaDirku.pritisniDirku();
					noviZaDirku.flagZaDirkuTrue();
					btn.setBackground(Color.RED);
				}
				
				@Override
				public void mouseExited(MouseEvent e) {
				}
				
				@Override
				public void mouseEntered(MouseEvent e) {
				}
				
				@Override
				public void mouseClicked(MouseEvent e) {
				/*	String slovoDgm = btn.getLabel();
					Color cl = null;
					cl=btn.getBackground();
					btn.setBackground(Color.RED);
					try {
						player.radi(player, mapa, slovoDgm.charAt(0), new Trajanje(1, 8));
					} catch (Exception e1) {
						e1.printStackTrace();
					}
					btn.setBackground(cl);
					if(flagZaPocetakIgre) {
						nizIgra.add(slovoDgm);
						if(!flagIgra){
							noviZaSviranje.flagIgraTrue();
						}
					}
					if(pocetakSnimanja) {
						nizIgra.add(slovoDgm);
					}*/
				}
			});
		}
		pro.addKeyListener(new KeyListener() {
			
			
			@Override
			public void keyTyped(KeyEvent e) {}
			
			@Override
			public void keyReleased(KeyEvent e) {
				if(dirke.containsKey(e.getKeyChar()+"")) {
					Button dugme = dirke.get(e.getKeyChar()+"");
					noviZaDirku.pustiDirku(); 
					flagZaDirku = false;
					dugme.setBackground(ime_i_boja.get(dugme.getLabel()));
					ime_i_boja.remove(dugme.getLabel());
					if(flagZaPocetakIgre) {
						nizIgra.add(dugme.getLabel());
						if(!flagIgra){
							noviZaSviranje.flagIgraTrue();
						}
					}
					if(pocetakSnimanja) {
						nizIgra.add(dugme.getLabel());
					}
				}
			}
			
			@Override
			public void keyPressed(KeyEvent e) {
				if(dirke.containsKey(e.getKeyChar()+"")) {
					Button dugme = dirke.get(e.getKeyChar()+"");
					if(!ime_i_boja.containsKey(dugme.getLabel())) {
						ime_i_boja.put(dugme.getLabel(), dugme.getBackground());	
						noviZaDirku = new ZaDirku(dugme.getLabel(),dugme.getBackground());
						noviZaDirku.pritisniDirku();
						noviZaDirku.flagZaDirkuTrue();
						dugme.setBackground(Color.RED);
					}
				}
				
			}
		});
		pro.setFocusTraversalKeysEnabled(true);
		pro.setVisible(true);
		
		
		
	}
	
	private class ZaDirku extends Thread{
		private boolean pustioDirku = false;
		private String nazivDgm;
		private Color boja;
		
		public ZaDirku(String n, Color b) {
			nazivDgm = n;
			boja = b;
			start();
		}
		public Color boja() {
			return boja;
		}
		public boolean pustio() {
			return pustioDirku;
		}
		public void pustiDirku() {
			pustioDirku = true;
		}
		public void pritisniDirku() {
			pustioDirku = false;
		}
		public void prekiniNit() {
			interrupt();
		}
		public synchronized void flagZaDirkuTrue() {
			flagZaDirku =true;
			notify();
		}
		
		@Override
		public void run() {
			try {
				synchronized (this) { 
						while(!flagZaDirku) wait();
						sleep(200);
						if(pustioDirku) {
							player.radi(player, mapa, nazivDgm.charAt(0), new Trajanje(1, 8));
						}
						else {
							player.radi(player, mapa, nazivDgm.charAt(0), new Trajanje(1, 4));
						}
				}
			}catch (InterruptedException e) {}
			catch (Exception e1) {e1.printStackTrace();}
		}
		
	}
	
	
	
	private boolean uporedi() {
		
		if(komp.kompozicija().get(0).dohvKar()=='?') {
			
			List<Character> kop = new ArrayList<>();
			
			for(Character ch : komp.kompozicija().get(0).dohvNizKar()) {
				kop.add(ch);
			}
			
			if(nizIgra.size()==kop.size()) {
				for(String elmIgra : nizIgra) {
					for(Character elmAkord : kop) {
						if(elmIgra.charAt(0)==elmAkord) {
							kop.remove(elmAkord);
							break;
						}
					}
				}
				if(kop.isEmpty()) {
					return true;
				}
				return false;
				}
			return false;
		}
		
		if(nizIgra.size()==1) {
			if(nizIgra.get(0).charAt(0) == komp.kompozicija().get(0).dohvKar())
				return true;
		}
		return false;
		
	}

	private class ZaSviranje extends Thread{
		public ZaSviranje() {
			start();
		}
		public synchronized void flagIgraTrue() {
			flagIgra = true;
			notify();
		}
		
		public void ugasiNit() {
			interrupt();
		}
		

		@Override
		public void run() {
			try {
				while(flagZaPocetakIgre) {
					
					synchronized (this) {
						if(komp.kompozicija().isEmpty()) {
							komp.ucitajKompoziciju(new File("data/"+nazivKomp+".txt"));
							obnoviKomp.repaint();
						}
						if(komp.kompozicija().get(0).dohvKar()==' ' || komp.kompozicija().get(0).dohvKar()=='|') {
							sleep(400);
							komp.kompozicija().remove(0);
							obnoviKomp.repaint();
						}else {
							while(!flagIgra) wait();
							sleep(400);
							if(uporedi()) {
								komp.kompozicija().remove(0);
								obnoviKomp.repaint();
							}
							nizIgra.clear();
							flagIgra=false;
							notify();
						}
					}
				}
			}catch (InterruptedException e) {}
		}
		
		
	}

	private class ZaSnimanje extends Thread{
		
		public ZaSnimanje() {
			start();
		}
		
		public void prekiniNit() {
			interrupt();
		}

		@Override
		public void run() {
			try {
				if(pocetakSnimanja) {
					while(!interrupted()) {
						synchronized (this) {
							nizIgra.clear();
							sleep(200);
							if(nizIgra.isEmpty()) {
								sleep(200);
								if(nizIgra.isEmpty()) {
									kreiranaKomp.add(new Pauza(new Trajanje(1, 4), '|'));
								}else {
									kreiranaKomp.add(new Pauza(new Trajanje(1, 8), ' '));
								}
							}
							if(!nizIgra.isEmpty()) {
								if(noviZaDirku.pustio()) {
									if(nizIgra.size()>1) {
										List<Character> kop = new ArrayList<>();
										for(String st : nizIgra) {
											kop.add(st.charAt(0));
										}
										kreiranaKomp.add(new Akord(new Trajanje(1, 4), kop));
									}else {
										kreiranaKomp.add(new Nota(new Trajanje(1, 8), nizIgra.get(0).charAt(0)));
									}
								}else {
									if(nizIgra.size()>1) {
										List<Character> kop = new ArrayList<>();
										for(String st : nizIgra) {
											kop.add(st.charAt(0));
										}
										kreiranaKomp.add(new Akord(new Trajanje(1, 4), kop));
									}else {
										kreiranaKomp.add(new Nota(new Trajanje(1, 4), nizIgra.get(0).charAt(0)));
									}
								}
							}
						}
					}
				}
			}catch (InterruptedException e) {}
			
		}
		
		
	}
	// TRAKA ZA OPCIJE (MENU)
	private class Traka extends MenuBar{
		public Traka() {
			Menu meni = new Menu("Opcije"); add(meni);
			Menu stavka1 = new Menu("Ucitaj kompoziciju i ispisi je"); meni.add(stavka1);
			MenuItem stavka11 = new MenuItem("Note"); 
			MenuItem stavka12 = new MenuItem("Slova");
			stavka1.add(stavka11);
			stavka1.add(stavka12);
			IspisAkcija ispOsl=new IspisAkcija();
			stavka11.addActionListener(ispOsl);
			stavka12.addActionListener(ispOsl);
			MenuItem stavka2 = new MenuItem("Automatsko sviranje kompozicije");
			meni.add(stavka2);
			AutomatskoSviranje autOsl = new AutomatskoSviranje();
			stavka2.addActionListener(autOsl);
			MenuItem stavka3 = new MenuItem("Sviranje klavira");meni.add(stavka3);
			stavka3.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					if(komp!=null) {
						flag = false;
						flagZaSviranje=false;
						flagZaPocetakIgre=true;
						noviZaSviranje = new ZaSviranje();
					}
				}
			});
			Menu stavka4 = new Menu("Snimanje kompozicije");meni.add(stavka4);
			MenuItem stavka41 = new MenuItem("TXT"); stavka4.add(stavka41);
			
			stavka41.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					MenuItem m = (MenuItem)e.getSource();
					trenOdlukaSnimanja = m.getLabel();
					
					Frame d= new Frame("Upit");
					d.setVisible(true);
					d.setBounds(750,300,400,200);
					d.setLayout(null);
					Label upit = new Label("Naziv Fajla:");
					upit.setBounds(140 , 50 , 400, 40);
					TextField txtU=new TextField("");
					txtU.setBounds(10,90,380,20);
					Button ok = new Button("OK");
					ok.setBounds(170,145,60,40);
					d.add(upit);
					d.add(txtU);
					d.add(ok);
					TextListener txtOsl = new TextListener() {
						@Override
						public void textValueChanged(TextEvent e) {
							nazivFajla = txtU.getText();
						}
					};
					txtU.addTextListener(txtOsl);
					ok.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							pro.add(pocniSnimanje);
							pro.add(zaustaviSnimanje);
							pocniSnimanje.setBounds(750,900,100,50);
							zaustaviSnimanje.setBounds(1050,900,100,50);
							d.dispose();
						}
						
					});
					if(flagZaPocetakIgre) {
						flagZaPocetakIgre=false;
						flagIgra=false;
						noviZaSviranje.ugasiNit();
					}
					
					pocniSnimanje.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							if(!pocetakSnimanja) {
								pocetakSnimanja = true;
								noviZaSnimanje = new ZaSnimanje();
							}
						}
					});
					zaustaviSnimanje.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							if(pocetakSnimanja) {
								pocetakSnimanja = false;
								noviZaSnimanje.prekiniNit();
								if(trenOdlukaSnimanja == "TXT") {
									txtForm.ubaciKomp(kreiranaKomp);
									txtForm.napraviFajl(nazivFajla);
									txtForm.ispisi();
								}else {
									midiForm.ubaciKomp(kreiranaKomp);
									midiForm.napraviFajl(nazivFajla, mapa);
								}
							}
						}
					});
					pocniSnimanje.setFocusable(false);
					zaustaviSnimanje.setFocusable(false);
					
				}
			});
			MenuItem stavka42 = new MenuItem("MIDI");stavka4.add(stavka42);
			stavka42.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					MenuItem m = (MenuItem)e.getSource();
					trenOdlukaSnimanja = m.getLabel();
					
					Frame d= new Frame("Upit");
					d.setVisible(true);
					d.setBounds(750,300,400,200);
					d.setLayout(null);
					Label upit = new Label("Naziv Fajla:");
					upit.setBounds(140 , 50 , 400, 40);
					TextField txtU=new TextField("");
					txtU.setBounds(10,90,380,20);
					Button ok = new Button("OK");
					ok.setBounds(170,145,60,40);
					d.add(upit);
					d.add(txtU);
					d.add(ok);
					TextListener txtOsl = new TextListener() {
						@Override
						public void textValueChanged(TextEvent e) {
							nazivFajla = txtU.getText();
						}
					};
					txtU.addTextListener(txtOsl);
					ok.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							pro.add(pocniSnimanje);
							pro.add(zaustaviSnimanje);
							pocniSnimanje.setBounds(750,900,100,50);
							zaustaviSnimanje.setBounds(1050,900,100,50);
							d.dispose();
						}
						
					});
					if(flagZaPocetakIgre) {
						flagZaPocetakIgre=false;
						flagIgra=false;
						noviZaSviranje.ugasiNit();
					}
					pocniSnimanje.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							if(!pocetakSnimanja) {
								pocetakSnimanja = true;
								noviZaSnimanje = new ZaSnimanje();
							}
						}
					});
					zaustaviSnimanje.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							if(pocetakSnimanja) {
								pocetakSnimanja = false;
								noviZaSnimanje.prekiniNit();
								if(trenOdlukaSnimanja == "TXT") {
									txtForm.ubaciKomp(kreiranaKomp);
									txtForm.napraviFajl(nazivFajla);
									txtForm.ispisi();
								}else {
									midiForm.ubaciKomp(kreiranaKomp);
									midiForm.napraviFajl(nazivFajla,mapa);
								}
							}
						}
					});
					pocniSnimanje.setFocusable(false);
					zaustaviSnimanje.setFocusable(false);
				}
			});
			
			
		}
	}
	
	//ISCRTAVANJE CRTICA(CETVRTINA)
	private class Crte extends Canvas{

		@Override
		public void paint(Graphics g) {
			for(int i=1;i<21;i++) {
				g.drawLine(i*92, 0, i*92, 70);
			}
		}
	}
	
	
	
	//ISCRTAVANJE KOMPPOZICIJE
	private class KarakteriKomp extends Canvas{
		
		@Override
		public void paint(Graphics g) {
			if(komp!=null) {
				int i=0;
				for (Simbol simb : komp.kompozicija()) {
					if(simb.dohvKar()=='?') {
						List<Character> deo=new ArrayList<>();
						g.setColor(Color.RED);
						int br=0;
						for (Character ch : simb.dohvNizKar()) {
							deo.add(ch);
							br++;
						}
						g.fillRect(i, 120-((br+1)/2)*20, 92, br*40);
						int poc=120-((br+1)/2)*20+25;
						g.setColor(Color.BLACK);
						if(trenOdluka.equals("Slova")) {
							int isp=0;
							for (Character ch : simb.dohvNizKar()) {
								g.drawString(ch+"", i+40, poc+isp);
								isp+=30;
							}
						}
						else {
							int isp=0;
							for (Character ch : simb.dohvNizKar()) {
								g.drawString(mapa.dohvNotu(ch), i+40, poc+isp);
								isp+=30;
							}
						}
					}
					else {
						if(simb.dohvTraj().jednako(new Trajanje(1, 4))) {
							g.setColor(Color.RED);
							g.fillRect(i, 120, 92, 40);
							g.setColor(Color.BLACK);
							if(trenOdluka.equals("Slova")) {
								if(simb.dohvKar()=='|') {
									g.drawString("", i+40, 141);
								}else {
									g.drawString(simb.dohvKar()+"", i+40, 141);
								}
							}else {
								if(simb.dohvKar()=='|') {
									g.drawString("", i+40, 141);
								}else {
									g.drawString(mapa.dohvNotu(simb.dohvKar()), i+40, 141);
								}
							}
						}else {
							g.setColor(Color.GREEN);
							g.fillRect(i, 120, 46, 40);
							g.setColor(Color.BLACK);
							g.drawString(simb.dohvKar()+"", i+20, 141);
						}
					}
				i+=simb.dohvPomeraj();
				}
			}
		}
	}
	
	
	
	
	
	// OSLUSKIVAC ZA ISPIS KOMPOZICIJE
	private class IspisAkcija implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			MenuItem m = (MenuItem)e.getSource();
			trenOdluka = m.getLabel();
			Frame d= new Frame("Upit");
			d.setVisible(true);
			d.setBounds(750,300,400,200);
			d.setLayout(null);
			Label upit = new Label("Naziv kompozicije");
			upit.setBounds(140 , 50 , 400, 40);
			TextField txtU=new TextField("");
			txtU.setBounds(10,90,380,20);
			Button ok = new Button("OK");
			ok.setBounds(170,145,60,40);
			d.add(upit);
			d.add(txtU);
			d.add(ok);
			TextListener txtOsl = new TextListener() {
				@Override
				public void textValueChanged(TextEvent e) {
					nazivKomp = txtU.getText();
				}
			};
			txtU.addTextListener(txtOsl);
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					komp =new Kompozicija();
					komp.ucitajKompoziciju(new File("data/"+nazivKomp+".txt"));
					obnoviKomp.repaint();
					d.dispose();
				}
			});
			
		}
		
	}
	
	
	private class AutomatskoSviranje implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			if(komp!=null) {
				Button sviraj = new Button("Sviraj");
				Button zaustavi = new Button("Zaustavi");
				pro.add(sviraj);
				pro.add(zaustavi);
				sviraj.setBounds(750,800,100,50);
				zaustavi.setBounds(1050,800,100,50);
				sviraj.addActionListener(new ActionListener() {
					@Override
					public synchronized void actionPerformed(ActionEvent e) {
						if(!flagZaSviranje) {
							flag = true;
							noviZaAutomatskoSviranje = new ZaAutomatSviranje();
							flagZaSviranje = true; notify();
							flagZaPocetakIgre=false;
							if(noviZaSviranje!=null)
								noviZaSviranje.ugasiNit();
						}
					}
				});
				sviraj.setFocusable(false);
				zaustavi.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						flag = false;
						flagZaSviranje=false;
					}
				});
				zaustavi.setFocusable(false);
				
			}
		}
		
	}
	
	private class ZaAutomatSviranje extends Thread{
		public ZaAutomatSviranje() {
			start();
		}
		public void ugasiNit() {
			interrupt();
		}
		
		@Override
		public void run() {
			try {
				synchronized (this) {
					while (!flagZaSviranje) wait();
					radiPosao2();
				}
			}catch (InterruptedException e) {}
		}
	}
	
	
	public void radiPosao2() {
		while(flag==true) {
				if ( komp.kompozicija().get(0).dohvKar()== '?') {
					List<Color> nizBoja = new ArrayList<>();
					List<Button> nizDgm = new ArrayList<>();
					for(Character ch : komp.kompozicija().get(0).dohvNizKar()) {
						for(Button btn : dgmNiz) {
							if(ch==btn.getLabel().charAt(0)) {
								nizDgm.add(btn);
							}
						}
					}
					for(Button dgm : nizDgm) {
						nizBoja.add(dgm.getBackground());
						dgm.setBackground(Color.RED);
					}
					try {
						player.radiAkord(player, mapa, komp.kompozicija().get(0).dohvNizKar(),  komp.kompozicija().get(0).dohvTraj());
					}catch (Exception ee) {}	
					for(Button dgm : nizDgm) {
						dgm.setBackground(nizBoja.get(0));
						nizBoja.remove(0);
					}
				}else {
					Color cl = null;
					for (Button btn : dgmNiz) {
						if(btn.getLabel().charAt(0)==komp.kompozicija().get(0).dohvKar()) {
							cl=btn.getBackground();
							btn.setBackground(Color.RED);
						}
					}
					
					try {
						player.radi(player, mapa, komp.kompozicija().get(0).dohvKar(),  komp.kompozicija().get(0).dohvTraj());
					}catch (Exception ee) {}
					for (Button btn : dgmNiz) {
						if(btn.getLabel().charAt(0)==komp.kompozicija().get(0).dohvKar()) {
							btn.setBackground(cl);			
						}
					}
				}
				
				komp.kompozicija().remove(0);
				obnoviKomp.repaint();
				if(komp.kompozicija().isEmpty()) {
					komp.ucitajKompoziciju(new File("data/"+nazivKomp+".txt"));
					obnoviKomp.repaint();
					flag=false;
					flagZaSviranje=false;
				}
				
		}
	}
	
	//OSLUSKOVAC ZA ZATVARANJE PROZORA
	private class Osluskivac extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			
			if(noviZaSviranje!=null)
				noviZaSviranje.ugasiNit();
			if(noviZaDirku!=null)
				noviZaDirku.prekiniNit();
			if(pocetakSnimanja) {
				pocetakSnimanja=false;
				noviZaSnimanje.prekiniNit();
			}
			
			flag=false;
			pro.dispose();
		}
	}
	
	
	
	public static void main(String[] varg) {
		new Piano();
	}

}
