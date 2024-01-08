import os, sys
import cv2,os
import numpy as np
import pickle
import os
import time
import mail
import glob
from mail import*
from PIL import Image
import shutil

import serial


capture_duration = 60
faceDetect=cv2.CascadeClassifier('haarcascade_frontalface_default.xml');
cam=cv2.VideoCapture(0);
rec=cv2.face.LBPHFaceRecognizer_create();
rec.read("recognizer//model.yml")


ser = serial.Serial(
    port='COM6',  # Device name
    baudrate=9600,  # Baud rate such as 9600 or 115200 etc.
    parity=serial.PARITY_NONE,  # Enable parity checking
    stopbits=serial.STOPBITS_ONE,  # Number of stop bits
    bytesize=serial.EIGHTBITS,  # Number of data bits.
    timeout=.1,  # Set a read timeout value.
    rtscts=0  # Enable hardware (RTS/CTS) flow control.
)


id=0
ret,img=cam.read(); 
#font=cv2.cv.Initfont(cv2.cv.CV_FONT_HERSHEY_COMPLEX_SMALL,5,1,0,4)
start_time = time.time()
ids = '$,'
list_names = ' '




while( int(time.time() - start_time) < capture_duration ):

        _,img=cam.read();
        
        gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        
        faces=faceDetect.detectMultiScale(gray,1.3,5);
        
        for(x,y,w,h) in faces:
                #cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
                cv2.rectangle(img,(x-50,y-50),(x+w+50,y+h+50),(255,0,0),2)
                id,conf=rec.predict(gray[y:y+h,x:x+w])
                print(conf)
                if (conf<60):
                        if id == 1:
                                print("mano");
                                ids = "mano"
                                #databasee(ids)
                                ser.write(b'2')
                    
                                time.sleep(3)
                        if id == 2:
                                print("dinesh");
                                ids = "dinesh"
                                #databasee(ids)
                                ser.write(b'2')
                    
                                time.sleep(3)
                        if id == 3:
                                print("j");
                                ids = "j"
                                #databasee(ids)
                                ser.write(b'2')
                    
                                time.sleep(3)
                                

                else:
                        cv2.imwrite('image.jpg', img)
                        print ("unknown")
                        ser.write(b'1')
                    
                        time.sleep(3)
                        mail.report_send_mail('UNKNOWN' , 'image.jpg')
                     

        cv2.imshow("Face",img);
        if(cv2.waitKey(1)==ord('q')):
                break;

cam.release()
cv2.destroyAllWindows()

