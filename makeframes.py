import numpy as np
import cv2
import time

cap0 = cv2.VideoCapture("/home/eswar/leftout.mp4")
cap1 = cv2.VideoCapture("/home/eswar/rightout.mp4")
countleft=0
countright=0
start=time.time()
while(True):
    # Capture frame-by-frame
    ret0, frame0 = cap0.read()
    ret1, frame1 = cap1.read()
    # Our operations on the frame come here
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # Display the resulting frame
    countleft=countleft+1
    countright=countright+1
    if start-time.time()>1:
        break
    #cv2.imshow('frame',frame0)
    #cv2.imshow('frame1',frame1)
    height1, width1 = frame0.shape[:2]
    height2, width2 = frame1.shape[:2]
    leftframe = cv2.resize(frame0,(2*width1, 2*height1),interpolation=cv2.INTER_CUBIC) 
    rightframe = cv2.resize(frame1,(2*width2, 2*height2),interpolation=cv2.INTER_CUBIC) 
    cv2.imwrite('./left/'+"leftframe"+str(countleft)+".png",leftframe)
    cv2.imwrite('./right/'+"rightframe"+str(countright)+".png",rightframe)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap0.release()
cap1.release()
cv2.destroyAllWindows()
