# 电磁炮目标识别程序 
# Untitled - By: Charmve - 周六 8月 10 2019

# Measure the distance
#
# This example shows off how to measure the distance through the size in imgage
# This example in particular looks for yellow pingpong ball.

import sensor, image, time, pyb
#load serial
#OpenMV: PB4--TX,PB5--RX
from pyb import UART

# For color tracking to work really well you should ideally be in a very, very,
# very, controlled enviroment where the lighting is constant...
# yellow_threshold   = ( 56,   83,    5,   57,   63,   80)

red_threshold   = ( 29,   75,   38,   65,   -26,   46)
# You may need to tweak the above settings for tracking green things...
# Select an area in the Framebuffer to copy the color settings.

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

uart = UART(3,115200)

K=2250 #the value should be measured  2800 2426 2520

#取像素点最大的色块
def Compare_Pixel(blob_a,blob_b):
    temp = blob_a.pixels() - blob_b.pixels()
    if temp == 0:
        return 0;
    elif temp > 0:
        return 1;
    else:
        return -1;

while(True):
    ball_cx = 0xfd
    ball_cy = 0xfd
    Max_Blob = None

    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # Take a picture and return the image.

    blobs = img.find_blobs([red_threshold])
    if len(blobs) == 1:
        # Draw a rect around the blob.
        b = blobs[0]
        for a in blobs:
            if Compare_Pixel(Max_Blob,b) == -1:
                b = a
        img.draw_rectangle(b[0:4]) # rect
        img.draw_cross(b[5], b[6]) # cx, cy
        ball_cx = b.cx()
        ball_cy = b.cy()

        Lm = (b[2]+b[3])/2
        length = K/Lm
        for i in range(11):
            length = length + K/Lm -12
        length = length / 11

        # print (Lm)
        print(length)
        
    Ball_Pos = bytearray([0xC8, 0xF2, int(ball_cx), int(ball_cx>>8)])
    uart.write(Ball_Pos)

    #print(clock.fps()) # Note: Your OpenMV Cam runs about half as fast while
    # connected to your computer. The FPS should increase once disconnected.
