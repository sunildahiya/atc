from Point import *

def merge_blobs(mainBlobs, splitBlobs, maxDist):

    mainBlobs = sorted(mainBlobs, key=lambda blob: blob[1], reverse=True)
    mainBlobs_copy = list(mainBlobs)
    mainBlobs = []

    i = 0
    j = 0
    
    while (i < len(mainBlobs_copy)):
        if (mainBlobs_copy[i][1] == -1):
            i += 1
            continue

        count = mainBlobs_copy[i][1]
        blob = mainBlobs_copy[i]
        blob[0].__mul__(count)
        j = 0
        while (j < len(mainBlobs_copy)):
            if (mainBlobs_copy[i][0].is_equal(mainBlobs_copy[j][0]) or mainBlobs_copy[j][1] == -1):
                j += 1
                continue
            else:
                if ( mainBlobs_copy[i][0].distance_to(mainBlobs_copy[j][0]) < maxDist ):
                    if (i == 40):
                        print( (mainBlobs_copy[j], j) )
                    mainBlobs_copy[j][0].__mul__( mainBlobs_copy[j][1] )
                    blob[0].__add__( mainBlobs_copy[j][0] )
                    count += mainBlobs_copy[j][1]
                    mainBlobs_copy[j][1] = -1
            j += 1
        blob[0].__div__(count)
        blob[1] = count
        mainBlobs.append(blob)
        i += 1

    mainBlobs = sorted(mainBlobs, key=lambda blob: blob[1], reverse=True)
    mainBlobs_copy = list(mainBlobs)
    mainBlobs = []
    i = 0
    j = 0
    while (i < len(mainBlobs_copy)):
        count = mainBlobs_copy[i][1]
        blob = mainBlobs_copy[i]
        blob[0].__mul__(count)
        j = 0
        while (j < len(splitBlobs)):
            if (splitBlobs[j][1] == -1):
                j += 1
                continue
            if (mainBlobs_copy[i][0].distance_to(splitBlobs[j][0]) < maxDist):
                splitBlobs[j][0].__mul__( splitBlobs[j][1] )
                blob[0].__add__( splitBlobs[j][0] )
                count += splitBlobs[j][1]
                splitBlobs[j][1] = -1
            j += 1
        blob[0].__div__(count)
        blob[1] = count
        mainBlobs.append(blob)  
        i += 1

    return mainBlobs