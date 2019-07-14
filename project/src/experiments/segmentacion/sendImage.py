import cv2


# echo "array 500 0.8 ../../../../fuentes_de_la_catedra/BSDS300/images/test/189080.jpg" | python sendImage.py | ./runSegmentacion | python pintar-segmentacion.py
# echo "array 500 0.8 ../../../../fuentes_de_la_catedra/BSDS300/images/test/189080.jpg" | python sendImage.py
# OUTPUT is: width, height and all the pixels from first to last (the pixel as an integer in range [0,255])
inputVar = raw_input().split(' ', 3)
disjoinset = inputVar[0]
scale = inputVar[1]
sigma = float(inputVar[2])
imageName = str(inputVar[3])

imgToFilter = cv2.imread(imageName)
imgToGray = cv2.GaussianBlur(imgToFilter,(0,0), sigma) # inputImg, #pixelsNearToLook, sigma
img = cv2.cvtColor(imgToGray, cv2.COLOR_BGR2GRAY)

# cv2.imshow("original",imgToFilter)
# cv2.imshow("blur",imgToGray)
# #cv2.imshow("blur gray",img)
# cv2.waitKey(0)
# cv2.destroyAllWindows

height, width = img.shape[:2]
print disjoinset
print scale
print height
print width
for i in range(int(height)):
	for j in range(int(width)):
		k = img.item(i,j)
		print k
