import cv2
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.patches as patches
import matplotlib.path as path
from Point import *
from util_func import *
from Blob import *
from merge_blobs import *

def median_filter(img, kernel) :
    img_shape = img.shape
    ki = int(kernel[0] / 2)
    kj = int(kernel[1] / 2)
    kernelSize = int((kernel[0] * kernel[1])/2)
    zero = np.zeros(img_shape[1], dtype=np.int32)
    imgMedian = np.zeros(img_shape, dtype=np.uint8)
    for i in range(0, img_shape[1]) :
        zero[i] = 0
    
    for i in range(0, kernel[0]):
        for j in range(0, img_shape[1]):
            color = img[i, j]
            if (color == 0):
                zero[j] += 1

    zeroKernel = 0
    for i in range(0, kernel[1]) :
        zeroKernel += zero[i]


    for i in range(ki, img_shape[0]-ki-1): 
        for j in range(kj, img_shape[1]-kj):
            if (j == kj):
                if (zeroKernel <= kernelSize):
                    imgMedian[i, j] = 255
                else:
                    imgMedian[i, j] = 0;
            else:
                zeroKernel -= zero[j-kj-1]
                zeroKernel += zero[j+kj]
                if (zeroKernel <= kernelSize):
                    imgMedian[i, j] = 255
                else:
                    imgMedian[i, j] = 0;


        for k in range (0, img_shape[1]):
            color = img[i-ki, k]
            color2 = img[i+ki+1, k]
            value1 = 1 if (color == 0) else 0
            value2 = 1 if (color2 == 0) else 0
        zeroKernel = 0
        for i in range(0, kernel[1]):
            zeroKernel += zero[k]
    return imgMedian


def hist_maxima(hist, kernel):
    if (kernel%2 != 0):
        kernel += 1

    # plt.plot(hist)
    # plt.xlim([0,256])
    # plt.show()
    startPos = int(kernel/2)
    endPos = int(254-kernel/2)

    maxFirst = 0
    maxSecond = 0
    maxFirstPos = int(kernel/2)
    maxSecondPos = int(kernel/2)
    current = 0

    for i in range(0, kernel):
        current += hist[i, 0]

    for i in range(startPos, endPos):
        if (maxFirst < current):
            maxFirst = current
            maxFirstPos = i
        
        current -= hist[int(i-kernel/2), 0]
        current += hist[int(i+kernel/2+1), 0]

    if (maxFirst < current):
        maxFirst = current
        maxFirstPos = int(255-kernel/2)
    

    current = 0
    for i in range(0, kernel):
        current += hist[i, 0]

    for i in range(startPos, endPos):
        if (maxSecond < current and abs(i-maxFirstPos) > 25):
            maxSecond = current
            maxSecondPos = i
        current -= hist[int(i-kernel/2), 0]
        current += hist[int(i+kernel/2+1), 0]
    return (maxFirstPos, maxSecondPos, maxFirst, maxSecond)


def get_stains_pos(img_gray, kernelImg, kernelHist):
    if (kernelImg[0]%2 != 0):
        kernelImg[0] += 1
    if (kernelImg[1]%2 != 0):
        kernelImg[1] += 1
    
    imgShape = img_gray.shape
    (maxFirstPos, maxSecondPos, maxFirst, maxSecond) = (0, 0, 0, 0)

    img = np.zeros(imgShape, dtype=np.uint8)
    for i in range(0, imgShape[0], kernelImg[0]):
        for j in range(0, imgShape[1], kernelImg[1]):
            hist = cv2.calcHist([img_gray[i:i+kernelImg[0], j:j+kernelImg[1]]],[0],None,[256],[0,256])
            (maxFirstPos, maxSecondPos, maxFirst, maxSecond) = hist_maxima(hist, kernelHist)
            if ((maxFirstPos - maxSecondPos) > 20):
                if (maxFirstPos < maxSecondPos):
                    maxSecond = maxFirst
                    maxSecondPos = maxFirstPos
                if (maxSecond > 500):
                    # plt.plot(hist), plt.show()
                    # ret, img_lower = cv2.threshold(img_gray[i:i+kernelImg[0], j:j+kernelImg[1]], 50, 255, cv2.THRESH_BINARY)
                    # ret, img_upper = cv2.threshold(img_gray[i:i+kernelImg[0], j:j+kernelImg[1]], 150, 255, cv2.THRESH_BINARY_INV)
                    ret, img_lower = cv2.threshold(img_gray[i:i+kernelImg[0], j:j+kernelImg[1]], maxSecondPos-kernelHist, 255, cv2.THRESH_BINARY)
                    ret, img_upper = cv2.threshold(img_gray[i:i+kernelImg[0], j:j+kernelImg[1]], maxSecondPos+kernelHist, 255, cv2.THRESH_BINARY_INV)
                    img[i:i+kernelImg[0], j:j+kernelImg[1]] = cv2.bitwise_and(img_lower, img_upper)
                    img2 = img[i:i+kernelImg[0], j:j+kernelImg[1]]
                    # cv2.namedWindow("Or", cv2.WINDOW_NORMAL)
                    # cv2.namedWindow("Gr", cv2.WINDOW_NORMAL)

                    # cv2.imshow("Or", img2)
                    # cv2.imshow("Gr", img_gray[i:i+kernelImg[0], j:j+kernelImg[1]])
                    # cv2.waitKey(0)
            # print((maxFirstPos, maxSecondPos, maxFirst, maxSecond))
    return img

