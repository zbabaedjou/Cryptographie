#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main()
{
    mpz_t n, res, test;
    int a;
char tab[]="0194203178792192493518218104227241265615022269116179186881151218910141561347834352382351127423207208141221801041451662011611715357198228154175231242898572199762912718421076209921785976208163";
mpz_init(n);
a=mpz_set_str(n,tab,10);

mpz_init(res);
mpz_set_ui(res,0);

mpz_init(test);
mpz_set_ui(test,0);

for(int i=3; i<=mpz_get_ui(n); i++){

     a=mpz_divisible_ui_p(n,i);
    printf("Hello world!  %d \n",i);
    mpz_set_ui(test,i);

    if(a!=0 && mpz_probab_prime_p(test,49)==2)
        mpz_out_str(stdout,10,res);

}

    printf("Hello world!\n");
    return 0;
}
