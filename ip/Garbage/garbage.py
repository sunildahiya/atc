def get_stains_threshold(I_Gray, percentageThresh, threshMargin):
    hist = cv2.calcHist([I_Gray],[0],None,[256],[0,256])
    plt.plot(hist)
    plt.xlim([0, 256])
    plt.show()
    totalNumOfPoints = (I_Gray.shape)[0]*(I_Gray.shape)[1]
    numOfPoints = 0
    thresh = 0

    for i in range(0, 255):
        numOfPoints += hist[i]
        if (numOfPoints*100/totalNumOfPoints > percentageThresh):
            thresh = i
            break

    lowerEnd = int(thresh-threshMargin/2) if (thresh-threshMargin/2)>0 else 0
    upperEnd = int(thresh-threshMargin/2) if (thresh+threshMargin/2)<0 else 255
    
    minNumOfPointsInMargin = 0
    numOfPointsInMargin = 0
    for i in range(lowerEnd, upperEnd):
        minNumOfPointsInMargin += hist[i]
    numOfPointsInMargin = minNumOfPointsInMargin
    
    lowerEnd += 1
    upperEnd += 1

    for i in range(upperEnd, 256):
        numOfPointsInMargin -= hist[lowerEnd]
        numOfPointsInMargin += hist[upperEnd]
        lowerEnd += 1
        upperEnd += 1

        if (minNumOfPoints > numOfPointsInMargin):
            minNumOfPointsInMargin = numOfPointsInMargin
            thresh = (lowerEnd+upperEnd)/2

    return thresh


    # print((maxFirstPos, maxSecondPos, maxFirst, maxSecond))
    # cv2.namedWindow("win", cv2.WINDOW_NORMAL)
    # cv2.namedWindow("win2", cv2.WINDOW_NORMAL)
    # cv2.namedWindow("dim", cv2.WINDOW_NORMAL)
    # cv2.imshow("win", img_lower)
    # cv2.waitKey(0)
    # cv2.imshow("win2", img_upper)
    # cv2.waitKey(0)
    # img = cv2.bitwise_and(img_lower, img_upper)
    # cv2.imshow("win", img)
    # cv2.imshow("win2", img_gray)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()


#     img_shape = img_edge.shape
#     start_row = int(kernel[0]/2+1)
#     end_row = int(img_shape[0]-kernel[0]/2-2)
#     start_col = int(kernel[1]/2+1)
#     end_col = int(img_shape[1]-kernel[1]/2-2)

#     sum_col = np.zeros((img_shape[1]), dtype=np.int32)
#     for i in range(0, img_shape[1]):
#         for j in range(0, kernel[0]):
#             sum_col[i] += img_edge[i, j]

#     sum_kernel = 0
#     for i in range(0, kernel[1]):
#         sum_kernel += sum_col[i]

#     stains_coord = []
#     stains_count = 0

#     for i in range(start_row, end_row):
#         for j in range(start_col, end_col):
#             if (sum_kernel > thresh):
#                 stains_coord.append(Point(j, i));
#                 stains_count += 1
#             sum_kernel -= sum_col[int(j-kernel[1]/2)]
#             sum_kernel += sum_col[int(j+kernel[1]/2)]
#         for k in range(0, img_shape[1]):
#             sum_col[k] -= img_edge[int(i-kernel[0]/2), k] 
#             sum_col[k] += img_edge[int(i+kernel[0]/2+1), k]
#   return (stains_coord, stains_count)

# def get_thresh

'''
img = cv2.imread('stain1.jpg')
# img = img[562-400:562+400, 2194-400:2194+400, :]
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img = cv2.GaussianBlur(img, (9, 9), 0)
img_org = img.copy()
img_orgc = img.copy()
img = get_stains_pos(img, [300, 300], 20)
img = cv2.medianBlur(img, 21)

# Blob blobs(self)
blobs  = getBlobProps(img)

# print(blobs.contourareas)
# cv2.circle(img2, (255, 255), 50, (0,255,0))


mainBlobs = []
splitBlobs = []

for i in range(0, len(blobs.contourareas)):
    if (blobs.contourareas[i] > 5000):
        mainBlobs.append(blobs.centroids[i])
    else:
        splitBlobs.append(blobs.centroids[i])

finalBlobs = merge_points(mainBlobs, splitBlobs, 1000)

for i in range(0, len(finalBlobs)):
    cv2.circle(img_org, finalBlobs[i].as_tuple(), 63, (255, 0, 0), -1)
print (finalBlobs)
img_new = np.zeros(img.shape, dtype=np.uint8)


cv2.namedWindow("Original", cv2.WINDOW_NORMAL)
cv2.namedWindow("Blobs", cv2.WINDOW_NORMAL)
cv2.imshow("Original", img_org)
cv2.imshow("Blobs", img_orgc)
'''







# for i in range(0, len(finalBlobs)):
    # img_orgc[finalBlobs[i].y-600:finalBlobs[i].y+600, finalBlobs[i].x-600:finalBlobs[i].x+600] = get_stains_pos(img_orgc[finalBlobs[i].y-600:finalBlobs[i].y+600, finalBlobs[i].x-600:finalBlobs[i].x+600], [1200, 1200], 20)
# img_new[2756-600:2756+600, 2537-600:2537+600] = /
#     255 if(get_stains_pos(img_orgc[2756-600:2756+600, 2537-600:2537+600], [1200, 1200], 20)) 


# print(blobs.centroids[0])
# print(len(blobs.contours))

# for i in range(0, len(blobs.centroids)):
#     print[blobs]
# img = median_filter(img, [5, 5])

# dstX = cv2.Sobel(img, cv2.CV_32F, 1, 0)
# dstY = cv2.Sobel(img, cv2.CV_32F, 0, 1)
# dstX = dstX[:,:,0]+dstY[:,:,1]+dstY[:,:,2];
# dstY = dstY[:,:,0]+dstY[:,:,1]+dstY[:,:,2];
# dst = np.ones(dstX.shape, dtype=np.int32)
# dst = abs(dstX) + abs(dstY)
# dst = dst.astype('uint8')
# a, dst = cv2.threshold(dst, 200, 1, cv2.THRESH_BINARY)
# (stains_coord, stains_count) = get_stains_pos(dst, [50, 50], 12000)
# for i in range(0, stains_count):
#     cv2.circle(img,stains_coord[i].as_tuple(), 1, (0,0,255), -1)
# cv2.imshow("win", dst)
# cv2.waitKey(0)
# print(type(dst))
# print(dst)
# plt.subplot(1,2,1),plt.imshow(dst)
# plt.show()
# I_shape = img.shape
# dst = np.zeros((200, 200), dtype=np.float32)
# dstX = np.absolute(dstX)
# dstY = np.absolute(dstY)
# dstX = np.uint8(dstX)
# dstY = np.uint8(dstY)
# max_ = -180
# min_ = 180
# dst = np.ones((200,200), dtype=np.int32)
# for i in range(0, 200):
#     for j in range(0, 200):
#         if (abs(dstX[i, j])+abs(dstY[i,j]) > 60):
#             if (dstX[i,j] == 0 and dstY[i,j] == 0):
#                 dst[i, j] = 0
#             elif (dstY[i,j] == 0):
#                 dst[i,j] = 90 if dstX[i,j]>0 else -90
#             elif(dstX[i,j] == 0):
#                 dst[i,j] = 0
#             else:
#                 dst[i,j] = np.arctan2(dstY[i,j],dstX[i,j])
#         else:
#             dst[i,j] = 0
#         if (max_ < dst[i,j]):
#             max_ = dst[i,j]
#         if (min_ > dst[i,j]):
#             min_ = dst[i,j]



# # print(max_)
# # print(min_)
# plt.hist(img, bins=18)  # arguments are passed to np.histogram

# plt.title("Histogram with 'auto' bins")
# plt.show()

# n, bins = np.histogram(dst, bins=18, range=None, normed=False, weights=None, density=None)
# print(bins)
# X = np.arange(0, 200, 1)
# Y = np.arange(0, 200, 1)
# X, Y = np.meshgrid(X, Y)
# R = np.sqrt(X**2 + Y**2)
# fig = plt.figure()
# ax = Axes3D(fig)
# ax.plot_surface(X, Y, dst, rstride=1, cstride=1, cmap=cm.viridis)
# plt.show()



# dst = dstX + dstY
# plt.subplot(1,2,1),plt.imshow(img,cmap = 'gray')
# plt.title('Original'), plt.xticks([]), plt.yticks([])
# plt.subplot(1,2,2),plt.imshow(dst,cmap = 'gray')
# plt.title('Sobel CV_8U'), plt.xticks([]), plt.yticks([])
# plt.subplot(1,3,3),plt.imshow(dstY,cmap = 'gray')
# plt.title('Sobel CV_8U'), plt.xticks([]), plt.yticks([])
# plt.show()
# for i in range(0, 200):
#     for j in range(0, 200):
#         dst[i, j] = dstX[i, j] + dstY[i, j]
# # dst[:,:] = dstX[:,:]+dstY[:,:]
# dst = cv2.threshold(dst, 40, 255, cv2.THRESH_TRUNC)
# print('1', type(dstX))
# print('2', dstX.shape)
# print ('3', type(dst))
# print('4', dst.shape)
# for i in range(0, I_shape[0]):
#     for j in range(0, I_shape[1]):
#         if (dstX[i,j] == 0 and dstY[i,j] == 0):
#             dst[i, j] = 0
#         elif (dstY[i,j] == 0):
#             dst[i,j] = 90 if dstX[i,j]>0 else -90
#         elif(dstX[i,j] == 0):
#             dst[i,j] = 0
#         else:
#             dst[i,j] = np.arctan2(dstY[i,j],dstX[i,j])

# plt.subplot(121), plt.imshow(img), plt.title('Original')
# plt.subplot(122), plt.imshow(dst), plt.title('dst')
# plt.show()

# # dstY1 = cv2.filter2D(img[:,:,1],-1,kernel)
# # dstY2 = cv2.filter2D(img[:,:,2],-1,kernel)

# # for i in range(0, I_shape(0)):
# #     for j in range(0, I_shape(1)):
# #         I_shape
# # for i in range(0, )
# dstY0[:,:,0] += 1
# dst = (dstX0[:,:,0]/dstY0[:,:,0])*180/3.14
# print('dstX0 type', dstX0.dtype)
# print('dst typte', dst.dtype)
# # for i in range(1, 3):
# #     if (dstY0)
# #     dst += dstX0[:,:,i]/dstY0[:,:,i]
# # hist = cv2.calcHist([dst],[0],None,[256],[0,256])
# hists = np.zeros(256)
# print
# I_size = img.shape
# count = 0
# for i in range(0, I_size[0]):
#     for j in range(0, I_size[1]):
#         if (dst[i,j] >255):
#             count += 1
#         else:
#             hists[int(dst[i,j])] += 1

# for i in range(0, 10):
#     print(hists[i])
# print("Count:\t", count)
# plt.plot(hists)
# plt.xlim([0, 256])
# plt.show()
# #+dstX1+dstY1+dstX2+dstY2
# # ret, dst = cv2.threshold(dst, 30, 255, cv2.THRESH_BINARY)
# cv2.namedWindow("Window", cv2.WINDOW_NORMAL)
# cv2.imshow("Window", dst)
# cv2.waitKey(0)
# # plt.subplot(121),plt.imshow(dstX),plt.title('X')
# # plt.xticks([]), plt.yticks([])
# # plt.subplot(122),plt.imshow(dstY),plt.title('Y')
# # plt.xticks([]), plt.yticks([])
# # plt.show()
