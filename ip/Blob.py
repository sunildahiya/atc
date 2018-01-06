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

  # cv2.namedWindow("contour", cv2.WINDOW_NORMAL)
  # cv2.imshow("contour", img_bw )
  # cv2.waitKey(0)
  # return blobs
  

#  void getBlobProps(Mat I, Blob* myBlobs)
# {
# 	vector<Vec4i> hierarchy;
# 	findContours(I, myBlobs->contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

# 	for (int i = 0; i<(myBlobs->contours).size(); i++) {
# 		vector<Point> contour = (myBlobs->contours)[i];
# 		(myBlobs->contourareas).push_back(contourArea(contour));
# 		Moments M = moments(contour);
# 		(myBlobs->centroids).push_back(Point(M.m10 / M.m00, M.m01 / M.m00));
# 		(myBlobs->dimension).push_back(*(new vector<double>));

# 		if ((myBlobs->contours)[i].size() > 5){
# 			RotatedRect ell = fitEllipse(Mat((myBlobs->contours)[i]));
# 			double a = ell.size.width / 2;    // width >= height
# 			double b = ell.size.height / 2;
# 			(myBlobs->dimension[(myBlobs->dimension).size() - 1]).push_back(ell.size.width);
# 			(myBlobs->dimension[(myBlobs->dimension).size() - 1]).push_back(ell.size.height);
# 			if (a > b)
# 				(myBlobs->eccentricity).push_back(0);
# 			else
# 				(myBlobs->eccentricity).push_back(sqrt(1 - (a*a) / (b*b)));
# 			(myBlobs->angle).push_back(ell.angle);
# 		}
# 		else{
# 			RotatedRect rect = minAreaRect(Mat(contour));
# 			(myBlobs->dimension[i]).push_back(rect.size.width);
# 			(myBlobs->dimension[i]).push_back(rect.size.height);
# 			//(myBlobs->eccentricity).push_back(sqrt(1 - (rect.size.width*rect.size.width) / (rect.size.height*rect.size.height)));
# 			(myBlobs->eccentricity).push_back(0);
# 			(myBlobs->angle).push_back(rect.angle);
# 		}
# 	}
# }
