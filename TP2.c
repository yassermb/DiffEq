#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nmax 10
#define y0 0
#define x0 0



double f(double x, double y )
{
   return pow(x,2)*cos(y);
}

double f_euler(double x, double y , double h )
{
   double y_new = y + h * f(x,y);
   return y_new;
}


double f_ordre(double x, double y , double h)
{
    double y_new = y + h * f(x+(h/2.0),y+(h/2.0)*f(x,y));
    return y_new;
}

double f_RK4 (double x, double y , double h)
{
    double y_new = y+h/6.0*(f(x,y)+2*f(x+h/2.0,y+(h/2)*f(x,y))+2.0*f(x+h/2,y+(h/2.0)*f(x+h/2.0,y+(h/2.0)*f(x,y)))+f(x+h,y+h*f(x+h/2,y+(h/2.0)*f(x+h/2.0,y+(h/2.0)*f(x,y)))));
    return y_new;
}



int main()
{
    double h = 1.0/nmax;
    int i;
    double x = x0;
    double y = y0;
    double Eh;
    double yana;
    int v=10;
    int j;
    int k;
    double x_new = x;
    double yana_new;
    FILE * fhandler1 = fopen("xy_euler_ordre","w");
    FILE * fhandler2 = fopen("xy_ana_ordre","w");
    FILE * fhandler3 = fopen("err_euler_ordre","w");

    for (i=0; i<nmax+1; i++)
    {
        //y=f_euler(x,y,h);
        y=f_ordre(x,y,h);
        //y=f_RK4(x,y,h);
        x=i*h;
        printf("%lf\t%lf\n",x,y);
        fprintf(fhandler1,"%lf\t%lf\n",x,y);
        yana = 2 * atan(exp(pow(x,3)/3))-(acos(-1.0)/2);  
        fprintf(fhandler2,"%lf\t%lf\n",x,yana);

        if(i==nmax)
        {
            printf("x: %lf\n",x);
            printf("y: %lf\n",y);
            printf("yana: %lf\n",yana);
            Eh= fabs(y-yana);
            printf("l'erreur est %lf",Eh);
        }
        
    }

    

    for(j=1; j<6; j++ )
    {
    
        h= 1.0/v;
        x_new = x0;
        y=y0;
        for (k=0; k<v+1; k++)
        {
            //y=f_euler(x_new,y,h);
            y=f_ordre(x_new,y,h);
            //y=f_RK4(x_new,y,h);
            x_new=k*h;
            yana_new= 2 * atan(exp(pow(x_new,3)/3))-(acos(-1.0)/2);
            
            if(k==v)
            {
                printf("x_new: %lf\n",x_new);
                printf("y: %lf\n",y);
                printf("yana_new: %lf\n",yana_new);
                Eh=fabs(y-yana_new);
                fprintf(fhandler3,"%.20lf\t%.20lf\n",h,Eh);
            }
        
        }
        v*=10;
            
    }

    fclose(fhandler1);
    fclose(fhandler2);
    fclose(fhandler3);
    
    return 0;
}

