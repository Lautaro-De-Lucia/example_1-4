#include "mbed.h"
#include "arm_book_lib.h"

DigitalIn gasDetector(D2);
DigitalIn overTempDetector(D3);
//
// Agrupamos aButton, bButton, cButton, dButton en un solo BusIn
BusIn buttonBus(D4, D5, D6, D7);

DigitalOut alarmLed(LED1);

int main()
{
    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);

    // Configura resistencias PullDown para los botones agrupados en BusIn
    for (int i = 0; i < 4; i++) {
        buttonBus[i].mode(PullDown);
    }

    alarmLed = OFF;
    bool alarmState = OFF;

    while (true) {
        if (gasDetector || overTempDetector) {
            printf("Se detecto gas o sobre-temperatura.\n");
            alarmState = ON;
        }

        // Muestra el estado actual de la alarma
        alarmLed = alarmState;
        printf("Estado de la alarma: %s\n", alarmState ? "ACTIVADA" : "DESACTIVADA");

        // Leer los 4 bits del BusIn (D4-D7)
        int buttonState = buttonBus.read();  // ejemplo: 0b0011 si A y B están presionados

        // Desactiva alarma si A y B están presionados, y C y D no
        if (buttonState == 0b0011) {
            printf("Código correcto. Apagando alarma...\n");
            alarmState = OFF;
        }

        delay(500);
    }
}
