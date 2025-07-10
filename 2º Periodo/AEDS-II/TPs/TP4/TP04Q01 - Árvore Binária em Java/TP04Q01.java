import java.io.*;
import java.util.*;

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
            System.out.println("erro" + e.getMessage());
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

class No {
    Show elemento;
    No esq, dir;

    public No(Show s) {
        this.elemento = s;
        this.esq = this.dir = null;
    }
}

class ArvoreBinaria {
    private No raiz;
    private int comparacoes;

    public int getComparacoes() {
        return comparacoes;
    }

    public void inserir(Show s) throws Exception {
        raiz = inserir(s, raiz);
    }

    private No inserir(Show s, No i) throws Exception {
        if (i == null) {
            return new No(s);
        }
        comparacoes++;
        int cmp = s.getTitle().compareTo(i.elemento.getTitle());
        if (cmp < 0) i.esq = inserir(s, i.esq);
        else if (cmp > 0) i.dir = inserir(s, i.dir);
        return i;
    }

    public boolean pesquisar(String title) {
        System.out.print("=>raiz ");
        return pesquisar(title, raiz);
    }

    private boolean pesquisar(String title, No i) {
        boolean resp;
        if (i == null) {
            resp = false;
        } else {
            comparacoes++;
            int cmp = title.compareTo(i.elemento.getTitle());
            if (cmp == 0) {
                resp = true;
            } else if (cmp < 0) {
                System.out.print("esq ");
                resp = pesquisar(title, i.esq);
            } else {
                System.out.print("dir ");
                resp = pesquisar(title, i.dir);
            }
        }
        return resp;
    }
}

public class TP04Q01 {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        ArvoreBinaria arvore = new ArvoreBinaria();
        long inicio = System.nanoTime();

        while (sc.hasNextLine()) {
            String linha = sc.nextLine();
            if (linha.equals("FIM")) break;
            Show s = new Show();
            s.ler(linha);
            try {
                arvore.inserir(s);
            } catch (Exception ignored) {}
        }

        while (sc.hasNextLine()) {
            String nome = sc.nextLine();
            if (nome.equals("FIM")) break;
            boolean achou = arvore.pesquisar(nome);
            System.out.println(achou ? "SIM" : "NAO");
        }

        long fim = System.nanoTime();
        double tempo = (fim - inicio) / 1e6; 

     

        sc.close();
    }
}
