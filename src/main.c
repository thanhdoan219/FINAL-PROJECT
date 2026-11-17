#include <stdio.h>
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
    int i = 0, inRange = 0;
    char check;
    //float temperature;
    
    do
    {
        printf("Temperature: ");
        scanf("%lf", &readings[i]);
        if (readings[i] > MAX || readings[i] < MIN)
            inRange = 1;
        printf("Do you want to add another temperature?(Y/N)");
        scanf(" %c", &check);
        check = toupper(check);
        if (check == 'Y' || i < READING_COUNT)
            i++;
    } while (check == 'Y' && i < READING_COUNT);

    displayReadings(readings, i);

    gpioInitialise();
    gpioSetMode(PIN,PI_OUTPUT);

    if(inRange == 1)
    {
        printf("Dangerous\n");
        gpioWrite(PIN,1);// LED ON
        getchar(); // waits for Enter key
    }
    else
    {
        printf("Safe\n");
    }

    printf("\nAverage temperature: %.1f F\n",
           calculateAverage(readings, i+1));
    
    
    printf("\n");
    
    	
    return 0;
}
