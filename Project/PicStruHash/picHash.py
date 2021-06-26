from PIL import Image
import numpy
import os
from tqdm import tqdm

def getPicHash(filename):
    try:
        img = numpy.asarray(Image.open(filename).resize((10, 10)).convert("L"))
        var = []
        ans = 0
        neighbor = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        for i in range(1, 9):
            for j in range(1, 9):
                _var = 0
                for k in neighbor:
                    x = i + k[0]
                    y = j + k[1]
                    _var += (int(img[i][j]) - int(img[x][y]))**2
                _var /= 8
                var.append(_var)
        median = numpy.median(var)
        for i in var:
            ans *= 2
            if (i > median):
                ans += 1
        # print(ans)
        return int(ans)
    except:
        return 0

def getSimilar(hash1, hash2):
    ans = 0
    similar = hash1^hash2
    while (similar != 0):
        similar &= (similar - 1)
        ans += 1
    return 1 - ans/64

def main():
    f = open("picHash.log", "w")
    path = "/home/czile/work/壁纸库/"
    fileHash = []
    filenames = os.listdir(path)
    maxSizeOfAllFileName = max(map(len, filenames))
    bar = tqdm(filenames)
    for filename in bar:
        bar.set_description("Reading file: "+filename.ljust(maxSizeOfAllFileName))
        if(filename.lower().endswith(('.bmp', '.dib', '.png', '.jpg', '.jpeg', '.pbm', '.pgm', '.ppm', '.tif', '.tiff'))):
            fileHash.append((path+filename, getPicHash(path+filename)))
            f.write("{}\n".format(fileHash[-1]))
    f.close()

    f = open("picSimilar.log", "w")
    bar = tqdm([(i, j) for i in fileHash for j in fileHash])
    for i, j in bar:
        bar.set_description("Comparing")
        if (i[0] != j[0]):
            similar = getSimilar(i[1], j[1])
            # print(similar)
            if (similar > 0.95):
                f.write("{} {} {}\n".format(i, j, similar))
    f.close()

main()