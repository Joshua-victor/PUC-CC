time da turma

int main()
{

printf("times da turma\n");

int alunos;
int cruzeiro = 0;
int atletico = 0;
char  time ;
bool erro;
char decisao;
do{
do{
printf("digite a quantidade de alunos");
scanf(" %i", &alunos);
if(alunos < 0 ) puts("numero invalido!");
}while (alunos < 0 );


for (int x = 0 ; x < alunos ; x++ )
{
    do{
    printf(" qual time voce torce?");
    scanf(" %c" , &time);
    time = toupper (time);
    erro = time != 'A' && time != 'C';
    if (erro) puts("resposta invalida");
    }while(erro);

    if(time == 'A') atletico++;
        else cruzeiro++;


}

if (cruzeiro > atletico) printf("cruzeiro e maior\n! %i" , cruzeiro);
    else {

         printf("atletico e maior com %i votos\n" , atletico);
    }



    printf("quer refazer o teste? [S/N]");
    scanf(" %c" , &decisao );
    decisao = toupper (decisao);

}while(decisao != 'N' );



    return 0;
}