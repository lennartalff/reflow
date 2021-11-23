#include "actuators.h"
#include "TeensyTimerTool.h"
#include "Arduino.h"

#define PWM_SLOT_US 20000
#define PWM_SLOTS 100
#define PWM_PIN 2

#define SSR_LOW LOW
#define SSR_HIGH HIGH

static TeensyTimerTool::PeriodicTimer timer(TeensyTimerTool::TCK);
static uint8_t on_cycles = 0;
static uint8_t current_slot = 0;
static bool active = false;

static void acutators_timer_cb();

void actuators_init() {
    pinMode(PWM_PIN, OUTPUT);
    timer.begin(acutators_timer_cb, PWM_SLOT_US, true);
}

static void acutators_timer_cb() {
    current_slot = (current_slot >= PWM_SLOTS - 1) ? 0 : current_slot + 1;
    if (active) {
        if (current_slot < on_cycles) {
            Serial.println("1");
            digitalWriteFast(PWM_PIN, SSR_HIGH);
        } else {
            Serial.println("0");
            digitalWriteFast(PWM_PIN, SSR_LOW);
        }
    } else {
        Serial.println("-");
        digitalWriteFast(PWM_PIN, SSR_LOW);
    }
}

void actuators_switchHeating(bool on){
    active = on;
}
void actuators_set_heating_duty(uint8_t duty){
    if (duty > PWM_SLOTS) {
        duty = PWM_SLOTS;
    }
    on_cycles = duty;
}