from PIL import Image
import numpy as np
import clipboard

im = Image.open('dcode-image.png') # nombre de la imagen GRIS a transformar en vector de vectores en c++

#image to array:
im2arr = np.array(im) # im2arr.shape: height x width x channel

imageMatrixStr = "{"
for fila in im2arr:
	pixelesFila = ""
	for pixelRGB in fila:
		pixelesFila = pixelesFila + "," + str(pixelRGB[0]) ## aca se pone " " ó ","
	pixelesFila = "{" + pixelesFila[1:] + "},"
	imageMatrixStr = imageMatrixStr +  pixelesFila  + "\n"

imageMatrixStr = imageMatrixStr[:-2] + "}" # borro el salto de linea y la coma
clipboard.copy(imageMatrixStr)  # now the clipboard content will be string "abc"


#TRANSFORMAR UNA IMAGEN EN UN VECTOR DE VECTORES EN C++ Y QUE ESTE EN EL CLIPBOARD