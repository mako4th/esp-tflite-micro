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

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_

#include "sensor.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "esp_system.h"

#include "esp_main.h"

/**
 * PIXFORMAT_RGB565,    // 2BPP/RGB565
 * PIXFORMAT_YUV422,    // 2BPP/YUV422
 * PIXFORMAT_GRAYSCALE, // 1BPP/GRAYSCALE
 * PIXFORMAT_JPEG,      // JPEG/COMPRESSED
 * PIXFORMAT_RGB888,    // 3BPP/RGB888
 */
#if defined DISPLAY_SUPPORT
#define CAMERA_PIXEL_FORMAT PIXFORMAT_RGB565
#else
#define CAMERA_PIXEL_FORMAT PIXFORMAT_GRAYSCALE
#endif
/*
 * FRAMESIZE_96X96,    // 96x96
 * FRAMESIZE_QQVGA,    // 160x120
 * FRAMESIZE_QQVGA2,   // 128x160
 * FRAMESIZE_QCIF,     // 176x144
 * FRAMESIZE_HQVGA,    // 240x176
 * FRAMESIZE_QVGA,     // 320x240
 * FRAMESIZE_CIF,      // 400x296
 * FRAMESIZE_VGA,      // 640x480
 * FRAMESIZE_SVGA,     // 800x600
 * FRAMESIZE_XGA,      // 1024x768
 * FRAMESIZE_SXGA,     // 1280x1024
 * FRAMESIZE_UXGA,     // 1600x1200
 */
#define CAMERA_FRAME_SIZE FRAMESIZE_96X96

#define CAMERA_MODULE_NAME "XIAO ESP32S3 Sense"

#define CAMERA_PIN_PWDN   -1
#define CAMERA_PIN_RESET  -1
#define CAMERA_PIN_XCLK   10
#define CAMERA_PIN_SIOD   40
#define CAMERA_PIN_SIOC   39

#define CAMERA_PIN_D7     48
#define CAMERA_PIN_D6     11
#define CAMERA_PIN_D5     12
#define CAMERA_PIN_D4     14
#define CAMERA_PIN_D3     16
#define CAMERA_PIN_D2     18
#define CAMERA_PIN_D1     17
#define CAMERA_PIN_D0     15

#define CAMERA_PIN_VSYNC  38
#define CAMERA_PIN_HREF   47
#define CAMERA_PIN_PCLK   13


#if CONFIG_CAMERA_MODULE_WROVER_KIT
#define CAMERA_MODULE_NAME "Wrover Kit"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET -1
#define CAMERA_PIN_XCLK 21
#define CAMERA_PIN_SIOD 26
#define CAMERA_PIN_SIOC 27

#define CAMERA_PIN_D7 35
#define CAMERA_PIN_D6 34
#define CAMERA_PIN_D5 39
#define CAMERA_PIN_D4 36
#define CAMERA_PIN_D3 19
#define CAMERA_PIN_D2 18
#define CAMERA_PIN_D1 5
#define CAMERA_PIN_D0 4
#define CAMERA_PIN_VSYNC 25
#define CAMERA_PIN_HREF 23
#define CAMERA_PIN_PCLK 22

#elif CONFIG_CAMERA_MODULE_ESP_EYE
#define CAMERA_MODULE_NAME "ESP-EYE"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET -1
#define CAMERA_PIN_XCLK 4
#define CAMERA_PIN_SIOD 18
#define CAMERA_PIN_SIOC 23

#define CAMERA_PIN_D7 36
#define CAMERA_PIN_D6 37
#define CAMERA_PIN_D5 38
#define CAMERA_PIN_D4 39
#define CAMERA_PIN_D3 35
#define CAMERA_PIN_D2 14
#define CAMERA_PIN_D1 13
#define CAMERA_PIN_D0 34
#define CAMERA_PIN_VSYNC 5
#define CAMERA_PIN_HREF 27
#define CAMERA_PIN_PCLK 25

#elif CONFIG_CAMERA_MODULE_ESP_S2_KALUGA
#define CAMERA_MODULE_NAME "ESP-S2-KALUGA"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET -1
#define CAMERA_PIN_XCLK 1
#define CAMERA_PIN_SIOD 8
#define CAMERA_PIN_SIOC 7

#define CAMERA_PIN_D7 38
#define CAMERA_PIN_D6 21
#define CAMERA_PIN_D5 40
#define CAMERA_PIN_D4 39
#define CAMERA_PIN_D3 42
#define CAMERA_PIN_D2 41
#define CAMERA_PIN_D1 37
#define CAMERA_PIN_D0 36
#define CAMERA_PIN_VSYNC 2
#define CAMERA_PIN_HREF 3
#define CAMERA_PIN_PCLK 33

#elif CONFIG_CAMERA_MODULE_ESP_S3_EYE
// #define CAMERA_MODULE_NAME "ESP-S3-EYE"
// #define CAMERA_PIN_PWDN -1
// #define CAMERA_PIN_RESET -1

// #define CAMERA_PIN_VSYNC 6
// #define CAMERA_PIN_HREF 7
// #define CAMERA_PIN_PCLK 13
// #define CAMERA_PIN_XCLK 15

// #define CAMERA_PIN_SIOD 4
// #define CAMERA_PIN_SIOC 5

// #define CAMERA_PIN_D0 11
// #define CAMERA_PIN_D1 9
// #define CAMERA_PIN_D2 8
// #define CAMERA_PIN_D3 10
// #define CAMERA_PIN_D4 12
// #define CAMERA_PIN_D5 18
// #define CAMERA_PIN_D6 17
// #define CAMERA_PIN_D7 16

#elif CONFIG_CAMERA_MODULE_ESP32_CAM_BOARD
#define CAMERA_MODULE_NAME "ESP-DEVCAM"
#define CAMERA_PIN_PWDN 32
#define CAMERA_PIN_RESET 33

#define CAMERA_PIN_XCLK 4
#define CAMERA_PIN_SIOD 18
#define CAMERA_PIN_SIOC 23

#define CAMERA_PIN_D7 36
#define CAMERA_PIN_D6 19
#define CAMERA_PIN_D5 21
#define CAMERA_PIN_D4 39
#define CAMERA_PIN_D3 35
#define CAMERA_PIN_D2 14
#define CAMERA_PIN_D1 13
#define CAMERA_PIN_D0 34
#define CAMERA_PIN_VSYNC 5
#define CAMERA_PIN_HREF 27
#define CAMERA_PIN_PCLK 25

#elif CONFIG_CAMERA_MODULE_M5STACK_PSRAM
#define CAMERA_MODULE_NAME "M5STACK-PSRAM"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET 15

#define CAMERA_PIN_XCLK 27
#define CAMERA_PIN_SIOD 25
#define CAMERA_PIN_SIOC 23

#define CAMERA_PIN_D7 19
#define CAMERA_PIN_D6 36
#define CAMERA_PIN_D5 18
#define CAMERA_PIN_D4 39
#define CAMERA_PIN_D3 5
#define CAMERA_PIN_D2 34
#define CAMERA_PIN_D1 35
#define CAMERA_PIN_D0 32
#define CAMERA_PIN_VSYNC 22
#define CAMERA_PIN_HREF 26
#define CAMERA_PIN_PCLK 21

#elif CONFIG_CAMERA_MODULE_M5STACK_WIDE
#define CAMERA_MODULE_NAME "M5STACK-WIDE"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET 15
#define CAMERA_PIN_XCLK 27
#define CAMERA_PIN_SIOD 22
#define CAMERA_PIN_SIOC 23

#define CAMERA_PIN_D7 19
#define CAMERA_PIN_D6 36
#define CAMERA_PIN_D5 18
#define CAMERA_PIN_D4 39
#define CAMERA_PIN_D3 5
#define CAMERA_PIN_D2 34
#define CAMERA_PIN_D1 35
#define CAMERA_PIN_D0 32
#define CAMERA_PIN_VSYNC 25
#define CAMERA_PIN_HREF 26
#define CAMERA_PIN_PCLK 21

#elif CONFIG_CAMERA_MODULE_AI_THINKER
#define CAMERA_MODULE_NAME "AI-THINKER"
#define CAMERA_PIN_PWDN 32
#define CAMERA_PIN_RESET -1
#define CAMERA_PIN_XCLK 0
#define CAMERA_PIN_SIOD 26
#define CAMERA_PIN_SIOC 27

#define CAMERA_PIN_D7 35
#define CAMERA_PIN_D6 34
#define CAMERA_PIN_D5 39
#define CAMERA_PIN_D4 36
#define CAMERA_PIN_D3 21
#define CAMERA_PIN_D2 19
#define CAMERA_PIN_D1 18
#define CAMERA_PIN_D0 5
#define CAMERA_PIN_VSYNC 25
#define CAMERA_PIN_HREF 23
#define CAMERA_PIN_PCLK 22

#elif CONFIG_CAMERA_MODULE_CUSTOM
#define CAMERA_MODULE_NAME "CUSTOM"
#define CAMERA_PIN_PWDN CONFIG_CAMERA_PIN_PWDN
#define CAMERA_PIN_RESET CONFIG_CAMERA_PIN_RESET
#define CAMERA_PIN_XCLK CONFIG_CAMERA_PIN_XCLK
#define CAMERA_PIN_SIOD CONFIG_CAMERA_PIN_SIOD
#define CAMERA_PIN_SIOC CONFIG_CAMERA_PIN_SIOC

#define CAMERA_PIN_D7 CONFIG_CAMERA_PIN_Y9
#define CAMERA_PIN_D6 CONFIG_CAMERA_PIN_Y8
#define CAMERA_PIN_D5 CONFIG_CAMERA_PIN_Y7
#define CAMERA_PIN_D4 CONFIG_CAMERA_PIN_Y6
#define CAMERA_PIN_D3 CONFIG_CAMERA_PIN_Y5
#define CAMERA_PIN_D2 CONFIG_CAMERA_PIN_Y4
#define CAMERA_PIN_D1 CONFIG_CAMERA_PIN_Y3
#define CAMERA_PIN_D0 CONFIG_CAMERA_PIN_Y2
#define CAMERA_PIN_VSYNC CONFIG_CAMERA_PIN_VSYNC
#define CAMERA_PIN_HREF CONFIG_CAMERA_PIN_HREF
#define CAMERA_PIN_PCLK CONFIG_CAMERA_PIN_PCLK
#endif

#define XCLK_FREQ_HZ 15000000

#ifdef __cplusplus
extern "C" {
#endif

int app_camera_init();

#ifdef __cplusplus
}
#endif

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_
