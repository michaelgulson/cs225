//#include <stdio>



int main() {
double **a = new double *[2];
double b[10];
a[0] = new double(1.0);
a[1] = b;
double **c = new double*;
*c = new double(*a[0]);
double ***d = &c;

delete*c;
delete c;
delete []a;
delete a[0];



return 0;
}
