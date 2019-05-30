import cv2

# INPUT: name of image.
# echo "12003.jpg" | python sendImage.py
# OUTPUT is: width, height and all the pixels from first to last (the pixel as an integer in range [0,255])
var = raw_input("Please enter image name:\n")

img = cv2.imread(var,cv2.IMREAD_GRAYSCALE)

height, width = img.shape[:2]

print height
print width

for i in range(height):
	for j in range(width):
		k = img.item(i,j)
		print k


