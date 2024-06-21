/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "AP_STA/AP_STA.h"
#include "NVS/NVS.h"
#include "HTTP_Server/HTTP_Server.h"
#include "driver/ledc.h"
#include "rom/ets_sys.h"
#include "esp_http_client.h"

extern "C"
{
    void app_main(void);
}

void sendDataToThingy(const char *API_KEY, double temp, double hum, double lux)
{
    char thingspeak_url[] = "http://api.thingspeak.com/update?api_key=%s&field1=%.2f&field2=%.2f&field3=%.2f";
    char post_data[200];
    esp_err_t err;
    strcpy(post_data, "");
    snprintf(post_data, sizeof(post_data), thingspeak_url, API_KEY, temp, hum, lux);
    printf("%s\n\r", post_data);

    esp_http_client_config_t config = {
        .url = post_data,
        .method = HTTP_METHOD_GET,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
        

    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        int status_code = esp_http_client_get_status_code(client);
        if (status_code == 200)
        {
            ESP_LOGI("Thing", "Message sent Successfully");
        }
        else
        {
            ESP_LOGI("Thing", "Message sent Failed");
        }
    }
    else
    {
        ESP_LOGI("Thing", "Message sent Failed");
    }

    esp_http_client_cleanup(client);
}

void app_main(void)
{
    NVS *nvs = new NVS();
    cJSON *dev_cfg = nvs->getConfig();
    if (dev_cfg == NULL)
    {
        AP_STA *wifi = new AP_STA("Kubascik", "kubascik25", "Generator", "123456789");
        HTTP_Server *server = new HTTP_Server(nvs);
        server->init();
    }

    else
    {
        uint32_t delay = atoi(cJSON_GetObjectItem(dev_cfg, "delay")->valuestring);
        char *api_key = cJSON_GetObjectItem(dev_cfg, "API_KEY")->valuestring;
        char *SSID = cJSON_GetObjectItem(dev_cfg, "SSID")->valuestring;
        char *PASSWORD = cJSON_GetObjectItem(dev_cfg, "PASSWORD")->valuestring;
#define DEV1
#ifdef DEV1
        AP_STA *wifi = new AP_STA(SSID, PASSWORD, "DEV1", "123456789");
#endif
#ifdef DEV2
        AP_STA *wifi = new AP_STA(SSID, PASSWORD, "DEV2", "123456789");
#endif
#ifdef DEV3
        AP_STA *wifi = new AP_STA(SSID, PASSWORD, "DEV3", "123456789");
#endif
#ifdef DEV4
        AP_STA *wifi = new AP_STA(SSID, PASSWORD, "DEV4", "123456789");
#endif
#ifdef DEV5
        AP_STA *wifi = new AP_STA(SSID, PASSWORD, "DEV5", "123456789");
#endif
#ifdef DEV6
        AP_STA *wifi = new AP_STA(SSID, PASSWORD, "DEV6", "123456789");
#endif
        HTTP_Server *server = new HTTP_Server(nvs);
        server->init();
        while (true)
        {
            vTaskDelay(delay*1000 / portTICK_PERIOD_MS);
            sendDataToThingy(api_key, rand() % 100, rand() % 100, rand() % 100);
        }
    }
}
