#include <stdio.h>

void celsius_to_fahrenheit(float *t) {
    *t = *t * 9 / 5 + 32;
}

void celsius_to_kelvin(float *t) {
    *t += 273.15;
}

void fahrenheit_to_celsius(float *t) {
    *t = (*t - 32) * 5 / 9;
}

void kelvin_to_celsius(float *t) {
    *t -= 273.15;
}

void convert_array(float a[], int n, void (*f)(float *)) {
    for (int i = 0; i < n; i++)
        f(a + i);
}

float average_temp(float a[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += *(a + i);
    return sum / n;
}

int main() {
    char cities[8][30] = {
        "Delhi", "Mumbai", "Chennai", "Kolkata",
        "Bengaluru", "Hyderabad", "Jaipur", "Pune"
    };

    float a[8] = {42.1, 36.5, 38.8, 34.2, 28.9, 40.3, 45.6, 33.1};
    int hot = 0, cold = 0;
    char choice, line[100];
    FILE *fp;

    for (int i = 1; i < 8; i++) {
        if (a[i] > a[hot])
            hot = i;
        if (a[i] < a[cold])
            cold = i;
    }

    printf("Hottest: %s %.2f C\n", cities[hot], a[hot]);
    printf("Coldest: %s %.2f C\n", cities[cold], a[cold]);
    printf("Average: %.2f C\n", average_temp(a, 8));

    printf("\nConvert to F or K: ");
    scanf(" %c", &choice);

    if (choice == 'F' || choice == 'f')
        convert_array(a, 8, celsius_to_fahrenheit);
    else if (choice == 'K' || choice == 'k')
        convert_array(a, 8, celsius_to_kelvin);
    else {
        printf("Invalid choice\n");
        return 0;
    }

    fp = fopen("temperature.txt", "w");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return 1;
    }

    fprintf(fp, "CITY TEMPERATURE REPORT\n");

    for (int i = 0; i < 8; i++) {
        printf("%s: %.2f\n", cities[i], a[i]);
        fprintf(fp, "%s: %.2f\n", cities[i], a[i]);
    }

    fclose(fp);
    printf("\nData saved to temperature.txt\n");

    fp = fopen("temperature.txt", "r");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return 1;
    }

    printf("\n===== SAVED FILE DATA =====\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);

    return 0;
}