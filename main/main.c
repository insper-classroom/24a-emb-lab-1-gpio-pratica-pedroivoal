#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN_ANTI = 2;
const int BTN_PIN_HORA = 13;
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9;

const int comands_ant[4][4] = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
};

const int comands_hora[4][4] = {
    {0,0,0,1},
    {0,0,1,0},
    {0,1,0,0},
    {1,0,0,0}
};

void set_pins();
void step_motor(int steps, int comands[4][4]);

int main() {
    stdio_init_all();
    set_pins();
    int passos = 90.0/360 * 2048;

    while (true) {
        if (!gpio_get(BTN_PIN_ANTI)) {
            printf("Button pressed\n");
            step_motor(passos, comands_ant);
            printf("Finished\n");
        }
        else if (!gpio_get(BTN_PIN_HORA)) {
            printf("Button pressed\n");
            step_motor(passos, comands_hora);
            printf("Finished\n");
        }
        
    }
}

void set_pins() {
    gpio_init(BTN_PIN_ANTI);
    gpio_set_dir(BTN_PIN_ANTI, GPIO_IN);
    gpio_pull_up(BTN_PIN_ANTI);

    gpio_init(BTN_PIN_HORA);
    gpio_set_dir(BTN_PIN_HORA, GPIO_IN);
    gpio_pull_up(BTN_PIN_HORA);

    gpio_init(IN1);
    gpio_set_dir(IN1, GPIO_OUT);

    gpio_init(IN2);
    gpio_set_dir(IN2, GPIO_OUT);

    gpio_init(IN3);
    gpio_set_dir(IN3, GPIO_OUT);

    gpio_init(IN4);
    gpio_set_dir(IN4, GPIO_OUT);
}

void step_motor(int steps, int comands[4][4]) {
    for (int i = 0; i < steps; i++) {
            printf("i: %d;\n", i);
            gpio_put(IN1, comands[i%4][0]);
            gpio_put(IN2, comands[i%4][1]);
            gpio_put(IN3, comands[i%4][2]);
            gpio_put(IN4, comands[i%4][3]);
            sleep_ms(3);
    }
}
