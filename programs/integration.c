#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M_PI 3.14159265358979323846

int main(void)
{
    printf("Numerical Integration and Related Computations\n");
    srand(time(NULL));
    int i = 0;
    int j = 0;
    int k = 0;
    int n = 10000;
    double a = 0.0, b = M_PI;
    double h = (b - a) / n;
    double rect = 0.0, trap = 0.0, simp = 0.0;
    for (i = 0; i < n; i++)
    {
        double x = a + i * h;
        rect += sin(x);
    }
    rect *= h;
    for (i = 0; i < n; i++)
    {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        trap += 0.5 * (sin(x1) + sin(x2));
    }
    trap *= h;
    for (i = 0; i < n; i += 2)
    {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;
        double x2 = a + (i + 2) * h;
        simp += (sin(x0) + 4 * sin(x1) + sin(x2));
    }
    simp *= h / 3.0;
    printf("Rect %.10f\nTrap %.10f\nSimp %.10f\n", rect, trap, simp);

    double monte = 0.0;
    for (i = 0; i < n; i++)
    {
        double r = a + (b - a) * (rand() / (double)RAND_MAX);
        monte += sin(r);
    }
    monte *= (b - a) / n;
    printf("Monte %.10f\n", monte);

    double gauss = 0.0;
    int ng = 1000;
    for (i = 0; i < ng; i++)
    {
        double t = cos(M_PI * (i + 0.75) / (ng + 0.5));
        gauss += sin(0.5 * (b - a) * t + 0.5 * (b + a));
    }
    gauss *= (b - a) / ng;
    printf("Gauss %.10f\n", gauss);

    double rom[8][8] = {{0.0}};
    for (i = 0; i < 8; i++)
    {
        int m = 1 << i;
        double step = (b - a) / m;
        double s = 0.5 * (sin(a) + sin(b));
        for (j = 1; j < m; j++)
            s += sin(a + j * step);
        rom[i][0] = s * step;
    }
    for (i = 1; i < 8; i++)
    {
        for (j = 1; j <= i; j++)
        {
            rom[i][j] = (pow(4, j) * rom[i][j - 1] - rom[i - 1][j - 1]) / (pow(4, j) - 1);
        }
    }
    printf("Romberg %.10f\n", rom[7][7]);

    double integ = 0.0;
    int slices = 5000;
    double step = (b - a) / slices;
    for (i = 0; i < slices; i++)
    {
        double x = a + i * step + step / 2.0;
        integ += exp(-x * x);
    }
    integ *= step;
    printf("Gaussian exp(-x^2) %.10f\n", integ);

    double double_sum = 0.0;
    int m1 = 200, m2 = 200;
    double xa = 0, xb = 1, ya = 0, yb = 1;
    double hx = (xb - xa) / m1;
    double hy = (yb - ya) / m2;
    for (i = 0; i < m1; i++)
    {
        for (j = 0; j < m2; j++)
        {
            double x = xa + (i + 0.5) * hx;
            double y = ya + (j + 0.5) * hy;
            double_sum += sin(x * y);
        }
    }
    double_sum *= hx * hy;
    printf("Double integral sin(xy) %.10f\n", double_sum);

    double volume = 0.0;
    int samples = 200000;
    for (i = 0; i < samples; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        double z = (double)rand() / RAND_MAX;
        if (x * x + y * y + z * z <= 1.0)
        {
            volume=volume+1;
        }
    }
    volume /= samples;
    volume *= 8.0;
    printf("Sphere volume %.10f\n", volume);

    double pi_est = 0.0;
    int hits = 0;
    for (i = 0; i < 500000; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0)
        {
            hits=hits+1;
        }
    }
    pi_est = 4.0 * hits / 500000.0;
    printf("Monte Pi %.10f\n", pi_est);

    double taylor = 0.0;
    double xval = 1.0;
    for (i = 0; i < 15; i++)
    {
        double term = pow(xval, i) / tgamma(i + 1);
        if (i % 2)
            term = -term;
        taylor += term;
    }
    printf("exp(-1) approx %.10f\n", taylor);

    double fourier = 0.0;
    int terms = 50;
    for (i = 1; i <= terms; i++)
    {
        fourier += (sin(i * 1.0) / i);
    }
    printf("Fourier partial sum %.10f\n", fourier);

    double nested_sum = 0.0;
    for (i = 1; i <= 30; i++)
    {
        for (j = 1; j <= 30; j++)
        {
            for (k = 1; k <= 30; k++)
            {
                nested_sum += 1.0 / (i + j + k);
            }
        }
    }
    printf("Nested harmonic %.10f\n", nested_sum);

    double adaptive = 0.0;
    int intervals = 2000;
    double prev = 0.0;
    for (i = 1; i <= intervals; i++)
    {
        double xi = a + (b - a) * i / intervals;
        double yi = cos(xi);
        adaptive += fabs(yi - prev);
        prev = yi;
    }
    adaptive *= (b - a) / intervals;
    printf("Adaptive-like %.10f\n", adaptive);

    double mat_sum = 0.0;
    int dim = 20;
    double mat[20][20];
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            mat[i][j] = sin((i + 1) * (j + 1));
        }
    }
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            mat_sum += mat[i][j];
        }
    }
    printf("Matrix sum %.10f\n", mat_sum);

    int count = 0;
    double seq = 0.0;
    i = 0;
    while (i < 1000)
    {
        double t = (i + 0.5) / 1000.0;
        seq += 1.0 / (1 + t * t);
        i=i+1;
        count=count+1;
    }
    seq /= 1000.0;
    seq *= 1.0;
    printf("Pi/4 approx %.10f steps %d\n", seq, count);

    double weird = 0.0;
    for (i = 1; i <= 100; i++)
    {
        for (j = 1; j <= 100; j++)
        {
            if ((i + j) % 2 == 0)
            {
                weird += sin(i * j * 0.001);
            }
            else
            {
                weird += cos(i * j * 0.001);
            }
        }
    }
    printf("Weird double sum %.10f\n", weird);

    double series = 0.0;
    for (i = 1; i <= 100; i++)
    {
        double term = pow(-1, i + 1) / (double)i;
        series += term;
    }
    printf("ln(2) approx %.10f\n", series);

    double bess = 0.0;
    double x0 = 1.0;
    for (i = 0; i < 20; i++)
    {
        double term = pow(-1, i) * pow(x0 / 2.0, 2 * i) / (tgamma(i + 1) * tgamma(i + 1));
        bess += term;
    }
    printf("Bessel J0(1) %.10f\n", bess);

    return 0;
}
