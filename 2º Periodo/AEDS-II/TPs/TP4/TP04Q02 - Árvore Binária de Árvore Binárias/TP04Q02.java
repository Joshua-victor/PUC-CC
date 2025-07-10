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

    public int getReleaseYear() {
        return release_year;
    }
}

class No2 {
    Show elemento;
    No2 esq, dir;

    public No2(Show s) {
        this.elemento = s;
        this.esq = this.dir = null;
    }
}
class No {
    int chave;
    No esq, dir;
    No2 outros;

    public No(int chave) {
        this.chave = chave;
        this.esq = this.dir = null;
        this.outros = null;
    }
}

class GlobalVariables {
    public static int comparacoes = 0;
    public static int movimentacoes = 0;
}
class ArvoreBinaria {
    private No raiz;

    public ArvoreBinaria() {
        raiz = null;

        try {
            inserirRaiz(7);
            inserirRaiz(3);
            inserirRaiz(11);
            inserirRaiz(1);
            inserirRaiz(5);
            inserirRaiz(9);
            inserirRaiz(13);
            inserirRaiz(0);
            inserirRaiz(2);
            inserirRaiz(4);
            inserirRaiz(6);
            inserirRaiz(8);
            inserirRaiz(10);
            inserirRaiz(12);
            inserirRaiz(14);
        } catch (Exception e) {
            System.err.println("Erro ao configurar árvore principal: " + e.getMessage());
        }
    }

    private void inserirRaiz(int x) throws Exception {
        raiz = inserirRaiz(x, raiz);
    }

    private No inserirRaiz(int x, No i) throws Exception {
        if (i == null) {
            i = new No(x);
        } else if (x < i.chave) {
            GlobalVariables.comparacoes++;
            i.esq = inserirRaiz(x, i.esq);
        } else if (x > i.chave) {
            GlobalVariables.comparacoes++;
            i.dir = inserirRaiz(x, i.dir);
        } else {
            throw new Exception("Erro ao inserir raiz duplicada");
        }
        return i;
    }

    public void inserir(Show s) throws Exception {
        int chave = s.getReleaseYear() % 15;
        inserir(s, raiz, chave);
    }

    private void inserir(Show s, No i, int chave) throws Exception {
        if (i == null) {
            throw new Exception("Erro: chave não encontrada na árvore principal.");
        } else if (chave < i.chave) {
            GlobalVariables.comparacoes++;
            inserir(s, i.esq, chave);
        } else if (chave > i.chave) {
            GlobalVariables.comparacoes++;
            inserir(s, i.dir, chave);
        } else {
            i.outros = inserirSub(s, i.outros);
        }
    }

    private No2 inserirSub(Show s, No2 i) throws Exception {
        if (i == null) {
            i = new No2(s);
        } else if (s.getTitle().compareTo(i.elemento.getTitle()) < 0) {
            GlobalVariables.comparacoes++;
            i.esq = inserirSub(s, i.esq);
        } else if (s.getTitle().compareTo(i.elemento.getTitle()) > 0) {
            GlobalVariables.comparacoes++;
            i.dir = inserirSub(s, i.dir);
        } else {
            throw new Exception("Erro ao inserir: título duplicado");
        }
        return i;
    }

    public boolean pesquisar(String title) {
        System.out.print("raiz ");
        return pesquisar(title, raiz);
    }

    private boolean pesquisar(String title, No i) {
        boolean resp = false;
        if (i != null) {
            resp = pesquisarSub(title, i.outros);
            if (!resp) {
                System.out.print("ESQ ");
                resp = pesquisar(title, i.esq);
            }
            if (!resp) {
                System.out.print("DIR ");
                resp = pesquisar(title, i.dir);
            }
        }
        return resp;
    }

    private boolean pesquisarSub(String title, No2 i) {
        boolean resp;
        if (i == null) {
            resp = false;
        } else if (title.equals(i.elemento.getTitle())) {
            GlobalVariables.comparacoes++;
            resp = true;
        } else if (title.compareTo(i.elemento.getTitle()) < 0) {
            GlobalVariables.comparacoes++;
            System.out.print("esq ");
            resp = pesquisarSub(title, i.esq);
        } else {
            System.out.print("dir ");
            resp = pesquisarSub(title, i.dir);
        }
        return resp;
    }
}

public class TP04Q02 {
    public static void saveExecutionFile(String filename, int comparacoes, int movimentacoes, double tempo) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("789339" + "\t" + tempo + "ms" + "\t" + comparacoes);
        } catch (IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }

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
        saveExecutionFile("789339_arvoreBinaria.txt", GlobalVariables.comparacoes, GlobalVariables.movimentacoes, tempo);
    }
}
