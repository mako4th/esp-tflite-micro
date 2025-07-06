#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_main.h"

ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 50,
    .clk_cfg = LEDC_AUTO_CLK,
    .deconfigure = false};

ledc_channel_config_t ledc_channel = {
    .gpio_num = 2,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_0,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_0,
    .duty = 614,
    .hpoint = 0};

void servo_init()
{
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, 614);
    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void servo_moveto(int moveto)
{
    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, moveto);
    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    // int target = targetList[count];
    // while (true)
    // {
    //     if (target < nowWidth)
    //     {
    //         nowWidth--;
    //         ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, nowWidth);
    //         ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    //         vTaskDelay(20 / portTICK_PERIOD_MS);
    //     }
    //     else if (target > nowWidth)
    //     {
    //         nowWidth++;
    //         ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, nowWidth);
    //         ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    //         vTaskDelay(20 / portTICK_PERIOD_MS);
    //     }
    //     else
    //     {
    //         break;
    //     }
    // }
    // printf("target %d,now %d\n",target,nowWidth);
    // // ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
}