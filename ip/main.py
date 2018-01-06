
# from picamera.array import PiRGBArray
# from picamera import PiCamera
import cv2
import time
import numpy as np

from matplotlib import pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.patches as patches
import matplotlib.path as path

from staindet import *
from Point import *
from util_func import *
from Blob import *
from merge_blobs import *

STAINS_IMG_KERNEL = [200, 200]
STAINS_HIST_KERNEL = 20
STAINS_MEDIANBLUR_THRESH = 21
STAINS_CONTOURAREA_THRESH = 4000
STAINS_MERGE_MAXDIST = 500

SERIAL_START_CHAR = "\n"
SERIAL_END_CHAR = "\n"

# initialize the camera and grab a reference to the raw camera capture
# camera = PiCamera()
# rawCapture = PiRGBArray(camera)
 
# # allow the camera to warmup
# time.sleep(0.1)
 
# grab an image from the camera
# camera.capture(rawCapture, format="bgr")
# img = rawCapture.array
img = cv2.imread('Resources/stain1.jpg')
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img_gray = cv2.GaussianBlur(img_gray, (9, 9), 0)

img_bw = get_stains_pos(img_gray, STAINS_IMG_KERNEL, STAINS_HIST_KERNEL)
img_bw = cv2.medianBlur(img_bw, STAINS_MEDIANBLUR_THRESH)

blobs  = getBlobProps(img_bw)

mainBlobs = []
splitBlobs = []


for i in range(0, len(blobs.centroids)):
    cv2.circle(img_gray, blobs.centroids[i].as_tuple(), 63, (255, 0, 0), -1)

for i in range(0, len(blobs.contourareas)):
    if (blobs.contourareas[i] > STAINS_CONTOURAREA_THRESH):
        mainBlobs.append( [blobs.centroids[i], blobs.contourareas[i]] )        
    else:
        splitBlobs.append( [blobs.centroids[i], blobs.contourareas[i]] )

finalBlobs = merge_blobs(mainBlobs, splitBlobs, STAINS_MERGE_MAXDIST)
# for i in range(0, len(finalBlobs)):
#     print(finalBlobs[i])
for i in range(0, len(finalBlobs)):
    cv2.circle(img, finalBlobs[i][0].as_tuple(), 63, (255, 0, 0), -1)

print(len(finalBlobs))
cv2.namedWindow("Blob", cv2.WINDOW_NORMAL)
cv2.imshow("Blob", img)
cv2.namedWindow("Blob Prev", cv2.WINDOW_NORMAL)
cv2.imshow("Blob Prev", img_gray)
cv2.namedWindow("Blob BW", cv2.WINDOW_NORMAL)
cv2.imshow("Blob BW", img_bw)

cv2.waitKey(0)
# for i in range(0, len(finalBlobs)):

# display the image on screen and wait for a keypress
# cv2.imshow("Image", image)
# cv2.waitKey(0)