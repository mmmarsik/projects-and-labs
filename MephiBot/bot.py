import asyncio
import logging
from aiogram import Bot, Dispatcher, types
from aiogram.filters.command import Command
from aiogram.enums import ParseMode
from aiogram.client.default import DefaultBotProperties
from aiogram.types import Message
from aiogram import F
from config import TOKEN
from GameInfo import GameInfo
from aiogram.utils.keyboard import ReplyKeyboardBuilder

logging.basicConfig(level=logging.INFO)

bot = Bot(token=TOKEN)
dp = Dispatcher()


game_info = GameInfo(
    caretakers={593807464: "Shreks", 1808760043: "Taxi-rider", 1413950580: "Ninja"},
    admins={},
    stations={"Shreks": True, "Taxi-rider": True, "Fax": True, "Crazy_frog": True,
              "Dancer": True, "Magic": True, "Ninja": True}
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
    builder = ReplyKeyboardBuilder()

    builder.add(types.KeyboardButton(text="Принять новую команду"))
    builder.add(types.KeyboardButton(text="Перенаправить текущую команду"))

    builder.adjust(2)

    await message.answer(
        "Что вы хотите сделать?",
        reply_markup=builder.as_markup(resize_keyboard=True),
    )


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

    if not free_stations:
        await message.reply("Нет свободных станций для перенаправления команды.")
        return

    builder = ReplyKeyboardBuilder()

    for station in free_stations:
        builder.add(types.KeyboardButton(text=station))

    builder.adjust(3)

    await message.answer(
        "Выберите станцию для перенаправления команды:",
        reply_markup=builder.as_markup(
            resize_keyboard=True, one_time_keyboard=True),
    )


@dp.message(F.text.in_(game_info.get_free_stations()))
async def handle_station_selection(message: types.Message):
    selected_station = message.text
    station = game_info.get_station_by_id(message.from_user.id)

    if station and selected_station:

        game_info.set_station_status(station, True)
        game_info.set_station_status(
            selected_station, False)
        await message.reply(f"Команда успешно перенаправлена на станцию {selected_station}.")

        for user_id, user_station in game_info.caretakers.items():
            if user_station == selected_station:
                await bot.send_message(user_id, f"К вам перенаправлена команда от станции {station}.")


async def main():
    await bot.delete_webhook(drop_pending_updates=True)
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())
