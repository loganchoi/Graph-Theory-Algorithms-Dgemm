#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <vector>
using namespace std;

class Timer{
public:
    void start(){
        err = clock_gettime(CLOCK_REALTIME, &start_time);
    }
    void end(){
        err = clock_gettime(CLOCK_REALTIME, &end_time);
    }
    double get(){
        return (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec)/(double)1000000000;
    }
private:
    int err = 0;
    struct timespec start_time, end_time;
};

int RandMatrixGen(double *M, int n){
    srand (time(NULL));
    for (int i = 0; i < n*n; i++)
      M[i] =  2.0*rand()/RAND_MAX - 1.0;
    return 0;
}

double verify(double *C0, double *C1, int n){
    double diff = fabs(C0[0] - C1[0]);
    for (int i = 0; i < n*n; i++)
      if (fabs(C0[i] - C1[i]) > diff) diff = fabs(C0[i] - C1[i]);
    return diff;
}

int dgemm_ijk(double *A, double *B, double *C, int n){
    // dgemm with loop order ijk 
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++)
          C[i*n+j] += A[i*n+k] * B[k*n+j];
    return 0;
}

int dgemm_ikj(double *A, double *B, double *C, int n){
    // implement your dgemm with loop order ikj 
    for (int i = 0; i <n; i++)
       for (int k= 0; k<n; k++)
          for(int j = 0; j<n; j++)
             C[i*n+k] += A[i*n+j] * B[j*n+k];
    return 0;
}

int dgemm_jik(double *A, double *B, double *C, int n){
    // implement your dgemm with loop order jik
    for (int j = 0; j<n; j++)
       for(int i = 0; i<n; i++)
          for(int k = 0; k<n;k++)
             C[j*n+i] += A[j*n+k] * B[k*n+i];
    return 0;
}

int dgemm_jki(double *A, double *B, double *C, int n){
    // implement your dgemm with loop order jki
    for (int j = 0; j<n; j++)
       for(int k = 0; k<n; k++)
          for(int i = 0; i<n;i++)
             C[j*n+k] += A[j*n+i] * B[i*n+k];
    return 0;
}

int dgemm_kij(double *A, double *B, double *C, int n){
    // implement your dgemm with loop order kij
    for (int k=0;k<n;k++)
       for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
             C[k*n+i] += A[k*n+j] * B[j*n+i];
    return 0;
}

int dgemm_kji(double *A, double *B, double *C, int n){
    // implement your dgemm with loop order kji
    for (int k = 0; k<n; k++)
       for (int j=0;j<n;j++)
          for(int i=0;i<n;i++)
             C[k*n+j] += A[k*n+i] * B[i*n+j];
    return 0;
}

int dgemm_recursive(double *A, double *B, double *C, int n){
    // implement your dgemm using recursive algorithm
    if (n==1)
    {  
       
       C[0] = A[0] *B[0];
          
    }
    else
    {
       double *A11p = new double[n*n/4];
       double *A12p = new double[n*n/4];
       double *A21p = new double[n*n/4];
       double *A22p = new double[n*n/4];
       double *B11p = new double[n*n/4];
       double *B12p = new double[n*n/4];
       double *B21p = new double[n*n/4];
       double *B22p = new double[n*n/4];
       double *combine1 =new double [n*n/4];
       double *combine2 =new double [n*n/4];
       double *combine3 =new double [n*n/4];
       double *combine4 =new double [n*n/4];
       double *combine5 =new double [n*n/4];
       double *combine6 =new double [n*n/4];
       double *combine7 =new double [n*n/4];
       double *combine8 =new double [n*n/4];
       
       //This will partition the matrix into four sub matrices
       for (int i = 0;i<n/2;i++)
       {
          for (int j = 0; j < n/2;j++)
          {
            A11p[i*(n/2)+j] = A[i*n+j];
            B11p[i*(n/2)+j] = B[i*n+j];
            
            A12p[i*(n/2)+j] = A[i*n+(j+n/2)];
            B12p[i*(n/2)+j] = B[i*n+(j+n/2)];
            
            A21p[i*(n/2)+j] = A[(i+n/2)*n+j];
            B21p[i*(n/2)+j] = B[(i+n/2)*n+j];
            
            A22p[i*(n/2)+j] = A[(i+n/2)*n+(j+n/2)];
            B22p[i*(n/2)+j] = B[(i+n/2)*n+(j+n/2)];
          }
       }
           
        dgemm_recursive(A11p,B11p,combine1,n/2);
        dgemm_recursive(A12p,B21p,combine2,n/2);
        dgemm_recursive(A11p,B12p,combine3,n/2);
        dgemm_recursive(A12p,B22p,combine4,n/2);
        dgemm_recursive(A21p,B11p,combine5,n/2);
        dgemm_recursive(A22p,B21p,combine6,n/2);
        dgemm_recursive(A21p,B12p,combine7,n/2);
        dgemm_recursive(A22p,B22p,combine8,n/2);
        for (int i = 0;i<n/2;i++)
        {
            for(int j = 0; j<n/2;j++)
            {
                C[i*n+j] = combine1[i*n+j] + combine2[i*n+j];
                C[i*n+(j+n/2)] = combine3[i*n+j] + combine4[i*n+j];
                C[(i+n/2)*n+j] = combine5[i*n+j] + combine6[i*n+j];
                C[(i+n/2)*n+(j+n/2)] = combine7[i*n+j] + combine8[i*n+j];
            }
        }

    }
    
    return 0;
}
void add(double *A, double*B, double *C, int n)
{
    for (int i = 0; i<n; i++)
        for (int j = 0; j<n;j++)
             C[i*n+j] = A[i*n+j] + B[i*n+j];
    return;
}

void subtract(double*A, double*B,double *C, int n)
{
    for (int i = 0; i<n; i++)
        for (int j = 0; j<n;j++)
             C[i*n+j] = A[i*n+j] - B[i*n+j];
    return;
}

int dgemm_Strassen(double *A, double *B, double *C, int n){
    // implement your dgemm using Strassen's algorithm
    if (n==1)
    {
        C[0] = A[0] *B[0]; 
    }
    else
    {
       double *a = new double[n*n/4];
       double *b = new double[n*n/4];
       double *c = new double[n*n/4];
       double *d = new double[n*n/4];
       double *e = new double[n*n/4];
       double *f = new double[n*n/4];
       double *g = new double[n*n/4];
       double *h = new double[n*n/4];
       double *FminusH = new double[n*n/4];
       double *AplusB = new double[n*n/4];
       double *CplusD = new double[n*n/4];
       double *GminusE = new double[n*n/4];
       double *AplusD = new double[n*n/4];
       double *EplusH = new double[n*n/4];
       double *BminusD = new double[n*n/4];
       double *GplusH = new double[n*n/4];
       double *AminusC = new double[n*n/4];
       double *EplusF = new double[n*n/4];
       double *p1 = new double[n*n/4];
       double *p2 = new double[n*n/4];
       double *p3 = new double[n*n/4];
       double *p4 = new double[n*n/4];
       double *p5 = new double[n*n/4];
       double *p6 = new double[n*n/4];
       double *p7 = new double[n*n/4];
       
       for (int i = 0;i<n/2;i++)
       {
          for (int j = 0; j < n/2;j++)
          {
            a[i*(n/2)+j] = A[i*n+j];
            e[i*(n/2)+j] = B[i*n+j];
            
            b[i*(n/2)+j] = A[i*n+(j+n/2)];
            f[i*(n/2)+j] = B[i*n+(j+n/2)];
            
            c[i*(n/2)+j] = A[(i+n/2)*n+j];
            g[i*(n/2)+j] = B[(i+n/2)*n+j];
            
            d[i*(n/2)+j] = A[(i+n/2)*n+(j+n/2)];
            h[i*(n/2)+j] = B[(i+n/2)*n+(j+n/2)];
          }
       }
       add(a,b,AplusB,n/2);
       add(c,d,CplusD,n/2);
       add(a,d,AplusD,n/2);
       add(e,h,EplusH,n/2);
       add(g,h,GplusH,n/2);
       add(e,f,EplusF,n/2);
       subtract(f,h,FminusH,n/2);
       subtract(g,e,GminusE,n/2);
       subtract(b,d,BminusD,n/2);
       subtract(a,c,AminusC,n/2);
       
       dgemm_Strassen(a,FminusH,p1,n/2);
       dgemm_Strassen(AplusB,h,p2,n/2);
       dgemm_Strassen(CplusD,e,p3,n/2);
       dgemm_Strassen(d,GminusE,p4,n/2);
       dgemm_Strassen(AplusD,EplusH,p5,n/2);
       dgemm_Strassen(BminusD,GplusH,p6,n/2);
       dgemm_Strassen(AminusC,EplusH,p7,n/2);
       
       for (int i = 0;i<n/2;i++)
        {
            for(int j = 0; j<n/2;j++)
            {
                C[i*n+j] = p5[i*n+j] + p4[i*n+j] - p2[i*n+j] + p6[i*n+j];
                C[i*n+(j+n/2)] = p1[i*n+j] + p2[i*n+j];
                C[(i+n/2)*n+j] = p3[i*n+j] + p4[i*n+j];
                C[(i+n/2)*n+(j+n/2)] = p1[i*n+j] + p5[i*n+j] - p3[i*n+j]-p7[i*n+j];
            }
        }
        
    }
    
    
    return 0;
}

int dgemm_register(double *A, double *B, double *C, int n){
    // BONUS example: dgemm with register reuse
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++){
          register double r = C[i*n+j];
          for (int k = 0; k < n; k++)
            r += A[i*n+k] * B[k*n+j];
          C[i*n+j] = r;
      }
    return 0;
}

int dgemm_register_blocked_2x2(double *A, double *B, double *C, int n){
    // BONUS: implement your dgemm with blocked cache/register reuse (block size = 2)
    return 0;
}

int dgemm_register_blocked_3x3(double *A, double *B, double *C, int n){
    // BONUS: implement your dgemm with blocked cache/register reuse (block size = 3)
    return 0;
}

int main(int argc, char **argv){

    int n = atoi(argv[1]);
    double * A = (double *) malloc(n*n*sizeof(double));
    double * B = (double *) malloc(n*n*sizeof(double));
    double * C0 = (double *) malloc(n*n*sizeof(double));
    double * C1 = (double *) malloc(n*n*sizeof(double));

    Timer timer;
    // record the execution time of functions
    std::vector<double> execution_time;
    // name of functions
    std::string functions[11] = {"dgemm_ijk", "dgemm_ikj", "dgemm_jik", "dgemm_jki", "dgemm_kij", "dgemm_kji", "dgemm_recursive", "dgemm_Strassen", "dgemm_register", "dgemm_register_blocked_2x2", "dgemm_register_blocked_3x3"};
    // max difference 
    double max_difference = 0;
    // generate input matrix A and B
    RandMatrixGen(A, n);
    RandMatrixGen(B, n);
    // compute result using dgemm_ijk
    memset(C0, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_ijk(A, B, C0, n);
    timer.end();
    execution_time.push_back(timer.get());

    // compute result using dgemm_ikj and compare the result with C0
    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_ikj(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_jik(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_jki(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_kij(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_kji(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_recursive(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_Strassen(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_register(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_register_blocked_2x2(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    memset(C1, 0, sizeof(double)*n*n);
    timer.start();
    dgemm_register_blocked_3x3(A, B, C1, n);
    timer.end();
    max_difference = verify(C0, C1, n);
    std::cout << "Max difference = " << max_difference << std::endl;
    execution_time.push_back(timer.get());

    free(A);
    free(B);
    free(C0);
    free(C1);

    // report result
    std::cout << std::endl;
    for(int i=0; i<execution_time.size(); i++){
        std::cout << functions[i] << " execution time: " << execution_time[i] << std::endl;
    }
    return 0;

}



















