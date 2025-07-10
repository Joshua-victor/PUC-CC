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
            String linha = br.readLine(); // pular cabeçalho
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

class HashReserva {
    private Show[] tabela;
    private int tamHash = 21;
    private int tamReserva = 9;
    private int posReserva = 21;
    private int comparacoes = 0;

    public HashReserva() {
        tabela = new Show[30];
    }

    public int hash(String title) {
        int soma = 0;
        for (char c : title.toCharArray()) {
            soma += c;
        }
        return soma % tamHash;
    }

    public boolean inserir(Show s) {
        int pos = hash(s.getTitle());
        if (tabela[pos] == null) {
            tabela[pos] = s;
            return true;
        } else {
            while (posReserva < tabela.length) {
                if (tabela[posReserva] == null) {
                    tabela[posReserva++] = s;
                    return true;
                } else {
                    posReserva++;
                }
            }
        }
        return false;
    }

    public int pesquisar(String title) {
        int pos = hash(title);
        comparacoes++;
        if (tabela[pos] != null && tabela[pos].getTitle().equals(title)) {
            return pos;
        } else {
            for (int i = 21; i < tabela.length; i++) {
                comparacoes++;
                if (tabela[i] != null && tabela[i].getTitle().equals(title)) {
                    return i;
                }
            }
        }
        return -1;
    }

    public int getComparacoes() {
        return comparacoes;
    }
}

public class TP04Q05 {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        HashReserva hash = new HashReserva();
        long inicio = System.nanoTime();

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
            int pos = hash.pesquisar(nome);
            if (pos != -1)
                System.out.println(" (Posicao: " + pos + ") SIM");
            else
                System.out.println(" (Posicao: " + hash.hash(nome) + ") NAO");
        }

        long fim = System.nanoTime();
        double tempo = (fim - inicio) / 1e6;

        FileWriter fw = new FileWriter("789339_hashReserva.txt");
        fw.write("789339\t" + tempo + "ms\t" + hash.getComparacoes());
        fw.close();

        sc.close();
    }
}
