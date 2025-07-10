import java.io.*;
import java.util.*;

class Celula { // classe Celula
    public Show elemento;
    public Celula prox;

    public Celula() {
        this(null);
    }

    public Celula(Show elemento) {
        this.elemento = elemento;
        this.prox = null;
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

    public void imprimir(boolean destacar) {
        String tituloFormatado = destacar ? title + " (R)" : title;
        System.out.println("=> " + show_ID + " ## " + tituloFormatado + " ## " + type + " ## " + director +
                " ## [" + String.join(", ", cast) + "] ## " + country + " ## " + date_added + " ## " +
                release_year + " ## " + rating + " ## " + duration + " ## [" + String.join(", ", listed_IN) + "]"+" ##");
    }

    public void imprimir() {
        imprimir(false);
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


class Lista { // classe lista
    private Celula primeiro;
    private Celula ultimo;

    public Lista() {
        primeiro = new Celula();
        ultimo = primeiro;
    }

    public void inserirInicio(Show x) {
        Celula tmp = new Celula(x);
        tmp.prox = primeiro.prox;
        primeiro.prox = tmp;
        if (tmp.prox == null) {
            ultimo = tmp;
        }
    }

    public void inserirFim(Show x) {
        Celula tmp = new Celula(x);
        ultimo.prox = tmp;
        ultimo = tmp;
    }

    public void inserir(Show x, int pos) {
        int tamanho = tamanho();
        if (pos < 0 || pos > tamanho) {
            
            System.out.print("Pos Invalida!");
            return;
        }

        if (pos == 0) inserirInicio(x);
        else if (pos == tamanho) inserirFim(x);
        else {
            Celula i = primeiro;
            for (int j = 0; j < pos; j++) i = i.prox;
            Celula tmp = new Celula(x);
            tmp.prox = i.prox;
            i.prox = tmp;
        }
    }

    public Show removerInicio() {
       
        Celula tmp = primeiro.prox;
        primeiro.prox = tmp.prox;
        if (primeiro.prox == null) ultimo = primeiro;
        return tmp.elemento;
    }

    public Show removerFim()  {
       
        Celula i = primeiro;
        while (i.prox != ultimo) i = i.prox;
        Show elemento = ultimo.elemento;
        ultimo = i;
        i.prox = null;
        return elemento;
    }

    public Show remover(int pos)  {
        int tamanho = tamanho();
      
        if (pos == 0) return removerInicio();
        else if (pos == tamanho - 1) return removerFim();
        else {
            Celula i = primeiro;
            for (int j = 0; j < pos; j++) i = i.prox;
            Celula tmp = i.prox;
            i.prox = tmp.prox;
            return tmp.elemento;
        }
    }

    public int tamanho() {
        int count = 0;
        for (Celula i = primeiro.prox; i != null; i = i.prox) count++;
        return count;
    }

public void mostrar() {
    for (Celula i = primeiro.prox; i != null; i = i.prox) {
        i.elemento.imprimir();
    }
}
}


public class TP03Q01 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Lista lista = new Lista();

        
        while (sc.hasNextLine()) {
            String entrada = sc.nextLine();
            if (entrada.equals("FIM")) break; // leitura de ids enquanto != de FIM

            Show s = new Show(); // cria um objeto show para colocar id, diretor, cast...
            s.ler(entrada);
            lista.inserirFim(s);
        }

        
         int quant = 0;
        quant = sc.nextInt();
        sc.nextLine();
        
        for(int i = 0; i < quant; i++){
            String linha = sc.nextLine();
            if (linha.isEmpty()) continue;

            if (linha.startsWith("II ")) {
                String id = linha.split(" ")[1];
                Show s = new Show();
                s.ler(id);
                lista.inserirInicio(s);

            } else if (linha.startsWith("IF ")) {
                String id = linha.split(" ")[1];
                Show s = new Show();
                s.ler(id);
                lista.inserirFim(s);

            } else if (linha.startsWith("I* ")) {
                String[] partes = linha.split(" ");
                int pos = Integer.parseInt(partes[1]);
                String id = partes[2];
                Show s = new Show();
                s.ler(id);
                lista.inserir(s, pos);

            } else if (linha.equals("RI")) {
                Show removido = lista.removerInicio();
                System.out.println("(R) " + removido.getTitle());

            } else if (linha.equals("RF")) {
                Show removido = lista.removerFim();
                System.out.println("(R) " + removido.getTitle());

            } else if (linha.startsWith("R* ")) {
                int pos = Integer.parseInt(linha.split(" ")[1]);
                Show removido = lista.remover(pos);
                System.out.println("(R) " + removido.getTitle());
            }
        }

        // Mostra lista final
        lista.mostrar();
        sc.close();
    }
}
