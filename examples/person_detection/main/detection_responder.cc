/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/*
 * SPDX-FileCopyrightText: 2019-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "detection_responder.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"

#include "esp_main.h"
#if DISPLAY_SUPPORT
#include "image_provider.h"
#include "bsp/esp-bsp.h"

// Camera definition is always initialized to match the trained detection model: 96x96 pix
// That is too small for LCD displays, so we extrapolate the image to 192x192 pix
#define IMG_WD (96 * 2)
#define IMG_HT (96 * 2)

static lv_obj_t *camera_canvas = NULL;
static lv_obj_t *person_indicator = NULL;
static lv_obj_t *label = NULL;

static void create_gui(void)
{
  bsp_display_start();
  bsp_display_backlight_on(); // Set display brightness to 100%
  bsp_display_lock(0);
  camera_canvas = lv_canvas_create(lv_scr_act());
  assert(camera_canvas);
  lv_obj_align(camera_canvas, LV_ALIGN_TOP_MID, 0, 0);

  person_indicator = lv_led_create(lv_scr_act());
  assert(person_indicator);
  lv_obj_align(person_indicator, LV_ALIGN_BOTTOM_MID, -70, 0);
  lv_led_set_color(person_indicator, lv_palette_main(LV_PALETTE_GREEN));

  label = lv_label_create(lv_scr_act());
  assert(label);
  lv_label_set_text_static(label, "Person detected");
  lv_obj_align_to(label, person_indicator, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
  bsp_display_unlock();
}
#endif // DISPLAY_SUPPORT
int count = 0;
bool servomoving = false;
void servoMove()
{
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_13_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK,
      .deconfigure = false};

  ledc_timer_config(&ledc_timer);

  ledc_channel_config_t ledc_channel = {
      .gpio_num = 2,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = LEDC_TIMER_0,
      .duty = 409,
      .hpoint = 0};

  ledc_channel_config(&ledc_channel);

  int dutylist[4] = {409, 614, 818, 614};

  ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, dutylist[count % 4]);
  ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
}

void RespondToDetection(float person_score, float no_person_score)
{
  int person_score_int = (person_score) * 100 + 0.5;
  (void)no_person_score; // unused
#if DISPLAY_SUPPORT
  if (!camera_canvas)
  {
    create_gui();
  }

  uint16_t *buf = (uint16_t *)image_provider_get_display_buf();

  bsp_display_lock(0);
  if (person_score_int < 60)
  { // treat score less than 60% as no person
    lv_led_off(person_indicator);
  }
  else
  {
    lv_led_on(person_indicator);
  }
  lv_canvas_set_buffer(camera_canvas, buf, IMG_WD, IMG_HT, LV_IMG_CF_TRUE_COLOR);
  bsp_display_unlock();
#endif // DISPLAY_SUPPORT
  MicroPrintf("person score:%d%%, no person score %d%%",
              person_score_int, 100 - person_score_int);
  if (person_score_int > 85)
  {
    if (servomoving == false)
    {
      servomoving = true;
      count++;
      servoMove();
      servomoving = false;
    }
  }
}
