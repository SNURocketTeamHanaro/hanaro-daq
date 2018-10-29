/***************************************************************************
   Filename       : CombustionTest.ino
   Target machine : Arduino Uno

   Contributor    :
          rev.1 @ 2018. 07. 04.
                HANARO, SNU.
                Jaerin Lee
 ***************************************************************************/

#include <stdio.h>
//#include <SD.h>
#include <SPI.h>
#include "SdFat.h"

#define PRESSURE0 A0
#define PRESSURE1 A1
#define LOADCELL0 A3

#define INIT_DATA_DUMP_COUNT 10
#define INIT_DATA_AVG_COUNT 20

#define PERIOD_DATA_RETRIEVAL 5 // ms
#define MAX_DATA_NUM 10
#define SAVE_CYCLE 5

/*
struct data_packet_t {
  uint32_t current_time; // 4
  uint16_t pressure0;    // 2
  uint16_t pressure1;    // 2
  uint16_t loadcell0;    // 2
};

typedef union data_t {
  struct data_packet_t data_packet;
  char data_packet_string[sizeof(struct data_packet_t)];
  byte data_packet_bytestring[sizeof(struct data_packet_t)];
};

data_t data[MAX_DATA_NUM];
uint32_t datanum = 0;
*/

uint32_t save_cycle = 0;

SdFat SD;
File file_sd;
char file_name[50] = "data.txt";
char data_string[50];

/*
uint32_t curr_time;
uint32_t prev_time = 0;
*/

void setup() {
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);

  Serial.begin(115200);
  Serial.println("[  WORK] Initiate device configuration.");
  memset(data_string, '\0', sizeof(char) * 50);

/*
  while (1) {
    if (!SD.begin()) {
      digitalWrite(6, HIGH);
      Serial.println("[ ERROR] Device error: SD card.");
    } else {
      // Open a new file
      //memset(file_name, '\0', sizeof(char) * 50);
      //sprintf(file_name, "%d.txt", millis());
      file_sd = SD.open(file_name, FILE_WRITE); //O_CREAT | O_WRITE);
      file_sd.close();
      Serial.print("[STATUS] File opened: ");
      Serial.println(file_name);

      Serial.println("[STATUS] Start logging ...");
      break;
    }
  }
  */
}

void loop() {
  while (1) {
    uint32_t curr_time = millis();
    int pressure0 = analogRead(PRESSURE0);
    int pressure1 = analogRead(PRESSURE1);
    int loadcell0 = analogRead(LOADCELL0);
    sprintf(data_string, "%lu\t%d\t%d\t%d", curr_time, pressure0, pressure1, loadcell0);
    //float pressure0_val = 1.0f + ((((float)pressure0 / 1024) * 5.0f / 0.3254f) - 4) * 100 / 16;
    //float pressure1_val = 1.0f + ((((float)pressure0 / 1024) * 5.0f / 0.3254f) - 4) * 100 / 16;
    //float loadcell0_val = (((loadcell0 / 1024) * 5000.0f) - 34.9) / 4728.72 * 200;
    //sprintf(data_string, "%lu\t%f\t%f\t%f", curr_time, pressure0_val, pressure1_val, loadcell0_val);
    /*
    file_sd = SD.open(file_name, FILE_WRITE); //O_CREAT | O_WRITE);
    file_sd.println(data_string);
    file_sd.close();
    */
    Serial.println(data_string);
    //++save_cycle;
    //if (save_cycle >= SAVE_CYCLE) {
    //  save_cycle = 0;
    //  file_sd.close();
    //  file_sd = SD.open(file_name, FILE_WRITE); //O_CREAT | O_WRITE);
    //}
    delayMicroseconds(PERIOD_DATA_RETRIEVAL * 1000);
  }

  /*
  curr_time = millis();
  if (curr_time - prev_time >= PERIOD_DATA_RETRIEVAL) {
    prev_time = curr_time;

    // Package remaining data
    data[datanum].data_packet.current_time = curr_time;
    data[datanum].data_packet.pressure0 = analogRead(PRESSURE0);
    data[datanum].data_packet.pressure1 = analogRead(PRESSURE1);
    data[datanum].data_packet.loadcell0 = analogRead(LOADCELL0);

    // Next data
    ++datanum;
  }
  */

/*
  if (datanum == MAX_DATA_NUM - 1) {
    // Assume no problem with either the SD card or the connection

    // Write the whole data
    for (uint32_t i = 0; i < datanum; ++i) {
      file_sd.write('$'); // Start character
      file_sd.write('$'); // Start character
      file_sd.write(data[i].data_packet_bytestring, sizeof(struct data_packet_t));
      file_sd.write('#'); // End character
      file_sd.write('#'); // End character 
    }

    // Reset data buffer; go closer to the next saving cycle
    datanum = 0;
    ++save_cycle;

    // Save the file into the SD card
    if (save_cycle >= SAVE_CYCLE) {
      save_cycle = 0;

      file_sd.close();
      file_sd = SD.open(file_name, FILE_WRITE); //O_CREAT | O_WRITE);

      Serial.print("[STATUS] Data saved at ");
      Serial.print(millis());
      Serial.println("ms.");
    }
  }
  */
}
