import java.io.*;
import java.util.*;

class TP {
    private long startTime, endTime;
    private int comp = 0;

    public void startTime() {
        startTime = System.nanoTime();
    }

    public void endTime() {
        endTime = System.nanoTime();
    }

    public double Time() {
        return (endTime - startTime) / 1000000.0;
    }

    public void addComp(int i) {
        this.comp += i;
    }

    public int getComp() {
        return comp;
    }

    public void pesquisaFile(String name) {
        try {
            PrintWriter write = new PrintWriter(new FileWriter(name));
            write.printf("Matrícula: 789339\t");
            write.printf("Tempo de execução: %.3fms\t", Time());
            write.printf("Comparações: %d\n", comp);
            write.close();
        } catch (IOException e) {
            System.out.println("Erro ao escrever no arquivo: " + e.getMessage());
        }
    }
}

class Show {
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

    public void ler(String id) {
        try (BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"))) {
            String linha = br.readLine(); 
            while ((linha = br.readLine()) != null) {
                String[] campos = dividirCSV(linha);
                if (campos[0].equals(id)) {
                    show_ID = campos[0];
                    type = campos[1];
                    title = campos[2];
                    director = campos[3];
                    cast = campos[4].isEmpty() ? new String[]{"NaN"} : campos[4].split(", ");
                    Arrays.sort(cast);
                    country = campos[5];
                    date_added = campos[6];
                    release_year = Integer.parseInt(campos[7].isEmpty() ? "0" : campos[7]);
                    rating = campos[8];
                    duration = campos[9];
                    listed_IN = campos[10].split(", ");
                    break;
                }
            }
        } catch (Exception e) {
            System.out.println("Erro ao ler: " + e.getMessage());
        }
    }

    private String[] dividirCSV(String linha) {
        List<String> campos = new ArrayList<>();
        boolean aspas = false;
        StringBuilder campo = new StringBuilder();
        for (char c : linha.toCharArray()) {
            if (c == '"') aspas = !aspas;
            else if (c == ',' && !aspas) {
                campos.add(campo.toString().replaceAll("^\"|\"$", ""));
                campo.setLength(0);
            } else campo.append(c);
        }
        campos.add(campo.toString().replaceAll("^\"|\"$", ""));
        return campos.toArray(new String[0]);
    }

    public String getTitle() {
        return title;
    }
}

// Lista Simples
class Celula {
    public Show elemento;
    public Celula prox;

    public Celula(Show elemento) {
        this.elemento = elemento;
        this.prox = null;
    }
}

class ListaSimples {
    private Celula primeiro, ultimo;

    public ListaSimples() {
        primeiro = ultimo = null;
    }

    public void inserir(Show s) {
        Celula nova = new Celula(s);
        if (primeiro == null) {
            primeiro = ultimo = nova;
        } else {
            ultimo.prox = nova;
            ultimo = nova;
        }
    }

    public boolean pesquisar(String title, TP tp) {
        Celula tmp = primeiro;
        while (tmp != null) {
            tp.addComp(1);
            if (tmp.elemento.getTitle().equals(title)) {
                return true;
            }
            tmp = tmp.prox;
        }
        return false;
    }
}

class HashIndireta {
    private ListaSimples[] tabela;
    private int tam = 21;

    public HashIndireta() {
        tabela = new ListaSimples[tam];
        for (int i = 0; i < tam; i++) {
            tabela[i] = new ListaSimples();
        }
    }

    public int hash(String title) {
        int soma = 0;
        for (char c : title.toCharArray()) {
            soma += c;
        }
        return soma % tam;
    }

    public void inserir(Show s) {
        int pos = hash(s.getTitle());
        tabela[pos].inserir(s);
    }

    public boolean pesquisar(String title, TP tp) {
        int pos = hash(title);
        return tabela[pos].pesquisar(title, tp);
    }
}

public class TP04Q07 {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        HashIndireta hash = new HashIndireta();
        TP tp = new TP();

        tp.startTime();

        while (sc.hasNextLine()) {
            String id = sc.nextLine();
            if (id.equals("FIM")) break;
            Show s = new Show();
            s.ler(id);
            hash.inserir(s);
        }

        while (sc.hasNextLine()) {
            String nome = sc.nextLine();
            if (nome.equals("FIM")) break;
            boolean achou = hash.pesquisar(nome, tp);
            System.out.print(" (Posicao: " + hash.hash(nome) + ") ");
            System.out.println(achou ? "SIM" : "NAO");
        }

        tp.endTime();
        tp.pesquisaFile("789339_hashIndireta.txt");

        sc.close();
    }
}
