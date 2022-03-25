package klavir;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public class TXTFormater extends Formater{
	
	
	public void napraviFajl(String nazivFajla) {
		
		try {
   		 
		      File file = new File("data/"+nazivFajla+".txt");
		      
		      if(!file.exists()) {
		    	  file.createNewFile();
		      }
		      PrintWriter pw = new PrintWriter(file);
		      for(Simbol simb : kreiranaKomp) {
		    	  if(simb.dohvKar()=='?') {
		    		  pw.print('[');
		    		  for(Character ch : simb.dohvNizKar()) {
		    			  pw.print(ch);
		    		  }
		    		  pw.print(']');
		    	  }else {
		    		  pw.print(simb.dohvKar());
		    	  }
		      }
		      pw.close();
		      
	    	} catch (IOException e) {
		      e.printStackTrace();
	    	}
	}
	
	public void ispisi() {
		for(Simbol sm : kreiranaKomp ) {
			sm.ispis();
		}
	}

}
