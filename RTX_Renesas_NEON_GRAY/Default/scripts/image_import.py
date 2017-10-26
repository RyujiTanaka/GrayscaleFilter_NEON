#
# Copyright (C) 2017 ARM Limited. All rights reserved.
#
from arm_ds.debugger_v1 import Debugger
from arm_ds.debugger_v1 import DebugException
from javax.imageio import ImageIO
import jarray
from java.lang import Byte

def parseDScmdRetStr(retval):
    # extract the path from '$10 = "path"' like format
    s = retval.find("\"")    # detect first character of "
    e = retval.rfind("\"")    # detect char " from the end
    return retval[s+1:e]

def getImageDir(ec):
    # get image folder from CurrentExecutionContext
    idir = ec.executeDSCommand('print $idir')
    dir = parseDScmdRetStr(idir)
    # replace \ to /
    dir = dir.replace('\\', '/')
    return dir

def loadImage(filepath):

    fp = open(filepath, 'r')
    image = ImageIO.read(fp)
    fp.close()
    
    return image

def storeImage(ec, store_adr, image):

    adr = store_adr

    height = image.getHeight()
    width = image.getWidth()
    #length = height * width * 3

    #bytes = jarray.zeros(length, 'i')

    # grayscale color image
    start_adr = adr
    idx = 0
    for y in range(0, height):
        dscmd = 'y=%d' % y
        print dscmd
        for x in range(0, width):
            argb8888 = image.getRGB(x, y)     # default TYPE_INT_ARGB
            
            red   = (argb8888 >> 16 & 0xff)
            green = (argb8888 >> 8  & 0xff)
            blue  = (argb8888       & 0xff)
            
            dscmd = 'memory set_typed 0x%08x (unsigned char) 0x%02x' % (adr, red)
            #print dscmd
            ec.executeDSCommand(dscmd)
            adr += 0x1
            #dscmd = 'y=%d, x=%d idx=%d = %s 0x%02x red' % (y, x, idx, hex(red)[2:], red)
            #print dscmd
            #bytes[idx] = red
            idx = idx + 1
            
            dscmd = 'memory set_typed 0x%08x (unsigned char) 0x%02x' % (adr, green)
            #print dscmd
            ec.executeDSCommand(dscmd)
            adr += 0x1
            #dscmd = 'y=%d, x=%d idx=%d = %s 0x%02x green' % (y, x, idx, hex(green)[2:], green)
            #print dscmd
            #bytes[idx] = green
            idx = idx + 1
            
            dscmd = 'memory set_typed 0x%08x (unsigned char) 0x%02x' % (adr, blue)
            #print dscmd
            ec.executeDSCommand(dscmd)
            adr += 0x1
            #dscmd = 'y=%d, x=%d idx=%d = %s 0x%02x blue' % (y, x, idx, hex(blue)[2:], blue)
            #print dscmd
            #bytes[idx] = blue
            idx = idx + 1

    print ' image  S:0x%08x - S:0x%08x' % (start_adr, adr)

    #fp.close()

    return adr

def main():

    # Obtain the first execution context
    debugger = Debugger()
    ec = debugger.getCurrentExecutionContext()

    # Assumed the image file is located on the project folder
    imgDir = getImageDir(ec)

    image = loadImage(imgDir + '/scripts/picture.jpg')

    #--- store image ---
    s_adr = 0x20650000     # SRC_BUFFER 0x20650000 to 0x2077C000 size 0x0012C000

    e_adr = storeImage(ec, s_adr, image)

    #--- save stored parameters to binary file ---
    dscmd = 'dump binary memory "%s/scripts/picture.bin" S:0x%08x S:0x%08x' % (imgDir, s_adr, e_adr)
    ec.executeDSCommand(dscmd)




if __name__ == '__main__':
    main() 
