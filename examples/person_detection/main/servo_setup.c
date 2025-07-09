#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_main.h"
#include <math.h>

// #define M_PI 3.14159265358979323846

int currentDuty = 614;
int currentPan = 614;
int currentTilt = 614;
ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 50,
    .clk_cfg = LEDC_AUTO_CLK,
    .deconfigure = false};

ledc_channel_config_t ledc_channelTilt = {
    .gpio_num = 2,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_0,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_0,
    .duty = 614,
    .hpoint = 0};
ledc_channel_config_t ledc_channelPan = {
    .gpio_num = 3,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_1,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_0,
    .duty = 614,
    .hpoint = 0};
void servo_init()
{
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channelTilt);
    ledc_set_duty(ledc_channelTilt.speed_mode, ledc_channelTilt.channel, 614);
    ledc_update_duty(ledc_channelTilt.speed_mode, ledc_channelTilt.channel);

    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channelPan);
    ledc_set_duty(ledc_channelPan.speed_mode, ledc_channelPan.channel, 614);
    ledc_update_duty(ledc_channelPan.speed_mode, ledc_channelPan.channel);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void servo_moveto(int panto,int tiltto)
{
    int startPan = currentPan;
    int startTilt = currentTilt;
    for (float t = 0; t <= M_PI; t += 0.05)
    {
        float eased = (1 - cosf(t)) / 2.0f;
        // float eased = t / M_PI;
        currentPan = startPan + (panto - startPan) * eased;
        currentTilt = startTilt + (tiltto - startTilt) * eased;
        ledc_set_duty(ledc_channelPan.speed_mode, ledc_channelPan.channel, currentPan);
        ledc_update_duty(ledc_channelPan.speed_mode, ledc_channelPan.channel);
        ledc_set_duty(ledc_channelTilt.speed_mode, ledc_channelTilt.channel, currentTilt);
        ledc_update_duty(ledc_channelTilt.speed_mode, ledc_channelTilt.channel);
        printf("t:%f currentPan:%d currentTilt:%d eased:%f\n", t, currentPan, currentTilt, eased);
        vTaskDelay(20.0 / portTICK_PERIOD_MS);
    }

}

void servo_panto(int moveto)
{
    int start = currentPan;
    for (float t = 0; t <= M_PI; t += 0.05)
    {
        float eased = (1 - cosf(t)) / 2.0f;
        // float eased = t / M_PI;
        currentPan = start + (moveto - start) * eased;

        ledc_set_duty(ledc_channelPan.speed_mode, ledc_channelPan.channel, currentPan);
        ledc_update_duty(ledc_channelPan.speed_mode, ledc_channelPan.channel);
        printf("t:%f current:%d moveto:%d eased:%f\n", t, currentPan, moveto, eased);
        vTaskDelay(20.0 / portTICK_PERIOD_MS);
    }
}
void servo_tiltto(int moveto)
{
    int start = currentTilt;

    for (float t = 0; t <= M_PI; t += 0.05)
    {
        float eased = (1 - cosf(t)) / 2.0f;
        // float eased = t / M_PI;
        currentTilt = start + (moveto - start) * eased;

        ledc_set_duty(ledc_channelTilt.speed_mode, ledc_channelTilt.channel, currentTilt);
        ledc_update_duty(ledc_channelTilt.speed_mode, ledc_channelTilt.channel);
        printf("t:%f current:%d moveto:%d eased:%f\n", t, currentTilt, moveto, eased);
        vTaskDelay(20.0 / portTICK_PERIOD_MS);
    }
}