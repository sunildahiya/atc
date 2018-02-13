import cv2

def find_commode(imgHSV, requiredPoints) :
    imgHist = cv2.calcHist([imgHSV],[0],None,[256],[0,256])
    threshold = 0;
    count = 0
    for i in range(0, 255):
        count += imgHist[i]
    print('Count: ', count)
    height, width = imgHSV.shape[:2]
    print('Points: ', height*width)
    while (requiredPoints>0):
        requiredPoints = requiredPoints - imgHist[threshold]
        threshold = threshold + 1
    print('Req. Points: ', requiredPoints)
    print("Threshold: ", threshold)

    ret, imgBW = cv2.threshold(imgHSV[:,:,1], threshold, 255, cv2.THRESH_BINARY_INV)
    cv2.namedWindow('img2', cv2.WINDOW_NORMAL)
    cv2.imshow('img2', imgHSV)
    while not (cv2.waitKey(1) & 0xFF == ord('q')):
        continue
    cv2.destroyAllWindows()
    return imgBW
    
def median_filter(img, imgMedian, kernel) :
    ki = kernel[0] / 2
    kj = kernel[1] / 2
    kernelSize = (kernel[0] * kernel[1])/2
    zero = []
    for i in range(0, img.cols) :
        zero[i] = 0
    
    for i in range(0, kernel[0]):
        for j in range(0, img.cols):
            color = img[i, j]
            if (color == 0):
                zero[j] += 1

    zeroKernel = 0
    for i in range(0, kernel[1]) :
        zeroKernel += zero[i]

    for i in range(ki, img.rows-ki-1): 
        for j in range(kj, img.cols-kj):
            if (j == kj):
                imgMedian = 255 if (zeroKernel <= kernelSize) else 0
            else:
                zeroKernel -= zero[j-kj-1]
                zeroKernel += zero[j+kj]
                imgMedian[i, j] = 255 if (zeroKernel <= kernelSize) else 0

        for k in range (0, img.cols):
            color = img[i-ki, k]
            color2 = img[i+ki+1, k]
            value1 = 1 if (color.val == 0) else 0
            value2 = 1 if (color2.val == 0) else 0
        zeroKernel = 0
        for i in range(0, kernel[1]):
            zeroKernel += zero[k]

cap = cv2.VideoCapture(0)

ret, img = cap.read()
# img = cv2.imread('test.jpg')
img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

imgBW = find_commode(img, 100000)
cv2.namedWindow('img', cv2.WINDOW_NORMAL)
cv2.imshow('img', imgBW)
while not (cv2.waitKey(1) & 0xFF == ord('q')):
    continue

# cap.release()
cv2.destroyAllWindows()
# cleanup the camera and close any open windows


