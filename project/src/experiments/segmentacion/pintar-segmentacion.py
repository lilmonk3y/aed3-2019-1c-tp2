from numpy import array
import matplotlib.pyplot as plt

#https://stackoverflow.com/questions/36410321/matplotlib-how-to-represent-array-as-image
segments = []

scale = int(raw_input())
height = int(raw_input())
width = int(raw_input())
pixelsRead = 0
componentDicc = set()
while pixelsRead < height * width:
    pixelComponent = int(raw_input())
    segments.append(pixelComponent)
    pixelsRead += 1
    if pixelComponent not in componentDicc:
        componentDicc.add(pixelComponent)

cantComp = len(componentDicc)


#Convert list to array
nArray = array(segments)
#covert array to "matrix"
a11=nArray.reshape(height,width)# alto y ancho
plt.imshow(a11, cmap='nipy_spectral') #mapa de rojos, opciones: 'hot', 'nipy_spectral'
#plt.colorbar()


textstr = '\n'.join((
    r'Cantidad de componentes=%.2f' % (cantComp, ),
    r'Scale=%.2f' % (scale, )))

# these are matplotlib.patch.Patch properties
props = dict(boxstyle='round', facecolor='wheat', alpha=0.8)

# place a text box in upper left in axes coords
# plt.text(0.05, 0.95, textstr, fontsize=10,
#         verticalalignment='top', bbox=props)

#title:
plt.title(textstr)

plt.show()

