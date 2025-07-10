import java.io.*;
import java.text.*;
import java.util.*;

public class tp04q4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<Show> shows = Show.lerArquivo("/tmp/disneyplus.csv");

        Map<String, Show> mapaShows = new HashMap<>();
        for (Show s : shows) {
            mapaShows.put(s.getShow_id(), s);
        }

        Arvore a = new Arvore();

        long inicio = System.currentTimeMillis();

        while (sc.hasNextLine()) {
            String linha = sc.nextLine().trim();
            if (linha.equalsIgnoreCase("FIM")) {
                break;
            }

            Show s = mapaShows.get(linha);
            if (s != null) {
                String nome = s.getTitle();
                a.inserir(nome);

            }
        }

        while (sc.hasNextLine()) {
            String linha = sc.nextLine().trim();
            if (linha.equalsIgnoreCase("FIM")) {
                break;
            }

            System.out.print("=>raiz  ");
            a.buscar(linha);

        }

        long fim = System.currentTimeMillis();
        long tempoExecucao = fim - inicio;

        try {
            PrintWriter writer = new PrintWriter("matrícula_avinegra.txt");
            writer.println("789339\t" + tempoExecucao + "\t" + a.getComparacoes());
            writer.close();
        } catch (IOException e) {
            System.err.println("Erro ao escrever o arquivo de log.");
        }

        sc.close();
    }
}

class No {
    public boolean cor;
    public String elemento;
    public No esq, dir;

    public No() {
        this(null);
    }

    public No(String elemento) {
        this(elemento, false, null, null);
    }

    public No(String elemento, boolean cor) {
        this(elemento, cor, null, null);
    }

    public No(String elemento, boolean cor, No esq, No dir) {
        this.cor = cor;
        this.elemento = elemento;
        this.esq = esq;
        this.dir = dir;
    }
}

class Arvore {
    private No raiz;
    private int comparacoes = 0;

    public Arvore() {
        raiz = null;
    }

    public void buscar(String titulo) {
        buscar(titulo, raiz);
    }

    private void buscar(String elemento, No no) {
        if (no == null) {
            System.out.println("NAO");
            return;
        }

        comparacoes++;
        int cmp = elemento.compareTo(no.elemento);
        if (cmp == 0) {
            System.out.println("SIM");
        } else if (cmp < 0) {
            System.out.print("esq ");
            buscar(elemento, no.esq);
        } else {
            System.out.print("dir ");
            buscar(elemento, no.dir);
        }
    }

    public void inserir(String elemento) {
        if (raiz == null) {
            raiz = new No(elemento);
        } else if (raiz.esq == null && raiz.dir == null) {
            comparacoes++;
            if (elemento.compareTo(raiz.elemento) < 0) {
                raiz.esq = new No(elemento);
            } else {
                raiz.dir = new No(elemento);
            }
        } else if (raiz.esq == null) {
            comparacoes++;
            if (elemento.compareTo(raiz.elemento) < 0) {
                raiz.esq = new No(elemento);
            } else {
                comparacoes++;
                if (elemento.compareTo(raiz.dir.elemento) < 0) {
                    raiz.esq = new No(raiz.elemento);
                    raiz.elemento = elemento;
                } else {
                    raiz.esq = new No(raiz.elemento);
                    raiz.elemento = raiz.dir.elemento;
                    raiz.dir.elemento = elemento;
                }
            }
            raiz.esq.cor = raiz.dir.cor = false;
        } else if (raiz.dir == null) {
            comparacoes++;
            if (elemento.compareTo(raiz.elemento) > 0) {
                raiz.dir = new No(elemento);
            } else {
                comparacoes++;
                if (elemento.compareTo(raiz.esq.elemento) > 0) {
                    raiz.dir = new No(raiz.elemento);
                    raiz.elemento = elemento;
                } else {
                    raiz.dir = new No(raiz.elemento);
                    raiz.elemento = raiz.esq.elemento;
                    raiz.esq.elemento = elemento;
                }
            }
            raiz.esq.cor = raiz.dir.cor = false;
        } else {
            inserir(elemento, null, null, null, raiz);
        }
        raiz.cor = false;
    }

    private void balancear(No bisavo, No avo, No pai, No i) {
        if (pai.cor == true) {
            comparacoes++;
            if (pai.elemento.compareTo(avo.elemento) > 0) {
                comparacoes++;
                if (i.elemento.compareTo(pai.elemento) > 0) {
                    avo = rotacaoEsq(avo);
                } else {
                    avo = rotacaoDirEsq(avo);
                }
            } else {
                comparacoes++;
                if (i.elemento.compareTo(pai.elemento) < 0) {
                    avo = rotacaoDir(avo);
                } else {
                    avo = rotacaoEsqDir(avo);
                }
            }
            if (bisavo == null) {
                raiz = avo;
            } else {
                comparacoes++;
                if (avo.elemento.compareTo(bisavo.elemento) < 0) {
                    bisavo.esq = avo;
                } else {
                    bisavo.dir = avo;
                }
            }
            avo.cor = false;
            avo.esq.cor = avo.dir.cor = true;
        }
    }

    private void inserir(String elemento, No bisavo, No avo, No pai, No i) {
        if (i == null) {
            comparacoes++;
            if (elemento.compareTo(pai.elemento) < 0) {
                i = pai.esq = new No(elemento, true);
            } else {
                i = pai.dir = new No(elemento, true);
            }
            if (pai.cor == true) {
                balancear(bisavo, avo, pai, i);
            }
        } else {
            if (i.esq != null && i.dir != null && i.esq.cor && i.dir.cor) {
                i.cor = true;
                i.esq.cor = i.dir.cor = false;
                if (i == raiz) {
                    i.cor = false;
                } else if (pai.cor == true) {
                    balancear(bisavo, avo, pai, i);
                }
            }

            comparacoes++;
            int cmp = elemento.compareTo(i.elemento);
            if (cmp < 0) {
                inserir(elemento, avo, pai, i, i.esq);
            } else if (cmp > 0) {
                inserir(elemento, avo, pai, i, i.dir);
            } else {
                System.out.println("Erro inserir (elemento repetido)!");
            }
        }
    }

    private No rotacaoDir(No no) {
        No noEsq = no.esq;
        No noEsqDir = noEsq.dir;

        noEsq.dir = no;
        no.esq = noEsqDir;

        return noEsq;
    }

    private No rotacaoEsq(No no) {
        No noDir = no.dir;
        No noDirEsq = noDir.esq;

        noDir.esq = no;
        no.dir = noDirEsq;

        return noDir;
    }

    private No rotacaoDirEsq(No no) {
        no.dir = rotacaoDir(no.dir);
        return rotacaoEsq(no);
    }

    private No rotacaoEsqDir(No no) {
        no.esq = rotacaoEsq(no.esq);
        return rotacaoDir(no);
    }

    public int getComparacoes() {
        return comparacoes;
    }
}

class Show implements Cloneable {
    private String show_id;
    private String type;
    private String title;
    private String director;
    private List<String> cast;
    private String country;
    private Date date_added;
    private int release_year;
    private String rating;
    private String duration;
    private List<String> listed_in;

    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);

    public Show() {
        this.show_id = "NaN";
        this.type = "NaN";
        this.title = "NaN";
        this.director = "NaN";
        this.cast = new ArrayList<>();
        this.country = "NaN";
        this.date_added = null;
        this.release_year = 0;
        this.rating = "NaN";
        this.duration = "NaN";
        this.listed_in = new ArrayList<>();
    }

    public Show(String linha) {
        ler(linha);
    }

    public void ler(String linha) {
        List<String> campos = parseCSV(linha);

        this.show_id = (campos.size() > 0 && !campos.get(0).trim().isEmpty()) ? campos.get(0) : "NaN";
        this.type = (campos.size() > 1 && !campos.get(1).trim().isEmpty()) ? campos.get(1) : "NaN";
        this.title = (campos.size() > 2 && !campos.get(2).trim().isEmpty()) ? campos.get(2) : "NaN";
        this.director = (campos.size() > 3 && !campos.get(3).trim().isEmpty()) ? campos.get(3) : "NaN";

        if (campos.size() > 4 && !campos.get(4).trim().isEmpty()) {
            this.cast = Arrays.asList(campos.get(4).split(", "));
        } else {
            this.cast = Arrays.asList("NaN");
        }

        this.country = (campos.size() > 5 && !campos.get(5).trim().isEmpty()) ? campos.get(5) : "NaN";

        try {
            this.date_added = (campos.size() > 6 && !campos.get(6).trim().isEmpty()) ? dateFormat.parse(campos.get(6))
                    : null;
        } catch (ParseException e) {
            this.date_added = null;
        }

        this.release_year = (campos.size() > 7 && !campos.get(7).trim().isEmpty())
                ? Integer.parseInt(campos.get(7).trim())
                : 0;

        this.rating = (campos.size() > 8 && !campos.get(8).trim().isEmpty()) ? campos.get(8) : "NaN";
        this.duration = (campos.size() > 9 && !campos.get(9).trim().isEmpty()) ? campos.get(9) : "NaN";

        if (campos.size() > 10 && !campos.get(10).trim().isEmpty()) {
            this.listed_in = Arrays.asList(campos.get(10).split(", "));
        } else {
            this.listed_in = Arrays.asList("NaN");
        }
    }

    private List<String> parseCSV(String linha) {
        List<String> campos = new ArrayList<>();
        boolean dentroDeAspas = false;
        StringBuilder campoAtual = new StringBuilder();

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);

            if (c == '\"') {
                dentroDeAspas = !dentroDeAspas;
            } else if (c == ',' && !dentroDeAspas) {
                campos.add(campoAtual.toString().trim().replaceAll("^\"|\"$", ""));
                campoAtual.setLength(0);
            } else {
                campoAtual.append(c);
            }
        }

        campos.add(campoAtual.toString().trim().replaceAll("^\"|\"$", ""));
        return campos;
    }

    public void imprimir() {
        String dataFormatada = (date_added != null) ? dateFormat.format(date_added) : "NaN";

        List<String> castOrdenado = new ArrayList<>(cast);
        Collections.sort(castOrdenado);

        List<String> listedInOrdenado = new ArrayList<>(listed_in);
        Collections.sort(listedInOrdenado);

        System.out.print("=> ");
        System.out.print(show_id + " ## ");
        System.out.print(title + " ## ");
        System.out.print(type + " ## ");
        System.out.print(director + " ## ");
        System.out.print("[" + String.join(", ", castOrdenado) + "] ## ");
        System.out.print(country + " ## ");
        System.out.print(dataFormatada + " ## ");
        System.out.print(release_year + " ## ");
        System.out.print(rating + " ## ");
        System.out.print(duration + " ## ");
        System.out.println("[" + String.join(", ", listedInOrdenado) + "] ## ");
    }

    public Show clone() {
        try {
            Show clone = (Show) super.clone();
            clone.cast = new ArrayList<>(this.cast);
            clone.listed_in = new ArrayList<>(this.listed_in);
            return clone;
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }

    public static List<Show> lerArquivo(String filePath) {
        List<Show> shows = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String linha;
            br.readLine(); // Pular cabeçalho
            while ((linha = br.readLine()) != null) {
                shows.add(new Show(linha));
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }
        return shows;
    }

    public String getShow_id() {
        return show_id;
    }

    public void setShow_id(String show_id) {
        this.show_id = show_id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDirector() {
        return director;
    }

    public void setDirector(String director) {
        this.director = director;
    }

    public List<String> getCast() {
        return cast;
    }

    public void setCast(List<String> cast) {
        this.cast = cast;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public Date getDate_added() {
        return date_added;
    }

    public void setDate_added(Date date_added) {
        this.date_added = date_added;
    }

    public int getRelease_year() {
        return release_year;
    }

    public void setRelease_year(int release_year) {
        this.release_year = release_year;
    }

    public String getRating() {
        return rating;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public List<String> getListed_in() {
        return listed_in;
    }

    public void setListed_in(List<String> listed_in) {
        this.listed_in = listed_in;
    }
}
