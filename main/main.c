#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define COMANDS_N 4

const int BTN_PIN = 2;
const int LED_PIN = 3;

const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9;


const int step_sequence[COMANDS_N][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};


const int step_sequence[COMANDS_N][4] = {
    {1, 0, 0, 1},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1}
};

void my_init();
void set_motor_pins(int a, int b, int c, int d);
void step_motor(int steps);

int main() {
    stdio_init_all();
    my_init();

    while (true) {
        if (!gpio_get(BTN_PIN)) {
            printf("Button pressed\n");
            gpio_put(LED_PIN, 1);

            step_motor(2048);

            gpio_put(LED_PIN, 0);
        }
    }
}

void my_init() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

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
        for (int j = 0; j < COMANDS_N; j++) {
            printf("i: %d, j: %d\n", i, j);
            set_motor_pins(step_sequence[j][0], step_sequence[j][1], step_sequence[j][2], step_sequence[j][3]);
            sleep_ms(5);
        }
    }
}

void set_motor_pins(int a, int b, int c, int d) {
    gpio_put(IN1, 0);
    gpio_put(IN2, 0);
    gpio_put(IN3, 0);
    gpio_put(IN4, 0);

    sleep_ms(5);

    gpio_put(IN1, a);
    gpio_put(IN2, b);
    gpio_put(IN3, c);
    gpio_put(IN4, d);
}
