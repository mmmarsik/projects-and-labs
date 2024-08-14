from aiogram import Router, F
from aiogram.filters.command import Command
from aiogram.types import Message
from aiogram import Bot, Dispatcher, types
from aiogram.utils.keyboard import ReplyKeyboardBuilder
from aiogram.filters import BaseFilter

from bot import game_info
from bot import bot

class IsCaretakerFilter(BaseFilter):
    async def __call__(self, message: Message) -> bool:
        return message.from_user.id in game_info.caretakers

caretaker_router = Router()
caretaker_router.message.filter(IsCaretakerFilter())

@caretaker_router.message(Command("start"))
async def cmd_start(message: types.Message):
    station = game_info.get_station_by_id(message.from_user.id)
    if station:
        await message.answer(
            (f"Привет, {message.from_user.full_name}, твоя станция это - {station}\n"
             f"Чтобы начать , напиши команду: /go"))


@caretaker_router.message(Command("go"))
async def cmd_work(message: types.Message):
    builder = ReplyKeyboardBuilder()

    builder.add(types.KeyboardButton(text="Принять новую команду"))
    builder.add(types.KeyboardButton(text="Перенаправить текущую команду"))

    builder.adjust(2)

    await message.answer(
        "Что вы хотите сделать?",
        reply_markup=builder.as_markup(resize_keyboard=True),
    )


@caretaker_router.message(F.text.lower() == "принять новую команду")
async def accept_new_task(message: types.Message):
    station = game_info.get_station_by_id(message.from_user.id)
    team = game_info.get_team_by_station(station)

    print(f"station is {station} and team is {team}")

    if station and team:
        game_info.start_station_progress(station)
        await message.reply(f"Вы успешно приняли новую команду '{team}' на станцию {station}.")
    else:
        await message.reply("Не удалось принять команду. Ваша станция занята или не найдена.")


@caretaker_router.message(F.text.lower() == "перенаправить текущую команду")
async def redirect_task(message: types.Message):
    station = game_info.get_station_by_id(message.from_user.id)
    team_name = game_info.get_team_by_station(station)

    is_any_team_completing: bool = game_info.is_station_in_progress(station)

    if (is_any_team_completing):
        game_info.free_station(station)

    if station and team_name and is_any_team_completing:
        next_free_station = game_info.get_next_free_station(team_name)

        if next_free_station:
            game_info.lock_station(next_free_station, team_name)

            next_station_caretaker_id = game_info.get_id_by_station(
                next_free_station)
            if next_station_caretaker_id:
                await bot.send_message(next_station_caretaker_id, f"К вам идет команда '{team_name}'.")

            await message.answer(
                f"Команда '{team_name}' перенаправлена на станцию {
                    next_free_station}."
            )
        else:
            await message.reply("Нет доступных станций для перенаправления.")
    else:
        await message.reply("Нет активных команд для перенаправления.")
