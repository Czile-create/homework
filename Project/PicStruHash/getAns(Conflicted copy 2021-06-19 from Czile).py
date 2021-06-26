from PIL import Image
import numpy
from tqdm import tqdm

def getPicArray(filename):
    img = numpy.asarray(Image.open(filename).resize((502, 502)).convert("L"))
    ans = []
    neighbor = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    for i in range(1, 501):
        ans.append([])
        for j in range(1, 501):
            _var = 0
            for k in neighbor:
                x = i + k[0]
                y = j + k[1]
                _var += abs((int(img[i][j]) - int(img[x][y])))
            ans[-1].append(_var/8)
    median = numpy.median(ans)
    ans = [[int(j>median)*255 for j in i] for i in ans]
    return ans

def getPicMean(fl):
    filelist = tqdm(fl)
    # Image.fromarray(numpy.array(getPicArray(fl[0])).astype(numpy.uint8)).show()
    ans = getPicArray(fl[0])
    for filename in filelist:
        if filename != fl[0]:
            tmp = getPicArray(filename)
            for i in range(len(tmp)):
                for j in range(len(tmp)):
                    ans[i][j] += tmp[i][j]
    
    ans = [[int(255 - min(j/len(fl), 255)) for j in i] for i in ans]
    return ans

def main():
    with open("pattern2.mdb", 'r') as f:
        filelist = f.read().split("\n")
        ans = getPicMean(filelist)
        # print(ans)
        im = Image.fromarray(numpy.array(ans).astype(numpy.uint8))
        im.save("2.png")
        im.show()

main()