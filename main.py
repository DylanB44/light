
from machine import Pin
import machine, neopixel, time

n = 308
p = 5

np = neopixel.NeoPixel(machine.Pin(p), n)


def rainbow_cycle(wait):
  for j in range(255):
    for i in range(n):
      rc_index = (i * 256 // n) + j
      np[i] = wheel(rc_index & 255)
    np.write()
    time.sleep_ms(wait)

def bounce(r, g, b, wait):
  for i in range(2 * n):
    for j in range(n):
      np[j] = (r, g, b)
    if (i // n) % 2 == 0:
      np[i % n] = (0, 0, 0)
    else:
      np[n - 1 - (i % n)] = (0, 0, 0)
    np.write()
    time.sleep_ms(wait)

def clear():
  for i in range(n):
    np[i] = (0, 0, 0)
    np.write()

def wheel(pos):
  
  if pos < 0 or pos > 255:
    return (0, 0, 0)
  if pos < 85:
    return (255 - pos * 3, pos * 3, 0)
  if pos < 170:
    pos -= 85
    return (0, 255 - pos * 3, pos * 3)
  pos -= 170
  return (pos * 3, 0, 255 - pos * 3)


def cycle(r, g, b, wait):
  for i in range(n):
    for j in range(n):
      np[j] = (0, 0, 0)
    np[i % n] = (r, g, b)
    np.write()
    time.sleep_ms(wait)




def web_page():

  
  html = """<html><head> <title>py web Server</title> <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,"> <style>html{font-family: Helvetica; display:inline-block; margin: 0px auto; text-align: center;}
  h1{color: #0F3376; padding: 2vh;}p{font-size: 1.5rem;}.button{display: inline-block; background-color: #e7bd3b; border: none; 
  border-radius: 4px; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
  .button2{background-color: #4286f4;}</style></head><body> <h1>ESP Web Server</h1> 
  <p>GPIO state: <strong></strong></p><p><a href="/?led=on"><button class="button">ON</button></a></p>
  <p><a href="/?led=off"><button class="button button2">OFF</button></a></p></body></html>"""
  return html
  
  #i know the html isnt really necessary but its useful for troubleshooting with siri, i dont think it should be the reason for it slowing down too much either.

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 80))
s.listen(5)

while True:
  conn, addr = s.accept()
  print('Got a connection from %s' % str(addr))
  request = conn.recv(1024)
  request = str(request)
  print('Content = %s' % request)
  rainbow = request.find('/r')
  led_off = request.find('/o')
  if rainbow == 6:
    wheel(254)
    rainbow_cycle(200)
  if led_off == 6:
    print('lights off')
    led.value(0)
    clear()
  response = web_page()
  conn.send('HTTP/1.1 200 OK\n')
  conn.send('Content-Type: text/html\n')
  conn.send('Connection: close\n\n')
  conn.sendall(response)
  conn.close()


