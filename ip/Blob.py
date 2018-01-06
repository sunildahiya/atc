import cv2
from Point import *

class Blob:
  def __init__(self):
    self.contours = []
    self.centroids = []
    self.contourareas = []
  

def getBlobProps(img_bw):
  # Blob blobs
  blobs = Blob()
  im2, blobs.contours, hierarchy = cv2.findContours(img_bw, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
  
  cv2.drawContours(img_bw, blobs.contours, -1, (0,255,0), 23)
  
  for i in range(0, len(blobs.contours)):
    contour = blobs.contours[i]
    moment = cv2.moments(contour)
    if (moment['m00'] == 0 or  moment['m00'] == 0):
      continue
    # print(int(moment['m10'] / moment['m00']), int(moment['m01'] / moment['m00']))
    blobs.centroids.append( Point( int(moment['m10'] / moment['m00']), int(moment['m01'] / moment['m00'])) )
    blobs.contourareas.append(cv2.contourArea(contour))
  return blobs
