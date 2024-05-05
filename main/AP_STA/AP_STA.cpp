#include "AP_STA.h"

AP_STA::AP_STA(char *STA_SSID, char *STA_PASSWORD, char *AP_SSID, char *AP_PASSWORD)
{
    
	ESP_ERROR_CHECK(esp_netif_init());
    EventGroupHandle_t wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_event_loop_create_default());
	esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
	assert(ap_netif);
	esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
	assert(sta_netif);
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_NULL) );
	ESP_ERROR_CHECK( esp_wifi_start() );
    const int CONNECTED_BIT = BIT0;

    wifi_config_t ap_config = {0};
    sprintf(reinterpret_cast<char *>(ap_config.ap.ssid), AP_SSID);
    sprintf(reinterpret_cast<char *>(ap_config.ap.password), AP_PASSWORD);
    ap_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    ap_config.ap.ssid_len = strlen(AP_SSID);
    ap_config.ap.max_connection = 10;
    ap_config.ap.channel = 0;
    printf("AP_DONE\n\r");
    if (strlen(AP_PASSWORD) == 0)
    {
        ap_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    wifi_config_t sta_config = {0};
    
    sprintf(reinterpret_cast<char *>(sta_config.sta.ssid), STA_SSID);
    sprintf(reinterpret_cast<char *>(sta_config.sta.password), STA_PASSWORD);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap_config));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_wifi_connect());
    int bits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                                   pdFALSE, pdTRUE, 5000 / portTICK_PERIOD_MS);
}

AP_STA::~AP_STA()
{
}

bool AP_STA::start()
{
    return true;
}
bool AP_STA::stop()
{
    return true;
}

