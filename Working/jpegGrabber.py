import requests # request img from web
from PIL import Image

url = "https://i.imgur.com/ke78nj5.jpeg"
filename = "cat.jpeg"

im = Image.open(requests.get(url, stream=True).raw)             #pull image from url provided
im = im.save(filename)                                          #save image
