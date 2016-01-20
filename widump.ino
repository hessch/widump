#include "ESP8266WiFi.h"
extern "C" {
#include "user_interface.h"
}
#include "network_80211.h"

void handle_pkt(uint8_t *buf, uint16 len) {
  if (len <= sizeof(struct RxControl)) return;
  struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
  for(int i = 0; i < sniffer->len[0]; i++) {
    Serial.printf("%02x ", sniffer->buf[i]);
    if (i > 15 && i % 16 == 0) Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  wifi_set_opmode(WIFI_STA);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(handle_pkt);
}

void loop() {  }
