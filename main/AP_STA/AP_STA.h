#ifndef __ACCESS_POINT_H__
#define __ACCESS_POINT_H__

#include <stdio.h>
#include "esp_log.h"
#include <string.h>
#include <esp_err.h>

#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

class AP_STA
{

private:
    int m_channel;
    int m_ssid_hidden;
    int m_max_connections;
    int m_beacon_interval;
    bool m_long_range;
    wifi_config_t ap;

public:
    AP_STA(char *STA_SSID, char *STA_PASSWORD, char *AP_SSID, char *AP_PASSWORD);
    ~AP_STA();
    bool start();
    bool stop();

private:
};

#endif