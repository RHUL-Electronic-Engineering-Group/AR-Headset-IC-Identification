import board
import digitalio
import adafruit_rgb_display.ili9341 as ili9341
import busio

# Set up the GPIO pins as SPI pins
spi_clk = digitalio.DigitalInOut(board.D11)
spi_mosi = digitalio.DigitalInOut(board.D10)
spi_dc = digitalio.DigitalInOut(board.D22)
spi_cs = digitalio.DigitalInOut(board.D8)

spi1= digitalio.DigitalInOut(board.D14)
spi2= digitalio.DigitalInOut(board.D15)
spi3= digitalio.DigitalInOut(board.D16)


spi_clk.direction = digitalio.Direction.OUTPUT
spi_mosi.direction = digitalio.Direction.OUTPUT
spi_dc.direction = digitalio.Direction.OUTPUT
spi_cs.direction = digitalio.Direction.OUTPUT

spi1.direction = digitalio.Direction.OUTPUT
spi2.direction = digitalio.Direction.OUTPUT
spi3.direction = digitalio.Direction.OUTPUT

spi1.value=False
spi2.value=True
spi3.value=True

# Create the SPI bus
spi = busio.SPI(clock=spi_clk, MOSI=spi_mosi)

# Create the display object
display = ili9341.ILI9341(spi, cs=spi_cs, dc=spi_dc)

# Create a new bitmap with "hello world" text
bitmap = displayio.Bitmap(240, 240, 1)
palette = displayio.Palette(1)
palette[0] = 0xFFFFFF
text_area = displayio.TileGrid(bitmap, pixel_shader=palette, x=0, y=0)
text_area[0,0] = 1
text_area[0,1] = 1
text_area[1,0] = 1
text_area[1,1] = 1
text_area[3,0] = 1
text_area[3,1] = 1
text_area[4,0] = 1
text_area[4,1] = 1
text_area[6,0] = 1
text_area[6,1] = 1
text_area[7,0] = 1
text_area[7,1] = 1
text_area[8,0] = 1
text_area[8,1] = 1
text_area[9,0] = 1
text_area[9,1] = 1
text_area[10,0] = 1
text_area[10,1] = 1

# Display the text on the screen
group = displayio.Group(max_size=1)
group.append(text_area)
display.show(group)

while True:
    pass

