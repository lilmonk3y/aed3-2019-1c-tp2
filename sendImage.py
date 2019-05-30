import cv2

# echo "array 3096.jpg" | python sendImage.py | ./runSegmentacion | python createSegmentatedImage.py 
# OUTPUT is: width, height and all the pixels from first to last (the pixel as an integer in range [0,255])
inputVar = raw_input("Please enter image name and disjoinset:\n").split(' ', 2)
disjoinset = inputVar[0]
imageName = str(inputVar[1])

img = cv2.imread(imageName,cv2.IMREAD_GRAYSCALE)

height, width = img.shape[:2]

print disjoinset
print height
print width

for i in range(height):
	for j in range(width):
		k = img.item(i,j)
		print k


