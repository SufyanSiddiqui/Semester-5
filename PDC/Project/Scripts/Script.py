from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from datetime import datetime
import re
from bs4 import BeautifulSoup as soup
f = open("Giphy_Data.txt","a")

f.write("Name,Views"+str(datetime.today)+",URL\n")
chrome_options = webdriver.ChromeOptions()
chrome_options.add_argument("--start-maximized")
chrome_options.add_argument("--headless")
chrome_options.add_experimental_option('excludeSwitches', ['enable-logging'])
chrome_options.add_argument("--log-level=3")
chrome_options.binary_location = r"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe"
driver = webdriver.Chrome(options=chrome_options,executable_path="chromedriver.exe")
driver.get("https://en.wikipedia.org/wiki/List_of_Joe_Biden_2020_presidential_campaign_endorsements")
WebDriverWait(driver,5).until(EC.visibility_of_all_elements_located((By.CSS_SELECTOR,"#content")))
page_soup = soup(driver.page_source,"lxml")
Text_On_Page = page_soup.get_text().strip().replace('  ',"")
Text_On_Page = re.sub(r'(?u)[^\w]',' ', Text_On_Page)
Text_On_Page = re.sub(' +',' ',Text_On_Page)
driver.quit()
f.write(str(Text_On_Page)+' ')
for i in range(1,1000):
	Fd.write(str(Text_On_Page)+' ')