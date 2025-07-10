int main ()
 {
  int x;
  int y;
  int *ponteiro1 = &x;
  int *ponteiro2 = &y;
  int  soma = 0;


  printf("\n digite o primeiro numero:");
  scanf("%i" , &x);
   printf("digite o segundo numero:");
  scanf("%i" , &y);




soma = *ponteiro1 + *ponteiro2;
printf("\n o resultado e: %i" , soma);

