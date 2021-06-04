import requests
from math import  *
import time
from retrying import retry

@retry
def getJson(url):
    return requests.get(url).json()

# 获取城市的经纬度
def getPosition(address):
    print(address, end=" ")
    url= 'http://api.map.baidu.com/geocoder?output=json&address='+str(address)
    answer = getJson(url)    
    lon = float(answer['result']['location']['lng'])
    lat = float(answer['result']['location']['lat'])
    print((lon, lat))
    return (lon, lat)


def getDistance(Pos1, Pos2):
    # 将十进制度数转化为弧度
    lon1, lat1, lon2, lat2 = map(radians, [Pos1[0], Pos1[1], Pos2[0], Pos2[1]])
    # haversine公式
    deltalon = lon2 - lon1 
    deltalat = lat2 - lat1 
    a = sin(deltalat/2)**2 + cos(lat1) * cos(lat2) * sin(deltalon/2)**2
    c = 2 * asin(sqrt(a)) 
    r = 6371 # 地球平均半径，单位为公里
    return c * r * 1000

location=['肇庆市', '佛山市', '广州市', '东莞市', '惠州市', '江门市', '中山市', '深圳市', '澳门特别行政区', '香港特别行政区', '珠海市']
position=list(map(getPosition, location))

# 由于百度地图的api无法获取香港和澳门的地址（获取到的地址为北京王府井附近），故此处单独修改地址
position[-3] = (114.171202, 22.277469)
position[-2] = (113.543117, 22.186883)

for i in range(len(location)):
    print(location[i], end=" ")
    for j in range(len(location)):
        print(int(getDistance(position[i], position[j])), end=" ")
    print()
