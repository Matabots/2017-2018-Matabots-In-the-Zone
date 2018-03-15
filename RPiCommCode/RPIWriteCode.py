#!/usr/bin/env python
import time
import serial
import cv2
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

def show_webcam(mirror=False):
    cam = cv2.VideoCapture(0)
    
    while True:
        ret_val, img = cam.read()
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        rectangles = face_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=10,minSize=(75, 75))
        for (i, (x, y, w, h)) in enumerate(rectangles):
                # Surround cascade with rectangle
                cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2)
                cv2.putText(image, CASCADE_ITEM + " #{}".format(i + 1), (x, y - 10),
                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 0, 255), 2)
            
        if mirror:
            img = cv2.flip(img, 1)
            
        cv2.imshow(CASCADE_ITEM + "s", img)
        
        if cv2.waitKey(1) == 27:
            break #esc to quit
    cv2.destroyAllWindows()
    

ser = serial.Serial(
        port='/dev/ttyS0', #Replace ttyS0 with ttyAMA0 for Pi1,Pi2,Pi0
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
show_webcam(mirror=True)

counter=0
print("reached before loop")
while True:
        print("In loop..")
        data = 'Hello World'.encode()
        print("Encoded")
        ser.write(data)
##        ser.close();
        print("Write counter: %d "%(counter))
        time.sleep(1)
        counter += 1


