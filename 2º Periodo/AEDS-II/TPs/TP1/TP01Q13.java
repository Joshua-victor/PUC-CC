import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
 
public class TP01Q13
{

	public static void contador(String nome, String str, int tamanho) {

	  int out01 = 0;// a
      int out02 = 0;// e
      int out03 = 0;// i
      int out04 = 0;// o
      int out05 = 0;// u
      int out06 = 0;// á
      int out07 = 0;// é
      int out08 = 0;// í
      int out09 = 0;// ó
      int out10 = 0;// ú
      int out11 = 0;// à
      int out12 = 0;// è
      int out13 = 0;// ì
      int out14 = 0;// ò
      int out15 = 0;// ù
      int out16 = 0;// ã
      int out17 = 0;// õ
      int out18 = 0;// â
      int out19 = 0;// ê
      int out20 = 0;// ô
      int out21 = 0;// î
      int out22 = 0;// û
      int out23 = 0;// Consoante-
      int out24 = 0;// <br>-
      int out25 = 0;// <table>-    


		for(int i = 0; i < tamanho; i++) {

			if(str.charAt(i) == '<') {

				if(str.charAt(i + 1) == 'b' &&  str.charAt(i + 2) == 'r'  &&  str.charAt(i + 3) == '>') {
					out24++; //<br>
					i+= 3; // se for <br> ele atualiza o i para não precisar passar por eles denovo
				} else if(str.charAt(i + 1) == 't' && str.charAt(i + 2) == 'a' && str.charAt(i + 2) == 'b'
				          && str.charAt(i + 2) == 'l' && str.charAt(i + 2) == 'e' && str.charAt(i + 2) == '>' ) {
					out25++; // < table>
					i+=6; // se for <table> ele atualiza o i para não precisar passar por eles denovo
				}
			} else if (str.charAt(i) >= 'a' && str.charAt(i) <= 'z') {

				if (str.charAt(i) == 'a')
					out01++;
				else if (str.charAt(i) == 'e')
					out02++;
				else if (str.charAt(i) == 'i')
					out03++;
				else if (str.charAt(i) == 'o')
					out04++;
				else if (str.charAt(i) == 'u')
					out05++;
				else // se não for vogal é consoante
				{
					out23++;
				}
			}
			 else if (str.charAt(i) == 225)
            out06++;// á
         else if (str.charAt(i) == 233)
            out07++;// é
         else if (str.charAt(i) == 237)
            out08++;// í
         else if (str.charAt(i) == 243)
            out09++;// ó
         else if (str.charAt(i) == 250)
            out10++;// ú
         else if (str.charAt(i) == 224)
            out11++;// à
         else if (str.charAt(i) == 232)
            out12++;// è
         else if (str.charAt(i) == 236)
            out13++;// ì
         else if (str.charAt(i) == 242)
            out14++;// ò
         else if (str.charAt(i) == 249)
            out15++;// ù
         else if (str.charAt(i) == 227)
            out16++;// ã
         else if (str.charAt(i) == 245)
            out17++;// õ
         else if (str.charAt(i) == 226)
            out18++;// â
         else if (str.charAt(i) == 234)
            out19++;// ê
         else if (str.charAt(i) == 238)
            out20++;// ô
         else if (str.charAt(i) == 244)
            out21++;// î
         else if (str.charAt(i) == 251)
            out22++;// û
				
		}
		
		 MyIO.println("a(" + out01 + ") e(" + out02 + ") i(" + out03 + ") o(" + out04 + ") u(" + out05 + ") á("
            + out06
            + ") é(" + out07 + ") í(" + out08 + ") ó(" + out09 + ") ú(" + out10 + ") à(" + out11 + ") è(" + out12
            + ") ì(" + out13 + ") ò(" + out14 + ") ù(" + out15 + ") ã(" + out16 + ") õ(" + out17 + ") â(" + out18
            + ") ê(" + out19 + ") î(" + out20 + ") ô(" + out21 + ") û(" + out22 + ") consoante(" + out23 + ") <br>("
            + out24 + ") <table>(" + out25 + ") " + nome);
		
	}



public static String leitor(String endereco) {  // le o endereço e  transforma em uma string
	StringBuffer resp = new StringBuffer();
	try {
		URL obj = new URL(endereco);
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();

		// MC)todo de requisiC'C#o
		con.setRequestMethod("GET");

		// CC3digo de resposta da conexC#o
		int responseCode = con.getResponseCode();

		// Se a conexC#o foi bem-sucedida (cC3digo 200)
		if (responseCode == HttpURLConnection.HTTP_OK) {
			BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
			String inputLine;

			while ((inputLine = in.readLine()) != null) {
				resp.append(inputLine);
			}

			// Fecha os buffers
			in.close();

		} else {
			System.out.println("Erro na conexC#o: " + responseCode);
		}

	} catch (Exception e) {
		e.printStackTrace();
	}

	return resp.toString();
}


public static void main(String[] args) {

    boolean isfim = false;
    do{
	String nomeSite = MyIO.readLine();
	
	if(nomeSite.equalsIgnoreCase("FIM")){
	    isfim = true;
	    break;
	}
	
	String url = MyIO.readLine(); // le o caminho do site
	String StringUrl = leitor(url);

	contador(nomeSite, StringUrl, StringUrl.length());
	
	}while(isfim != true);



}


}








