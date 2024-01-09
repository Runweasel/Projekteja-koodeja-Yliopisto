from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import telebot

token = ""
bot = telebot.TeleBot(token)

@bot.message_handler(commands=['start', 'help'])
def send_welcome(message):
    bot.reply_to(message, "Olen Ratikka botti")

@bot.message_handler(commands=['Hallila'])
def aikataulu(message):
    PATH = Service('C:\Program Files (x86)\chromedriver.exe')
    driver = webdriver.Chrome(service=PATH)

    url = 'https://reittiopas.tampere.fi/'

    driver.get(url)
    print(driver.title)

    time.sleep(1)

    search = driver.find_element(by=By.ID, value="origin")
    search.send_keys("Männikönkatu 1, Tampere")
    search.send_keys(Keys.RETURN)

    time.sleep(2)

    search = driver.find_element(by=By.ID, value="destination")
    search.send_keys("Hämeenkatu 5, Tampere")
    search.send_keys(Keys.RETURN)

    time.sleep(2)

    try:
        main = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "itinerary-start-time-and-end-time")))

        articles = driver.find_elements(by=By.CLASS_NAME, value="itinerary-start-time-and-end-time")

        for times in articles:

            bot.send_message(message.chat.id, times.text)

    finally:
        driver.quit()

bot.infinity_polling()