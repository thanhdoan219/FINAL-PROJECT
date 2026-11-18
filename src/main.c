#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#define READING_COUNT 5
#define MIN 67.0
#define MAX 75.0
#define PIN 17

double calculateAverage(double readings[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) total += readings[i];
    return total / count;
}

/*int isOutOfRange(float temperature) {
    return (temperature > MAX || temperature < MIN) ? 1 : 0; 
}
*/
void displayReadings(double readings[], int count) {
    printf("Temperature Readings:\n");
    for (int i = 0; i < count; i++)
    {
        
        if(readings[i] > MAX || readings[i] < MIN)
        {
            printf("%.1f F ", readings[i]);
            printf("is not within the acceptable range. \n");
            
        }
        else
        {
            printf("%.1f F ", readings[i]);
            printf("is within the acceptable range. \n");
        }
          
    }
    printf("\n");
        
}

int main(int argc, char* argv[]) {
    double readings[READING_COUNT];
    int i = 0, inRange;
    char check;
    
    FILE* fp = fopen("filename.csv", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    fprintf(fp, "Temperature, status\n");
    
    gpioInitialise();
    gpioSetMode(PIN,PI_OUTPUT);
    gpioWrite(PIN, 0);
    //float temperature;
    
    
    do
    {
        inRange = 0;
        printf("Temperature: ");
        scanf("%lf", &readings[i]);
        
        if (readings[i] > MAX || readings[i] < MIN)
            inRange = 1;
        if(inRange == 1)
        {
            fprintf(fp, "%.1f, Dangerous\n", readings[i]);
            printf("Dangerous\n");
            gpioWrite(PIN,1);// LED ON
            getchar(); // waits for Enter key
        }
        else
        {
            fprintf(fp, "%.1f, Safe\n", readings[i]);
            printf("Safe\n");
            gpioWrite(PIN, 0);// LED OFF
            getchar(); // waits for Enter key
        }
        
        //fprintf(fp, "%f, %d", readings[i], inRange);
        
        printf("Do you want to add another temperature?(Y/N)");
        scanf(" %c", &check);
        check = toupper(check);
        if (check == 'Y' || i < READING_COUNT)
            i++;
        else if (i == 0)
            i = 1;
    } while (check == 'Y' && i < READING_COUNT);

    
    printf("\nAverage temperature: %.1f F\n",
           calculateAverage(readings, i+1));
    
    
    
    fclose(fp);
    
    
    printf("\n");
    
    	
    return 0;
}
