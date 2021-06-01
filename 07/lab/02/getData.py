
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import re
#vertion 1.0
driver = webdriver.Chrome()
driver.get('https://map.baidu.com/')
driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/div[@id='searchbox']/div[@id='searchbox-container']/div[@id='sole-searchbox-content']/div[@class='searchbox-content-button right-button route-button loading-button']").click()
driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/div[@id='searchbox']/div[@id='searchbox-container']/div[@id='route-searchbox-content']/div[@class='route-header']/div[@class='searchbox-content-common route-tabs']/div[@class='tab-item walk-tab']/span").click()
#单击第一个按钮进入搜索界面

def startSpide(start,end):
    #start是第一输入框的内容，end是第二个，startSpide爬两地点间时间文字信息
    driver.find_element_by_xpath('/html/body/div[1]/div[2]/div/div[1]/div[2]/div[2]/div/div[2]/div[1]/input').clear()
    driver.find_element_by_xpath('/html/body/div[1]/div[2]/div/div[1]/div[2]/div[2]/div/div[2]/div[2]/input').clear()
    #清空两个输入框，即问号按键

    driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/div[@id='searchbox']/div[@id='searchbox-container']/div[@id='route-searchbox-content']/div[@class='routebox']/div[@class='searchbox-content-common routebox-content']/div[@class='routebox-inputs']/div[@class='routebox-input route-start']/input[@class='route-start-input']").send_keys(start)
    driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/div[@id='searchbox']/div[@id='searchbox-container']/div[@id='route-searchbox-content']/div[@class='routebox']/div[@class='searchbox-content-common routebox-content']/div[@class='routebox-inputs']/div[@class='routebox-input route-end']/input[@class='route-end-input']").send_keys(end)
    #在两个框内输入字符start和end
    
    driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/div[@id='searchbox']/button[@id='search-button']").click()
    #点击搜索
    
    time.sleep(2)
    try:
        driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/ul[@id='cards-level1']/li[1]/div[@class='RouteAddressOuterBkg']/div[@class='RouteAddressInnerBkg']/div[@id='RouteAddress_DIV1']/div[@class='sel_body']/div[@id='RADIV_BODY1']/div[@id='RADiv_ResItem1']/div[@id='RA_ResItem_1']/table/tbody/tr[1]/td[2]").click()
    except:
        a = 1
    else:
        time.sleep(2)
        # pass
    try:
        driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/ul[@id='cards-level1']/li[1]/div[@class='RouteAddressOuterBkg']/div[@class='RouteAddressInnerBkg']/div[@id='RouteAddress_DIV0']/div[@class='sel_body']/div[@id='RADIV_BODY0']/div[@id='RADiv_ResItem0']/div[@id='RA_ResItem_0']/table/tbody/tr[1]/td[2]").click()
    except:
        a = 1
    #出现模糊地址的时候选择第一个准确地址
    
    time.sleep(2)
    try:#超时异常处理
        WebDriverWait(driver,5,0.5).until(EC.presence_of_element_located((By.XPATH, "/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/ul[@id='cards-level1']/li[1]/div[@id='nav_container']/div[@class='route_contentWrapper walk_cont']/div[@id='route_content_walk']/div[@class='special']/div[@class='drive']/div[@class='con']/div[@class='navtrans-navlist-view active expand navtrans-type-walk']/div[@class='navtrans-navlist-title']/p[@class='navtrans-navlist-title-p title-info']/span[@class='last']")))
    except:
        driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/div[@id='searchbox']/button[@id='search-button']").click()
        try:
            driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/ul[@id='cards-level1']/li[1]/div[@class='RouteAddressOuterBkg']/div[@class='RouteAddressInnerBkg']/div[@id='RouteAddress_DIV1']/div[@class='sel_body']/div[@id='RADIV_BODY1']/div[@id='RADiv_ResItem1']/div[@id='RA_ResItem_1']/table/tbody/tr[1]/td[2]").click()
        except:
            a = 1
        time.sleep(2)
        try:
            driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/ul[@id='cards-level1']/li[1]/div[@class='RouteAddressOuterBkg']/div[@class='RouteAddressInnerBkg']/div[@id='RouteAddress_DIV0']/div[@class='sel_body']/div[@id='RADIV_BODY0']/div[@id='RADiv_ResItem0']/div[@id='RA_ResItem_0']/table/tbody/tr[1]/td[2]").click()
        except:
            a = 1
    try:
        span2=driver.find_element_by_xpath("/html/body[@class='pc']/div[@id='app']/div[@id='left-panel']/ul[@id='cards-level1']/li[1]/div[@id='nav_container']/div[@class='route_contentWrapper walk_cont']/div[@id='route_content_walk']/div[@class='special']/div[@class='drive']/div[@class='con']/div[@class='navtrans-navlist-view active expand navtrans-type-walk']/div[@class='navtrans-navlist-title']/p[@class='navtrans-navlist-title-p title-info']/span[@class='last']").get_attribute('textContent')
    except:
        span2 = '-1'
    #找到文字的信息
    span2=transform(span2)
    print(span2,end=" ")

def transform(span):
    # 把文字转换为以米为单位的数字
    if span.find("公里")!= -1:
        span = re.sub('公里','',span)
        span = re.sub('约','',span)
        span = int(float(span)*1000)
    else:
        span = re.sub('约','',span)
        span = re.sub('米','',span)
        span = int(float(span))
    return span
location=['肇庆', '佛山', '广州', '东莞', '惠州', '江门', '中山', '深圳', '澳门', '香港', '珠海']
for i in range(len(location)):
    print(location[i], end=" ")
    for j in range(len(location)):
        if(j==i):
            print(0,end=" ")
        else:
            startSpide(location[i],location[j])
    print()
