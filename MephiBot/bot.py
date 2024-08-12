import asyncio
import logging
from aiogram import Bot, Dispatcher, types
from aiogram.filters.command import Command
from aiogram.enums import ParseMode
from aiogram.client.default import DefaultBotProperties
from aiogram.types import Message
from aiogram import F
from config import TOKEN

logging.basicConfig(level=logging.INFO)

bot = Bot(token=TOKEN)
dp = Dispatcher()

class GameInfo:
    def __init__(self, caretakers: dict[int, str], admins: dict[int, str], stations: dict[str, bool]):
        self.caretakers = caretakers
        self.admins = admins
        self.stations = stations

    def is_station_free(self, station_name: str):
        return self.stations.get(station_name, False)

    def get_station_by_id(self, user_id: int):
        return self.caretakers.get(user_id) or self.admins.get(user_id)

    def set_station_status(self, station_name: str, is_free: bool):
        if station_name in self.stations:
            self.stations[station_name] = is_free

    def get_free_stations(self):
        return [station for station, is_free in self.stations.items() if is_free]


game_info = GameInfo(
    caretakers={593807464: "Shreks", 1808760043: "Taxi-rider"},
    admins={},
    stations={"Shreks": True, "Taxi-rider": True}
)

@dp.message(Command("start"))
async def cmd_start(message: types.Message):
    station = game_info.get_station_by_id(message.from_user.id)
    if station:
        await message.answer(
            (f"Привет, {message.from_user.full_name}, твоя станция это - {station}\n"
             f"Чтобы начать работу, напиши команду: /work"))

@dp.message(Command("work"))
async def cmd_work(message: types.Message):
    kb = [
        [types.KeyboardButton(text="Принять новую команду")],
        [types.KeyboardButton(text="Перенаправить текущую команду")]
    ]
    keyboard = types.ReplyKeyboardMarkup(
        keyboard=kb,
        resize_keyboard=True,
        input_field_placeholder="Выберите действие"
    )
    await message.answer("Что вы хотите сделать?", reply_markup=keyboard)

@dp.message(F.text.lower() == "принять новую команду")
async def accept_new_task(message: types.Message):
    station = game_info.get_station_by_id(message.from_user.id)
    if station and game_info.is_station_free(station):
        game_info.set_station_status(station, False)
        await message.reply(f"Вы успешно приняли новую команду на станцию {station}.")
    else:
        await message.reply("Не удалось принять команду. Ваша станция занята или не найдена.")

@dp.message(F.text.lower() == "перенаправить текущую команду")
async def redirect_task(message: types.Message):
    free_stations = game_info.get_free_stations()
    if free_stations:
        kb = [[types.KeyboardButton(text=station)] for station in free_stations]
        keyboard = types.ReplyKeyboardMarkup(
            keyboard=kb,
            resize_keyboard=True,
            input_field_placeholder="Выберите станцию для перенаправления"
        )
        await message.answer("Выберите станцию для перенаправления команды:", reply_markup=keyboard)
    else:
        await message.reply("Нет свободных станций для перенаправления команды.")

@dp.message(F.text.in_(game_info.get_free_stations()))
async def handle_station_selection(message: types.Message):
    selected_station = message.text
    station = game_info.get_station_by_id(message.from_user.id)

    if station and selected_station:
        game_info.set_station_status(station, True)  # Освобождаем текущую станцию
        game_info.set_station_status(selected_station, False)  # Занимаем новую станцию
        await message.reply(f"Команда успешно перенаправлена на станцию {selected_station}.")
        
        for user_id, user_station in game_info.caretakers.items():
            if user_station == selected_station:
                await bot.send_message(user_id, f"К вам перенаправлена команда от станции {station}.")

async def main():
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())
