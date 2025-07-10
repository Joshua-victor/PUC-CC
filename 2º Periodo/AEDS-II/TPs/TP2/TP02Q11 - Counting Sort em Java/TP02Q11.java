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



public class TP02Q11 {
    
    
public static void countingsort(ArrayList<Show> todosShows) {
    if (todosShows.isEmpty()) return;

    // Determina o maior e o menor ano para o Counting Sort
    int menorAno = Integer.MAX_VALUE;
    int maiorAno = Integer.MIN_VALUE;

    for (Show show : todosShows) {
        int ano = show.getReleaseYear();
        if (ano < menorAno) menorAno = ano;
        if (ano > maiorAno) maiorAno = ano;
    }

    // Cria a lista de listas para os anos
    int range = maiorAno - menorAno + 1; // Faixa de anos
    List<List<Show>> count = new ArrayList<>(range); // Lista de listas de Shows

    // Inicializa as sublistas
    for (int i = 0; i < range; i++) {
        count.add(new ArrayList<Show>());
    }

    // Coloca os shows nas listas de acordo com o ano de lançamento
    for (Show show : todosShows) {
        int index = show.getReleaseYear() - menorAno;
        count.get(index).add(show);
    }

    // Reordena as listas de shows para ordenar por título em cada grupo de releaseYear
    todosShows.clear();
    for (List<Show> lista : count) {
        lista.sort((s1, s2) -> s1.getTitle().compareTo(s2.getTitle())); // Ordena por título
        todosShows.addAll(lista);
    }
}


public static void bubbleSort(ArrayList<Show> todosShows) {
    int n = todosShows.size(); // tamanho da lista 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            Show s1 = todosShows.get(j);
            Show s2 = todosShows.get(j + 1);
            // Se os anos forem iguais, comparando os títulos
            if (s1.getReleaseYear() == s2.getReleaseYear() && s1.getTitle().compareTo(s2.getTitle()) > 0) {
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

    
    countingsort(todosShows);
    bubbleSort(todosShows);
    

    // Exibe os shows ordenados
    for (Show s : todosShows) {
        s.mostrar();
    }
    
    
    
    

  
    
    
    
}
}
