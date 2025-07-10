import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;




 class Show {
   
    private String showId;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private String dateAdded;
    private int releaseYear;
    private String rating;
    private String duration;
    private String[] listedIn;
   
   
   
    public Show(){
       
        this.showId = "NaN";
        this.type = "NaN";
        this.title = "NaN";
        this.director = "NaN";
        this.cast = new String[]{"NaN"};
        this.country = "NaN";
        this.dateAdded = "NaN";
        this.releaseYear = 0;
        this.rating = "NaN";
        this.duration = "NaN";
        this.listedIn = new String[]{"NaN"};
       
       
       
    }
   
    // Construtor  (o nome do contrutor deve ser o mesmo da classe) (usados para inicializar os atributos da classe)
    public Show(String showId, String type, String title, String director, String[] cast, String country,
                String dateAdded, int releaseYear, String rating, String duration, String[] listedIn) {
        this.showId = showId;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = cast;
        this.country = country;
        this.dateAdded = dateAdded;
        this.releaseYear = releaseYear;
        this.rating = rating;
        this.duration = duration;
        this.listedIn = listedIn;
    }
   
    //Os getters e setters são métodos que servem para acessar e modificar os atributos de um objeto de forma controlada.)

    // Getters Pegam valores dos atributos
    public String getShowId() {
        return this.showId;
    }
   
    public String getType() {
        return this.type;
    }
   
    public String getTitle() {
        return this.title;
    }
   
    public String getDirector() {
        return this.director;
    }
   
    public String[] getCast() {
        return this.cast;
    }
   
    public String getCountry() {
        return this.country;
    }
   
    public String getDateAdded() {
        return this.dateAdded;
    }
   
    public int getReleaseYear() {
        return this.releaseYear;
    }
   
    public String getRating() {
        return this.rating;
    }
   
    public String getDuration() {
        return this.duration;
    }
   
    public String[] getListedIn() {
        return this.listedIn;
    }
   
   

    // Setters Alteram valores dos atributos
    public void setShowId(String showId) {
        this.showId = showId;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDirector(String director) {
        this.director = director;
    }

    public void setCast(String[] cast) {
        this.cast = cast;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public void setDateAdded(String dateAdded) {
        this.dateAdded = dateAdded;
    }

    public void setReleaseYear(int releaseYear) {
        this.releaseYear = releaseYear;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public void setListedIn(String[] listedIn) {
        this.listedIn = listedIn;
    }
   
    //clone
    public Show clone(){
       
        return new Show(this.showId, this.type, this.title, this.director, this.cast, this.country, this.dateAdded, this.releaseYear, this.rating, this.duration, this.listedIn);
   
    }
   
   
    public void mostrar() {
    // Ordena o casting (elenco) em ordem alfabética antes de exibir
    String[] elencoOrdenado = this.getCast().clone();
    Arrays.sort(elencoOrdenado);

    System.out.println("=> "
        + this.getShowId() + " ## "
        + this.getTitle() + " ## "
        + this.getType() + " ## "
        + this.getDirector() + " ## "
        + Arrays.toString(elencoOrdenado) + " ## "
        + this.getCountry() + " ## "
        + this.getDateAdded() + " ## "
        + this.getReleaseYear() + " ## "
        + this.getRating() + " ## "
        + this.getDuration() + " ## "
        + Arrays.toString(this.getListedIn()) + " ## ");
}

   
    public void ler(String linha){
      // SimpleDateFormat sdf = new SimpleDateFormat("MMMM dd, yyyy");
       // System.out.print("ENTREI");
       
       try{
           
           String[] partes = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1); // split para separar cada atributo mesmo com virgulas dentro de aspas

           this.showId = partes[0]; // alocando em showId a posição 0 de partes
           this.type = partes[1]; // alocando em type a posição 1 de partes
           this.title = partes[2].replaceAll("^\"|\"$", "").replaceAll("\"\"", ""); // alocando em title a posição 2 de partes
           this.director = partes[3].isEmpty() ? "NaN" : partes[3].replaceAll("^\"|\"$", "").replaceAll("\"\"", ""); // if partes[3] vazia this.director = "NaN" else this.director = partes[3]
           this.cast = partes[4].isEmpty() ? new String[] { "NaN" } : partes[4].replace("\"", "").split(",");
           
           for (int i = 0; i < this.cast.length; i++) {
                this.cast[i] = this.cast[i].trim();
            }
           
           this.country = partes[5].isEmpty() ? "NaN" : partes[5].replace("\"", "");
           this.dateAdded = partes[6].isEmpty() ? "NaN" : partes[6].replace("\"", "");
           this.releaseYear = partes[7].isEmpty() ? 0 : Integer.parseInt(partes[7]); //Integer.parseInt usado para trasnformar uma string em Int
           this.rating = partes[8].isEmpty() ? "NaN" : partes[8];// alocando em rating a posição 8 de partes
           this.duration = partes[9].isEmpty() ? "NaN" : partes[9];// alocando em duration a posição 9 de partes
           this.listedIn = partes[10].isEmpty() ? new String[] { "NaN" } : partes[10].replace("\"", "").split(",");
       
            // Remove os espaços extras de cada valor de "listedIn"
           for (int i = 0; i < this.listedIn.length; i++) {
                this.listedIn[i] = this.listedIn[i].trim();
            }
           
       } catch(Exception e){
           
           System.out.println("Erro ao ler a linha" + linha);
       }
    }
}



public class TP02Q13 {
    
    
public static void mergeSort(List<Show> lista, int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        mergeSort(lista, esq, meio);
        mergeSort(lista, meio + 1, dir);
        intercalar(lista, esq, meio, dir);
    }
}

public static void intercalar(List<Show> lista, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    List<Show> left = new ArrayList<>();
    List<Show> right = new ArrayList<>();

    for (int i = 0; i < n1; i++) left.add(lista.get(esq + i));
    for (int j = 0; j < n2; j++) right.add(lista.get(meio + 1 + j));

    int i = 0, j = 0, k = esq;

    while (i < n1 && j < n2) {
        Show s1 = left.get(i);
        Show s2 = right.get(j);
        int d1 = extrairDuracao(s1.getDuration());
        int d2 = extrairDuracao(s2.getDuration());

        int cmp = Integer.compare(d1, d2);
        if (cmp == 0) {
            cmp = s1.getTitle().compareTo(s2.getTitle());
        }

        if (cmp <= 0) {
            lista.set(k++, s1);
            i++;
        } else {
            lista.set(k++, s2);
            j++;
        }
    }

    while (i < n1) lista.set(k++, left.get(i++));
    while (j < n2) lista.set(k++, right.get(j++));
}


public static int extrairDuracao(String duracao) {
    if (duracao == null || duracao.isEmpty()) return 0;
    String[] partes = duracao.split(" ");
    try {
        return Integer.parseInt(partes[0]);
    } catch (NumberFormatException e) {
        return 0;
    }
}


public static void bubbleSort(ArrayList<Show> todosShows) {
    int n = todosShows.size(); // tamanho da lista 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            Show s1 = todosShows.get(j);
            Show s2 = todosShows.get(j + 1);
            // Se os anos forem iguais, comparando os títulos
            if (s1.getDuration() == s2.getDuration() && s1.getTitle().compareTo(s2.getTitle()) > 0) {
                // Troca os shows
                Show temp = todosShows.get(j);
                todosShows.set(j, todosShows.get(j + 1));
                todosShows.set(j + 1, temp);
            }
        }
    }
}

    
    
    public static void main(String[] args) throws IOException {
    Scanner scanner = new Scanner(System.in);
    ArrayList<String> lista = new ArrayList<>();
    ArrayList<Integer> relase = new ArrayList<>();
    HashMap<String, Show> mapaShows = new HashMap<>();
    ArrayList<Show> todosShows = new ArrayList<>();

    while (true) {
        String linha = scanner.nextLine();
        if (linha.equalsIgnoreCase("FIM")) break;
        lista.add(linha);
    }

    BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"));
    String CSV;
    br.readLine(); // pula o cabeçalho

    while ((CSV = br.readLine()) != null) {
        Show s = new Show();
        s.ler(CSV);
        if (lista.contains(s.getShowId())) {
            todosShows.add(s);
            relase.add(s.getReleaseYear());
            mapaShows.put(s.getShowId(), s);
        }
    }

    br.close();

    
    mergeSort(todosShows, 0, todosShows.size() -1);
    bubbleSort(todosShows);
    

    // Exibe os shows ordenados
    for (Show s : todosShows) {
        s.mostrar();
    }
    
    
    
    

  
    
    
    
}
}
