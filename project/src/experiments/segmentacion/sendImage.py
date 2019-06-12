import cv2


# echo "array 500 ../../../../fuentes_de_la_catedra/BSDS300/images/test/189080.jpg" | python sendImage.py | ./runSegmentacion | python pintar-segmentacion.p
# OUTPUT is: width, height and all the pixels from first to last (the pixel as an integer in range [0,255])
inputVar = raw_input().split(' ', 3)
disjoinset = inputVar[0]
scale = inputVar[1]
imageName = str(inputVar[2])

img = cv2.imread(imageName,cv2.IMREAD_GRAYSCALE)

height, width = img.shape[:2]
print disjoinset
print scale
print height
print width
for i in range(int(height)):
	for j in range(int(width)):
		k = img.item(i,j)
		print k
