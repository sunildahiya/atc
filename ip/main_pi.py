from picamera.array import PiRGBArray
from picamera import PiCamera
from format_change import *
import cv2
import time
import numpy as np

import serial

from staindet import *
from Point import *
from util_func import *
from Blob import *
from merge_blobs import *
from ptrans import *

STAINS_IMG_KERNEL = [200, 200]
STAINS_HIST_KERNEL = 20
STAINS_MEDIANBLUR_THRESH = 21
STAINS_CONTOURAREA_THRESH = 4000
STAINS_MERGE_MAXDIST = 500

SERIAL_START_CHAR = "\n"
SERIAL_END_CHAR = "\n"

ref_x1 = 653
ref_y1 = 72
ref_x2 = 173
ref_y2 = 62
ref_x3 = 202
ref_y3 = 417
ref_x4 = 598
ref_y4 = 437
length = 42.5
width = 45.2

camera = PiCamera()
rawCapture = PiRGBArray(camera)
 
# # allow the camera to warmup
time.sleep(5)
port = serial.Serial("/dev/ttyACM0", baudrate=115200, timeout=3.0)
recv = port.read(1);

# grab an image from the camera
while (1):
    while (bytes_to_int(port.read(1)) != 51):
        if (bytes_to_int(port.read(1)) == 52):
            break
        continue
    camera.capture(rawCapture, format="bgr")
    img = rawCapture.array

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

    stainsPos = []
    print("blob")
    finalBlobs
    for i in range(0, len(finalBlobs)):
        stainsPos.append(get_world_coordinates(ref_x1, ref_y1, ref_x2, ref_y2, ref_x3, ref_y3, ref_x4, ref_y4, finalBlobs[i][0].x, finalBlobs[i][0].y, length, width))

    # print(len(stainsPos))
    for i in range(0, len(stainsPos)):
        port.write( bytes[ int(stainsPos[i][1]) ] )
        print(port.read(1))
    cv2.imwrite("Blobs.png", img_gray)
    cv2.imwrite("FinalBlobs.png", img)
    # for i in range(0, len(finalBlobs)):

    # display the image on screen and wait for a keypress
    # cv2.imshow("Image", image)
    # cv2.waitKey(0)