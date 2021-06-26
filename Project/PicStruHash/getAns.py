from PIL import Image
import numpy
from tqdm import tqdm

def getPicArray(filename):
    img = numpy.asarray(Image.open(filename).resize((302, 302)).convert("L"))
    ans = []
    neighbor = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    for i in range(1, 301):
        ans.append([])
        for j in range(1, 301):
            _var = 0
            for k in neighbor:
                x = i + k[0]
                y = j + k[1]
                _var += abs((int(img[i][j]) - int(img[x][y])))
            ans[-1].append(_var/8)
    medium = numpy.median(ans)
    if medium == 0:
        medium = 1
    ans = [[j*128/medium for j in i] for i in ans]
    return ans

def getPicMean(fl):
    filelist = tqdm(fl)
    # Image.fromarray(numpy.array(getPicArray(fl[0])).astype(numpy.uint8)).show()
    # ans = getPicArray(fl[0])
    for filename in filelist:
        if filename != fl[0]:
            tmp = getPicArray(filename)
            for i, j in zip(ans, tmp):
                i = numpy.sum([numpy.array(i), numpy.array(j)])
    
    ans = [[int(255 - min(j, 255)) for j in i] for i in ans]
    return ans

def main():
    with open("pattern3.mdb", 'r') as f:
        filelist = f.read().split("\n")
        ans = getPicMean(filelist)
        # print(ans)
        im = Image.fromarray(numpy.array(ans).astype(numpy.uint8))
        im.save("ans3.png")
        im.show()

main()