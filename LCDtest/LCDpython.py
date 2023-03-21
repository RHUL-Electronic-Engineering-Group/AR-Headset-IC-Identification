import board
import busio
import digitalio
import adafruit_st7789 as st7789
import time
import math

spi = busio.SPI(board.SCK, MOSI=board.MOSI)

# Create the ST7789 display:
cs_pin = digitalio.DigitalInOut(board.CE0)
dc_pin = digitalio.DigitalInOut(board.D22)
reset_pin = digitalio.DigitalInOut(board.D13)
display = st7789.ST7789(spi, cs=cs_pin, dc=dc_pin, rst=reset_pin, width=240, height=240, rowstart=80, colstart=40)

p = 3.1415926

def tft_print_test():
    display.fill(st7789.BLACK)
    text_color = st7789.RED
    display.text("Test", 0, 30, text_color)
    text_color = st7789.YELLOW
    display.text("Test", 0, 50, text_color, 2)
    text_color = st7789.GREEN
    display.text("Test", 0, 80, text_color, 3)
    text_color = st7789.BLUE
    display.text(str(1234.567), 0, 120, text_color, 4)
    time.sleep(1.5)
    display.fill(st7789.BLACK)
    text_color = st7789.WHITE
    display.text("Test", 0, 0, text_color, 1)
    text_color = st7789.GREEN
    display.text("{:.6f} Test".format(p), 0, 20, text_color, 1)
    display.text(" ", 0, 40, text_color, 1)
    display.text("{:X} Print HEX!".format(8675309), 0, 60, text_color, 1)
    display.text(" ", 0, 80, text_color, 1)
    display.text("Sketch has been", 0, 100, text_color, 1)
    display.text("running for:", 0, 120, text_color, 1)
    text_color = st7789.MAGENTA
    display.text("{:.1f} seconds.".format(time.monotonic()), 0, 140, text_color, 1)

display.rotation = 270
display.invert(True)
tft_print_test()
time.sleep(1)
display.invert(False)
tft_print_test()
time.sleep(1)

