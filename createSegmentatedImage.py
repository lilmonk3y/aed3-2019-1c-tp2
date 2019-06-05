import cv2 
import numpy as np

def create_blank(width, height, rgb_color=(0, 0, 0)):
    """Create new image(numpy array) filled with certain color in RGB"""
    # Create black blank image
    image = np.zeros((height, width, 3), np.uint8)

    # Since OpenCV uses BGR, convert the color first
    color = tuple(reversed(rgb_color))
    # Fill image with color
    image[:] = color
    return image


# Get the height and width and h*w integers that represents de Segments of de image
# OUTPUT: new image with all the segments as diferent colors.
ADD_INTENSITY = 10
segments = []

height = int(raw_input())
width = int(raw_input())
print height
print width
pixelsRead = 0
while pixelsRead < height * width:
	segments.append(int(raw_input()))
	pixelsRead += 1

colorsBySegment = {}
colorB = 0
colorG = 0
colorR = 0
lastUpdated = 'R'


red = (255, 0, 0)
img = create_blank(width, height, rgb_color=red)
# img = cv.CreateImage((height,width),8,3) # (Size as tuple, number of channels, pixel depth)


for i in range(height):
	for j in range(width):
		if segments[i*j+j] in colorsBySegment:
			colorB = colorsBySegment[segments[i*j+j]][0]
			colorG = colorsBySegment[segments[i*j+j]][1]
			colorR = colorsBySegment[segments[i*j+j]][2]
		else:
			colorsBySegment[segments[i*j+j]] = [colorB,colorG,colorR]
			if lastUpdated == 'R':
				colorB+= ADD_INTENSITY
				lastUpdated = 'B'
			elif lastUpdated == 'B':
				colorR+= ADD_INTENSITY
				lastUpdated = 'R'
			else:
				colorG+= ADD_INTENSITY
				lastUpdated = 'G'
		img.itemset((i, j, 0), colorB) #Set B
        img.itemset((i, j, 1), colorG) #Set G
        img.itemset((i, j, 2), colorR) #Set R


cv2.imshow('segments.jpg',img)
cv2.waitKey(0)