try:
  import usocket as socket
except:
  import socket

from machine import Pin
import network, neopixel

import esp
esp.osdebug(None)
n=308
p=5

np = neopixel.NeoPixel(machine.Pin(p), n)

import gc
gc.collect()

ssid = 'BT-TGAHZR'
password = 'beqxyVRt6cGng7'

station = network.WLAN(network.STA_IF)

station.active(True)
station.connect(ssid , password)

while station.isconnected() == False:
  pass

print('Connection successful')
for i in range(308):
    np[i] = (0, 0, 0)
    np.write()
print(station.ifconfig())

led = Pin(2, Pin.OUT)



