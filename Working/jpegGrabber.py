import requests # request img from web
from PIL import Image

url = "http://192.168.1.64/saved-photo"
filename = "Snapshot.jpeg"

im = Image.open(requests.get(url, stream=True).raw)             #pull image from url provided
im = im.save(filename)                                          #save image
