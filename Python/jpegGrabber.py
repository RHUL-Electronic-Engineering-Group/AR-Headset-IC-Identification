import requests # request img from web
from PIL import Image

url = "http://192.168.1.66/capture"
filename = "Snapshot.jpeg"

im = Image.open(requests.get(url, stream=True).raw)             #pull image from url provided
im = im.save(filename)                                          #save image
