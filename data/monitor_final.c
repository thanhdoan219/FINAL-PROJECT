#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define READING_COUNT 5
#define MIN 67.0
#define MAX 75.0


int isOutOfRange(float temperature) {
    return (temperature > MAX || temperature < MIN) ? 1 : 0; 
}

double calculateAverage(double readings[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) total += readings[i];
    return total / count;
}

void displayReadings(double readings[], int count) {
    printf("\n");
    printf("Temperature Readings:\n");
    for (int i = 0; i < count; i++) 
    {
        printf("%.1f F\t", readings[i]);
        if (readings[i] > MAX || readings[i] < MIN)
        {
            printf(" is not within the acceptable range");    
        }
        else
        {
            printf(" is within the acceptable range");
            
        }
}





int main(void) {
    double readings[READING_COUNT];
    int i = 0;
    char check;
    float temperature;
    
    do
    {
        printf("Temperature: ");
        scanf("%lf", &readings[i]);
        printf("Do you want to add another temperature?(Y/N)");
        scanf(" %c", &check);
        check = toupper(check);
        if (check == 'Y' || i < READING_COUNT)
            i++;
    } while (check == 'Y' && i < READING_COUNT);

    displayReadings(readings, i);
    printf("\nAverage temperature: %.1f F\n",
           calculateAverage(readings, i+1));
    
    /*temperature = calculateAverage(readings, i+1);


    if (temperature > MAX || temperature < MIN)
    {
        printf("%.1f is not within the acceptable range \n", temperature);
        isOutOfRange(temperature) == 0;
    }
    else
    {
        printf("%.1f is within the acceptable range \n", temperature);
        isOutOfRange(temperature) == 1;
    }*/

    
    	
    return 0;
}
