#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void)
{
    printf("\n\n");
    printf("*************************************************************\n");
    printf("**      Discrete Fourier Transform Calculation Program     **\n");
    printf("*************************************************************\n");

    double complex in[] = {2.0, 3.0, 5.0, 7.0, 11.0};

    const size_t n = sizeof(in) / sizeof(in[0]);

    double complex out[n];

    const double epsilon = 1e-14;

    printf("--- Displaying Initial Input Signal ---\n\n");

    printf("Input array:\n");
    printf("[");
    for (size_t i = 0; i < n; ++i)
    {
        if (i != 0)
        {
            printf(", ");
        }

        double current_real_part;
        double current_imag_part;

        current_real_part = creal(in[i]);
        current_imag_part = cimag(in[i]);

        if (current_imag_part == 0)
        {
            printf("%f", current_real_part);
        }
        else if (current_imag_part > 0)
        {
            printf("%f+%fi", current_real_part, current_imag_part);
        }
        else
        {
            printf("%f%fi", current_real_part, current_imag_part);
        }
    }
    printf("]\n\n");

    printf("--- Beginning Forward Discrete Fourier Transform (DFT) ---\n\n");

    double two_pi_val;
    double neg_two_pi_val;
    double n_as_double_dft;
    double f;

    two_pi_val = 2.0 * M_PI;
    neg_two_pi_val = -1.0 * two_pi_val;
    n_as_double_dft = (double)n;
    f = neg_two_pi_val / n_as_double_dft;

    for (size_t i = 0; i < n; ++i)
    {
        double complex sum = 0.0 + 0.0 * I;

        for (size_t j = 0; j < n; ++j)
        {
            double angle_i_component;
            double angle_j_component;
            double angle_product;
            double final_angle_x;
            double cos_of_x;
            double sin_of_x;

            angle_i_component = (double)i;
            angle_j_component = (double)j;
            angle_product = f * angle_i_component;
            final_angle_x = angle_product * angle_j_component;

            cos_of_x = cos(final_angle_x);
            sin_of_x = sin(final_angle_x);

            double complex exponential_term;
            exponential_term = cos_of_x + sin_of_x * I;

            double complex input_sample;
            input_sample = in[j];

            double complex term_to_add;
            term_to_add = input_sample * exponential_term;

            sum += term_to_add;
        }

        double real_part_before_clean;
        double imag_part_before_clean;

        real_part_before_clean = creal(sum);
        imag_part_before_clean = cimag(sum);

        double rounded_real_part;
        double rounded_imag_part;

        rounded_real_part = round(real_part_before_clean);
        rounded_imag_part = round(imag_part_before_clean);

        double real_difference;
        double imag_difference;

        real_difference = fabs(real_part_before_clean - rounded_real_part);
        imag_difference = fabs(imag_part_before_clean - rounded_imag_part);

        double final_real_part = real_part_before_clean;
        double final_imag_part = imag_part_before_clean;

        if (real_difference < epsilon)
        {
            final_real_part = rounded_real_part;
        }

        if (imag_difference < epsilon)
        {
            final_imag_part = rounded_imag_part;
        }

        double complex cleaned_value;
        cleaned_value = final_real_part + final_imag_part * I;

        out[i] = cleaned_value;
    }

    printf("--- Forward DFT Complete. Displaying Result ---\n\n");

    printf("Discrete Fourier Transform:\n");
    printf("[");
    for (size_t i = 0; i < n; ++i)
    {
        if (i != 0)
        {
            printf(", ");
        }

        double r_dft;
        double im_dft;

        r_dft = creal(out[i]);
        im_dft = cimag(out[i]);

        if (im_dft == 0)
        {
            printf("%f", r_dft);
        }
        else if (im_dft > 0)
        {
            printf("%f+%fi", r_dft, im_dft);
        }
        else
        {
            printf("%f%fi", r_dft, im_dft);
        }
    }
    printf("]\n\n");

    printf("--- Beginning Inverse Discrete Fourier Transform (IDFT) ---\n\n");

    double pos_two_pi_val;
    double n_as_double_idft;
    double f_inverse;

    pos_two_pi_val = 2.0 * M_PI;
    n_as_double_idft = (double)n;
    f_inverse = pos_two_pi_val / n_as_double_idft;

    for (size_t i = 0; i < n; ++i)
    {
        double complex inv_sum = 0.0 + 0.0 * I;

        for (size_t j = 0; j < n; ++j)
        {
            double inv_angle_i_comp;
            double inv_angle_j_comp;
            double inv_angle_prod;
            double final_inv_angle_x;
            double inv_cos_x;
            double inv_sin_x;

            inv_angle_i_comp = (double)i;
            inv_angle_j_comp = (double)j;
            inv_angle_prod = f_inverse * inv_angle_i_comp;
            final_inv_angle_x = inv_angle_prod * inv_angle_j_comp;

            inv_cos_x = cos(final_inv_angle_x);
            inv_sin_x = sin(final_inv_angle_x);

            double complex inv_exp_term;
            inv_exp_term = inv_cos_x + inv_sin_x * I;

            double complex dft_sample;
            dft_sample = out[j];

            double complex inv_term_to_add;
            inv_term_to_add = dft_sample * inv_exp_term;

            inv_sum += inv_term_to_add;
        }

        double complex scaled_sum;
        scaled_sum = inv_sum / n_as_double_idft;

        double inv_real_before_clean;
        double inv_imag_before_clean;

        inv_real_before_clean = creal(scaled_sum);
        inv_imag_before_clean = cimag(scaled_sum);

        double inv_rounded_real;
        double inv_rounded_imag;

        inv_rounded_real = round(inv_real_before_clean);
        inv_rounded_imag = round(inv_imag_before_clean);

        double inv_real_diff;
        double inv_imag_diff;

        inv_real_diff = fabs(inv_real_before_clean - inv_rounded_real);
        inv_imag_diff = fabs(inv_imag_before_clean - inv_rounded_imag);

        double inv_final_real = inv_real_before_clean;
        double inv_final_imag = inv_imag_before_clean;

        if (inv_real_diff < epsilon)
        {
            inv_final_real = inv_rounded_real;
        }

        if (inv_imag_diff < epsilon)
        {
            inv_final_imag = inv_rounded_imag;
        }

        double complex inv_cleaned_value;
        inv_cleaned_value = inv_final_real + inv_final_imag * I;

        in[i] = inv_cleaned_value;
    }

    printf("--- Inverse DFT Complete. Displaying Final Reconstructed Signal ---\n\n");

    printf("Inverse DFT:\n");
    printf("[");
    for (size_t i = 0; i < n; ++i)
    {
        if (i != 0)
        {
            printf(", ");
        }

        double r_idft;
        double im_idft;

        r_idft = creal(in[i]);
        im_idft = cimag(in[i]);

        if (im_idft == 0)
        {
            printf("%f", r_idft);
        }
        else if (im_idft > 0)
        {
            printf("%f+%fi", r_idft, im_idft);
        }
        else
        {
            printf("%f%fi", r_idft, im_idft);
        }
    }
    printf("]\n\n");

    printf("--- Program Finished ---\n");
    printf("All calculations are complete. Exiting.\n\n");

    return 0;
}
