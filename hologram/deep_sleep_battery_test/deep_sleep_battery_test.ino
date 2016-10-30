int check_interval_ms = 15 * 60 * 1000;

void setup() {
  Dash.begin();
  SerialUSB.begin(9600);
  SerialCloud.begin(115200);

  String init_msg = "Bat Mon test init";
  SerialUSB.println(init_msg);
  SerialCloud.println(init_msg);
}

void loop() {
  uint8_t bat_percent = Dash.batteryPercentage();
  uint32_t bat_mv = Dash.batteryMillivolts();

  // we're going to send a 3-byte package up to cloud
  // first byte is the bat_percent (never expect a percent over 100)
  // second byte is bits 9-16 of the bat_mv (never expect a mv reading over 64 volts...)
  // 3rd byte is bits 1-8 of the bat_mv

   char bat_msg[3];
   bat_msg[0] = bat_percent;
   bat_msg[1] = bat_mv / 256;
   bat_msg[2] = bat_mv % 256;

  SerialUSB.write(bat_msg, 3);
  SerialUSB.println();

  SerialCloud.write(bat_msg, 3);
  SerialCloud.println(); // does what you'd expect 'flush' to. appears newlines are used as packet delimiters.

  //SerialUSB.print(bat_percent);
  //SerialUSB.print(',');
  //SerialUSB.print(bat_mv);
  //SerialUSB.println();
  
  Dash.snooze(check_interval_ms);
}
