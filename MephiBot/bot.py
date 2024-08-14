import asyncio
import logging
from aiogram import Bot, Dispatcher
from config import TOKEN
from GameInfo import GameInfo
from aiogram.fsm.storage.memory import MemoryStorage

storage = MemoryStorage()


bot = Bot(token=TOKEN)
dp = Dispatcher(storage=storage)


game_info = GameInfo(
    caretakers={1808760043: "Taxi-rider"},
    admins={593807464},
    stations_list={"Shreks", "Taxi-rider", "Fax",
                   "Crazy_frog", "Dancer", "Magic", "Ninja"},
    teams={"tigers", "bober", "lion", "kingkong"},

)

logging.basicConfig(level=logging.INFO)

from handlers import caretaker, admin


async def main():
    dp.include_router(caretaker.caretaker_router)
    dp.include_router(admin.admin_router)

    await bot.delete_webhook(drop_pending_updates=True)
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())
