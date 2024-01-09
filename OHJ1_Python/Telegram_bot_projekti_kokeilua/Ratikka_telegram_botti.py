import telebot
import os

token = ""
bot = telebot.TeleBot(token)

@bot.message_handler(commands=['start', 'help'])

def send_welcome(message):
    bot.reply_to(message, "Olen Ratikka botti")

@bot.message_handler(commands=['Hallila'])

def aikataulu(message):
    bot.send_message(message.chat.id, "Hallilaan tulee raitiovaunu: ")

@bot.message_handler(func=lambda message: True)

def echo_all(message):
    bot.reply_to(message, message.text)

bot.polling()

