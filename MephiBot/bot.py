import asyncio
import logging
from aiogram import Bot, Dispatcher, types
from aiogram.filters.command import Command
from aiogram.types import Message
from aiogram import F
from aiogram import Bot, Dispatcher
from config import TOKEN
from GameInfo import GameInfo
from handlers import caretaker, admin

bot = Bot(token=TOKEN)
dp = Dispatcher()


game_info = GameInfo(
    caretakers={593807464: "Shreks",
                1808760043: "Taxi-rider"},
    admins={},
    stations_list={"Shreks", "Taxi-rider", "Fax",
                   "Crazy_frog", "Dancer", "Magic", "Ninja"},
    teams={"tigers", "bober", "lion", "kingkong"},

)

logging.basicConfig(level=logging.INFO)



async def main():
    dp.include_router(caretaker.caretaker_router)

    await bot.delete_webhook(drop_pending_updates=True)
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())
