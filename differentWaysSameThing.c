#include <stdio.h>
#include <uncertain.h>



int
main(int argc, char *  argv[])
{
	double	a, b, c, d, e;
    
    double sampA[]={11.132, 14.32, 10.98, 22.3, 16.75,13.55,17.11};
    double sampB[]={14.0, 10.0, 12.4, 15.6, 17.9, 13.5};

    a=libUncertainDoubleDistFromSamples(sampA, sizeof(sampA)/sizeof(double));

    b=libUncertainDoubleDistFromSamples(sampB, sizeof(sampB)/sizeof(double));


    printf("a is %lf,  b is %lf\n",a, b);
    printf("Var a is %lf,  Var b is %lf\n",libUncertainDoubleNthMoment(a,2), libUncertainDoubleNthMoment(b,2));

    printf("\nCalculating a^2/(a+b) in 3 different ways.\n\n");

    c=(a/(b+a))*a;
    d=(a*a)/(a+b); 
    e=a/(1.0+b/a);

    printf("c = %lf\t",c); 
	printf("Mean c = %lf\t", libUncertainDoubleNthMoment(c,1));
    printf("Var c = %lf\n", libUncertainDoubleNthMoment(c,2)); 

    printf("d = %lf\t",d); 
	printf("Mean d = %lf\t", libUncertainDoubleNthMoment(d,1));
    printf("Var d = %lf\n", libUncertainDoubleNthMoment(d,2));

    printf("e = %lf\t",e); 
	printf("Mean e = %lf\t", libUncertainDoubleNthMoment(e,1));
    printf("Var e = %lf\n", libUncertainDoubleNthMoment(e,2));

 
	return 0;
}

