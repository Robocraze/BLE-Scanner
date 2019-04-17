# BLE-Scanner
A simple example to develop a BLE Scanner using ESP32. It uses at least 2 ESP devices. The devices are classified into 2 types:

    • Server
    • Client
  
In this example, the following steps are performed

    • The server device, also called Advertised device, broadcasts a BLE Server 
    • The client or scanner device scans for various advertised devices
    • Checks if our device is present among them and returns its RSSI
    • The RSSI value is then used to actuate the buzzer connected to the client device
    • The repetition intensity of beeps represent proximity of the client from the server

This particular example can be used to play a Treasure Hunt game.
