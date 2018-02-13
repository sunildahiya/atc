from ptrans import get_world_coordinates
import cv2

# <----------------------------- ptrans module tested --------------------------------------------->
img = cv2.imread('3.jpg')
cv2.namedWindow('Viewer', cv2.WINDOW_NORMAL)
cv2.imshow('Viewer', img)
while not cv2.waitKey(1) & 0xFF == ord('q'):
    continue
refCorners = [[1186, 2020], [1837, 2006], [1838, 1613], [1166, 1614]]
corners = [[660, 2447], [2363, 2363], [2447, 913], [471, 844]]
for i in range(0, 4):
    print(get_world_coordinates(refCorners[0][0], refCorners[0][1], refCorners[1][0], refCorners[1][1], refCorners[2][0], refCorners[2][1], refCorners[3][0], refCorners[3][1], corners[i][0], corners[i][1], 29.8, 20.55))
print(get_world_coordinates(refCorners[0][0], refCorners[0][1], refCorners[1][0], refCorners[1][1], refCorners[2][0], refCorners[2][1], refCorners[3][0], refCorners[3][1], 3222, 918, 29.8, 20.55))
print (refCorners[0][0])

#  <---------------------------- merge_blobs modules test ----------------------------->
from Point import *
from merge_blobs import *

mainBlobs = [[Point(40, 30), 3], [Point(10, 5), 4], [Point(2, 5), 1], [Point(40, 29), 5]]
sorted(mainBlobs, key=lambda item: item[1], reverse=True)
splitBlobs = []
print(mainBlobs)
mainBlobs = merge_points(mainBlobs, splitBlobs, 5)
print(mainBlobs)