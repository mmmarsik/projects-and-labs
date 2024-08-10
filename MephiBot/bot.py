from aiogram import *
import asyncio
from aiogram.filters.command import Command




TOKEN = "7317277427:AAGKGmLfxcE8BUiq9ketqQtY5jFykaetGNM"
bot = Bot(token=TOKEN)
dp = Dispatcher()


@dp.message(Command("start"))
async def cmd_start(msg: types.Message):
    await msg.answer(f"Я бот. Приятно познакомиться, {msg.from_user.first_name}")


# @dp.message_handler(content_types=['text'])
# async def get_text_messages(msg: types.Message):
#     if msg.text.lower() == 'привет':
#         await msg.answer('Привет!')
#     else:
#         await msg.answer('Не понимаю, что это значит.')

async def main():
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())


