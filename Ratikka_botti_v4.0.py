from aiogram import Bot, Dispatcher, executor, types
from aiogram.types import InlineKeyboardMarkup, InlineKeyboardButton
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import logging
import asyncio

logging.basicConfig(level=logging.INFO)

# Lisää Telegram Bot Token "tähän"
bot = Bot(token="")
dp = Dispatcher(bot)


# Virhe tulee jos chromedriver ei ole samaa versiota, kuin chrome.
# Lataa uusi chromedriver siinä tapauksessa. Selenium osoittaa errorissa mikä versio.
# Selenium ei myös tue välttämättä Chrome versiota, joten täytyy käyttää vanhempaa versiota.

@dp.message_handler(commands=["start"])
async def welcome(message: types.Message):
    await message.reply("Hei! Olen Ratikka-Botti! Komennot ovat: \n "
                        "\n/Hallila "
                        "\n\n\n/Rautatieasema "
                        "\n\n\n/Hervantakeskus"
                        "\n\n .")
    await bot.delete_message(chat_id=message.chat.id,
                             message_id=message.message_id)

@dp.message_handler(commands=["help"])
async def welcome(message: types.Message):
    bot_message = await message.reply("Hei! Olen Ratikka-Botti! Komennot ovat: \n "
                        "\n/Hallila "
                        "\n\n\n/Rautatieasema "
                        "\n\n\n/Hervantakeskus"
                        "\n\n .")

    await bot.delete_message(chat_id=message.chat.id,
                             message_id=message.message_id)

    await asyncio.sleep(7)

    await bot.delete_message(chat_id=bot_message.chat.id,
                             message_id=bot_message.message_id)

"""Hallila"""
button1 = InlineKeyboardButton(text="Hallila: Pyynikintori",
                               callback_data="Hallila_Pyynikintori")
button2 = InlineKeyboardButton(text="Hallila: Hervanta",
                               callback_data="Hallila_Hervanta")
keyboard_inline_hallila = InlineKeyboardMarkup().add(button1, button2)
""""""

"""Hervanta"""
button3 = InlineKeyboardButton(text="Hervantakeskus: Pyynikintori",
                               callback_data="Hervantakeskus_Pyynikintori")
button4 = InlineKeyboardButton(text="Hervantakeskus: Hervantajärvi",
                               callback_data="Hervantakeskus_Hervantajärvi")
keyboard_inline_hervanta = InlineKeyboardMarkup().add(button3, button4)
""""""

"""Keskusta"""
button5 = InlineKeyboardButton(text="Rautatieasema: Pyynikintori",
                               callback_data="Rautatieasema_Pyynikintori")
button6 = InlineKeyboardButton(text="Rautatieasema: Hervanta",
                               callback_data="Rautatieasema_Hervanta")
keyboard_inline_keskusta = InlineKeyboardMarkup().add(button5, button6)
""""""


@dp.message_handler(commands=["Hallila"])
async def welcome(message: types.Message):
    bot_message = await message.reply("Kumpaan suuntaan olet menossa?",
                        reply_markup=keyboard_inline_hallila)
    await message.delete()

    await asyncio.sleep(7)

    await bot.delete_message(chat_id=bot_message.chat.id,
                             message_id=bot_message.message_id)


@dp.message_handler(commands=["Hervantakeskus"])
async def welcome(message: types.Message):
    bot_message = await message.reply("Kumpaan suuntaan olet menossa?",
                        reply_markup=keyboard_inline_hervanta)
    await message.delete()

    await asyncio.sleep(7)

    await bot.delete_message(chat_id=bot_message.chat.id,
                             message_id=bot_message.message_id)


@dp.message_handler(commands=["Rautatieasema"])
async def welcome(message: types.Message):
    bot_message = await message.reply("Kumpaan suuntaan olet menossa?",
                        reply_markup=keyboard_inline_keskusta)
    await message.delete()

    await asyncio.sleep(7)

    await bot.delete_message(chat_id=bot_message.chat.id,
                             message_id=bot_message.message_id)

@dp.callback_query_handler(text=["Hallila_Pyynikintori", "Hallila_Hervanta",
                                 "Hervantakeskus_Pyynikintori",
                                 "Hervantakeskus_Hervantajärvi",
                                 "Rautatieasema_Pyynikintori",
                                 "Rautatieasema_Hervanta", "jaa_sijainti"])

async def kb_answer_hallila(call: types.CallbackQuery):
    """Tästä alkaa toistettava pätkä"""
    if call.data == "Hallila_Pyynikintori":

        global a
        a = 0
        path = Service('C:\Chromedriver\chromedriver.exe')
        driver = webdriver.Chrome(service=path)

        url = 'https://reittiopas.tampere.fi/pysakit/tampere%3A0827'

        driver.get(url)

        time.sleep(1)

        try:

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "time-cell")))

            articles = driver.find_elements(by=By.CLASS_NAME,
                                            value="time-cell")

            lista = []

            for ratikka_times in articles:
                if a == 4:
                    full_message = f"Seuraava ratikka saapuu Hallilan pysäkille Pyynikintoria kohti {lista[0]}, sitten  {lista[1]},  {lista[2]}  ja  {lista[3]}. "
                    message = await call.message.answer(full_message)
                    await asyncio.sleep(15)
                    await bot.delete_message(chat_id=message.chat.id,
                                             message_id=message.message_id)
                    break

                if ratikka_times.text.__contains__("kello"):
                    s = ratikka_times.text.split("\n")
                    lista.append(s[0])
                    a += 1

        finally:
            driver.quit()

    if call.data == "Hallila_Hervanta":

        a = 0
        path = Service('C:\Chromedriver\chromedriver.exe')
        driver = webdriver.Chrome(service=path)

        url = 'https://reittiopas.tampere.fi/pysakit/tampere%3A0828'

        driver.get(url)

        time.sleep(1)

        try:

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "time-cell")))

            articles = driver.find_elements(by=By.CLASS_NAME,
                                            value="time-cell")

            lista = []

            for ratikka_times in articles:
                if a == 4:
                    full_message = f"Seuraava ratikka saapuu Hallilan pysäkille Hervantaa kohti {lista[0]}, sitten  {lista[1]},  {lista[2]}  ja  {lista[3]}. "
                    message = await call.message.answer(full_message)
                    await asyncio.sleep(15)
                    await bot.delete_message(chat_id=message.chat.id,
                                             message_id=message.message_id)
                    break

                if ratikka_times.text.__contains__("kello"):
                    s = ratikka_times.text.split("\n")
                    lista.append(s[0])
                    a += 1

        finally:
            driver.quit()

    """Tähän loppuu toistettava pätkä"""

    if call.data == "Hervantakeskus_Pyynikintori":

        a = 0
        path = Service('C:\Chromedriver\chromedriver.exe')
        driver = webdriver.Chrome(service=path)

        url = 'https://reittiopas.tampere.fi/pysakit/tampere%3A0833'

        driver.get(url)

        time.sleep(1)

        try:

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "time-cell")))

            articles = driver.find_elements(by=By.CLASS_NAME,
                                            value="time-cell")

            lista = []

            for ratikka_times in articles:
                if a == 4:
                    full_message = f"Seuraava ratikka saapuu Hervantakeskuksen pysäkille Pyynikintoria kohti {lista[0]}, sitten  {lista[1]},  {lista[2]}  ja  {lista[3]}. "
                    message = await call.message.answer(full_message)
                    await asyncio.sleep(15)
                    await bot.delete_message(chat_id=message.chat.id,
                                             message_id=message.message_id)
                    break

                if ratikka_times.text.__contains__("kello"):
                    s = ratikka_times.text.split("\n")
                    lista.append(s[0])
                    a += 1

        finally:
            driver.quit()

    if call.data == "Hervantakeskus_Hervantajärvi":

        a = 0
        path = Service('C:\Chromedriver\chromedriver.exe')
        driver = webdriver.Chrome(service=path)

        url = 'https://reittiopas.tampere.fi/pysakit/tampere%3A0834'

        driver.get(url)

        time.sleep(1)

        try:

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "time-cell")))

            articles = driver.find_elements(by=By.CLASS_NAME,
                                            value="time-cell")

            lista = []

            for ratikka_times in articles:
                if a == 4:
                    full_message = f"Seuraava ratikka saapuu Hervantakeskuksen pysäkille Hervantajärveä kohti {lista[0]}, sitten  {lista[1]},  {lista[2]}  ja  {lista[3]}. "
                    message = await call.message.answer(full_message)
                    await asyncio.sleep(15)
                    await bot.delete_message(chat_id=message.chat.id,
                                             message_id=message.message_id)
                    break

                if ratikka_times.text.__contains__("kello"):
                    s = ratikka_times.text.split("\n")
                    lista.append(s[0])
                    a += 1

        finally:
            driver.quit()

    """"""

    if call.data == "Rautatieasema_Pyynikintori":

        a = 0
        path = Service('C:\Chromedriver\chromedriver.exe')
        driver = webdriver.Chrome(service=path)

        url = 'https://reittiopas.tampere.fi/pysakit/tampere%3A0809'

        driver.get(url)

        time.sleep(1)

        try:

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "time-cell")))

            articles = driver.find_elements(by=By.CLASS_NAME,
                                            value="time-cell")

            lista = []

            for ratikka_times in articles:
                if a == 4:
                    full_message = f"Seuraava ratikka saapuu Rautatieaseman pysäkille Pyynikintoria kohti {lista[0]}, sitten  {lista[1]},  {lista[2]}  ja  {lista[3]}. "
                    message = await call.message.answer(full_message)
                    await asyncio.sleep(15)
                    await bot.delete_message(chat_id=message.chat.id,
                                             message_id=message.message_id)
                    break

                if ratikka_times.text.__contains__("kello"):
                    s = ratikka_times.text.split("\n")
                    lista.append(s[0])
                    a += 1

        finally:
            driver.quit()

    if call.data == "Rautatieasema_Hervanta":

        a = 0
        path = Service('C:\Chromedriver\chromedriver.exe')
        driver = webdriver.Chrome(service=path)

        url = 'https://reittiopas.tampere.fi/pysakit/tampere%3A0810'

        driver.get(url)

        time.sleep(1)

        try:

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "time-cell")))

            articles = driver.find_elements(by=By.CLASS_NAME,
                                            value="time-cell")

            lista = []

            for ratikka_times in articles:
                if a == 4:
                    full_message = f"Seuraava ratikka saapuu Rautatieaseman pysäkille Hervantaa kohti {lista[0]}, sitten  {lista[1]},  {lista[2]}  ja  {lista[3]}. "
                    message = await call.message.answer(full_message)
                    await asyncio.sleep(15)
                    await bot.delete_message(chat_id=message.chat.id,
                                             message_id=message.message_id)
                    break

                if ratikka_times.text.__contains__("kello"):
                    s = ratikka_times.text.split("\n")
                    lista.append(s[0])
                    a += 1

        finally:
            driver.quit()


executor.start_polling(dp)
