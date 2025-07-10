import java.io.*;
import java.util.*;

class Celula { // classe Celula
    public Show elemento;
    public Celula prox;
    public Celula ant;

    public Celula() {
        this(null);
    }

    public Celula(Show elemento) {
        this.elemento = elemento;
        this.prox = null;
        this.ant = null;
    }
}

class Show { // classe show
    private String show_ID;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private String date_added;
    private int release_year;
    private String rating;
    private String duration;
    private String[] listed_IN;

    public Show() {
        this.show_ID = "NaN";
        this.type = "NaN";
        this.title = "NaN";
        this.director = "NaN";
        this.cast = new String[]{"NaN"};
        this.country = "NaN";
        this.date_added = "NaN";
        this.release_year = 0;
        this.rating = "NaN";
        this.duration = "NaN";
        this.listed_IN = new String[]{"NaN"};
    }

    public void imprimir(boolean destacar, int tam) {
        String tituloFormatado = destacar ? title + " (R)" : title;
        System.out.println("[" + tam + "] " + "=> " + show_ID + " ## " + tituloFormatado + " ## " + type + " ## " + director +
                " ## [" + String.join(", ", cast) + "] ## " + country + " ## " + date_added + " ## " +
                release_year + " ## " + rating + " ## " + duration + " ## [" + String.join(", ", listed_IN) + "]"+" ##");
    }

    public void imprimir(int tam) {
        imprimir(false, tam);
    }


    public void ler(String id) {
        try (BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"))) {
            String linha;
            br.readLine(); // Cabeçalho
            while ((linha = br.readLine()) != null) {
                String[] campos = dividirCSV(linha);
                if (campos.length < 11) continue;

                if (campos[0].equals(id)) {
                    this.show_ID = campos[0].isEmpty() ? "NaN" : campos[0];
                    this.type = campos[1].isEmpty() ? "NaN" : campos[1];
                    this.title = campos[2].isEmpty() ? "NaN" : campos[2];
                    this.director = campos[3].isEmpty() ? "NaN" : campos[3];

                    if (campos[4].isEmpty()) {
                        this.cast = new String[]{"NaN"};
                    } else {
                        this.cast = campos[4].split(", ");
                        Arrays.sort(this.cast);
                    }

                    this.country = campos[5].isEmpty() ? "NaN" : campos[5];
                    this.date_added = campos[6].isEmpty() ? "NaN" : campos[6];
                    this.release_year = campos[7].isEmpty() ? 0 : Integer.parseInt(campos[7]);
                    this.rating = campos[8].isEmpty() ? "NaN" : campos[8];
                    this.duration = campos[9].isEmpty() ? "NaN" : campos[9];
                    this.listed_IN = campos[10].isEmpty() ? new String[]{"NaN"} : campos[10].split(", ");
                    break;
                }
            }
        } catch (Exception e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
        }
    }

    private String[] dividirCSV(String linha) {
        List<String> resultado = new ArrayList<>();
        boolean dentroDeAspas = false;
        StringBuilder campo = new StringBuilder();

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '"') {
                dentroDeAspas = !dentroDeAspas;
            } else if (c == ',' && !dentroDeAspas) {
                resultado.add(campo.toString().replaceAll("^\"|\"$", ""));
                campo.setLength(0);
            } else {
                campo.append(c);
            }
        }
        resultado.add(campo.toString().replaceAll("^\"|\"$", ""));
        return resultado.toArray(new String[0]);
    }

    public String getTitle() {
        return title;
    }
}


class Pilha { // classe Pilha
    private Celula primeiro;
    private Celula ultimo;

    public Pilha() {
        primeiro = new Celula();
        ultimo = primeiro;
    }

    public void inserirFim(Show x) {
        
        ultimo.prox = new Celula(x);
        ultimo.prox.ant = ultimo;
        ultimo = ultimo.prox;
    }

    public Show removerFim()  {
       
        Show elemento = ultimo.elemento;
        ultimo = ultimo.ant;
        ultimo.prox = null;
        return elemento;
    }


    public int tamanho() {
        int count = 0;
        for (Celula i = primeiro.prox; i != null; i = i.prox) count++;
        return count;
    }

public void mostrar(int tam) {
    for (Celula i = ultimo; i != primeiro; i = i.ant) {
        i.elemento.imprimir(tam);
        tam--;
    }
}

}


public class TP03Q09 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Pilha pilha = new Pilha();

        
        while (sc.hasNextLine()) {
            String entrada = sc.nextLine();
            if (entrada.equals("FIM")) break; // leitura de ids enquanto != de FIM

            Show s = new Show(); // cria um objeto show para colocar id, diretor, cast...
            s.ler(entrada);
            pilha.inserirFim(s);
        }

        
         int quant = 0;
        quant = sc.nextInt();
        sc.nextLine();
        
        for(int i = 0; i < quant; i++){
            String linha = sc.nextLine();
            if (linha.isEmpty()) continue;

              if (linha.startsWith("I")) {
                String id = linha.split(" ")[1];
                Show s = new Show();
                s.ler(id);
                pilha.inserirFim(s);

            } else if (linha.equals("R")) {
                Show removido = pilha.removerFim();
                System.out.println("(R) " + removido.getTitle());

            } 
        }

        // Mostra pilha final
        int tam = pilha.tamanho();
        pilha.mostrar(tam - 1);
        sc.close();
    }
}
