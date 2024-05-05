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
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");

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
    }
    else
    {
        AP_STA *wifi = new AP_STA("Kubascik", "kubascik25", "Generator", "123456789");
        uint32_t delay = atoi(cJSON_GetObjectItem(dev_cfg, "delay")->valuestring);
        char *api_key = cJSON_GetObjectItem(dev_cfg, "API_KEY")->valuestring;
    }
    HTTP_Server *server = new HTTP_Server(nvs);
    server->init();
    while (true)
    {
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        sendDataToThingy("J8WA1NS5ADC4FMED", rand() % 100, rand() % 100, rand() % 100);
    }
}
