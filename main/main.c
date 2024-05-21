#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN = 2;

const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9;

const int comands[4][4] = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
};

void my_init();
void set_motor_pins();
void step_motor(int steps);

int main() {
    stdio_init_all();
    my_init();


    while (true) {
        if (!gpio_get(BTN_PIN)) {
            printf("Button pressed\n");
            int passos = 90.0/360 * 2048;
            step_motor(passos);
            printf("Finished\n");
        }
    }
}

void my_init() {
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    gpio_init(IN1);
    gpio_set_dir(IN1, GPIO_OUT);

    gpio_init(IN2);
    gpio_set_dir(IN2, GPIO_OUT);

    gpio_init(IN3);
    gpio_set_dir(IN3, GPIO_OUT);

    gpio_init(IN4);
    gpio_set_dir(IN4, GPIO_OUT);
}

void step_motor(int steps) {
    for (int i = 0; i < steps; i++) {
            printf("i: %d;\n", i);
            gpio_put(IN1, comands[i%4][0]);
            gpio_put(IN2, comands[i%4][1]);
            gpio_put(IN3, comands[i%4][2]);
            gpio_put(IN4, comands[i%4][3]);
            sleep_ms(5);
    }
}
