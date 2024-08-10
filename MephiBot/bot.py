import asyncio
import logging
from aiogram import Bot, Dispatcher, types
from aiogram.filters.command import Command

from config import TOKEN

logging.basicConfig(level=logging.INFO)

bot = Bot(token=TOKEN)

dp = Dispatcher()

@dp.message(Command("start"))
async def cmd_start(message: types.Message):
    await message.answer("Hello! let's start")

@dp.message(Command("help"))
async def cmd_start(message: types.Message):
    await message.answer("Hello! I will help you")

async def main():
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())
