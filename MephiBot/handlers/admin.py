from aiogram import Router, F
from aiogram.filters.command import Command
from aiogram.types import Message
from aiogram.filters import BaseFilter
from aiogram.fsm.context import FSMContext
from aiogram.fsm.state import default_state, State, StatesGroup
from aiogram.filters import StateFilter
from aiogram.utils.keyboard import ReplyKeyboardBuilder
from aiogram import types


from bot import game_info
from bot import storage


class IsAdminFilter(BaseFilter):
    async def __call__(self, message: Message) -> bool:
        return message.from_user.id in game_info.admins


admin_router = Router()
admin_router.message.filter(IsAdminFilter())


class FSMStatesRegister(StatesGroup):
    choose_name = State()
    accept_info = State()


@admin_router.message(Command("start"), StateFilter(default_state))
async def cmd_start(message: Message):
    await message.answer(f"Привет, {message.from_user.first_name}, твоя роль - адимн\n"
                         f"Чтобы зарегистрировать команду, напиши: /register"
                         )


@admin_router.message(Command("cancel"), StateFilter(default_state))
async def cmd_cancel(message: Message):
    await message.answer(f"Вы находитесь вне процесса регистрации команд, отменять нечего")


@admin_router.message(Command("cancel"), ~StateFilter(default_state))
async def process_cancel_command_state(message: Message, state: FSMContext):
    await message.answer(f"Вы сбросили процесс регистрации команды, чтобы повторить его напишите /register")
    await state.clear()


@admin_router.message(Command("register"), StateFilter(default_state))
async def cmd_register(message: Message, state: FSMContext):
    await message.answer(f"Введите название команды")
    await state.set_state(FSMStatesRegister.choose_name)


@admin_router.message(StateFilter(FSMStatesRegister.choose_name), F.text)
async def process_name_sent(message: Message, state: FSMContext):
    await state.update_data(name=message.text)

    builder = ReplyKeyboardBuilder()

    builder.add(types.KeyboardButton(text="Да"))
    builder.add(types.KeyboardButton(text="Нет"))
    builder.adjust(2)

    await message.answer(f"Вы ввели название команды: {message.text}\n"
                         f"Верно?", reply_markup=builder.as_markup(resize_keyboard=True),)

    await state.set_state(FSMStatesRegister.accept_info)


@admin_router.message(StateFilter(FSMStatesRegister.choose_name))
async def warning_not_name(message: Message):
    await message.answer(
        f'То, что вы отправили не похоже на название команды\n\n'
        f'Пожалуйста, введите верное название\n\n'
        f'Если вы хотите прервать заполнение - '
        f'отправьте команду /cancel'
    )


@admin_router.message(StateFilter(FSMStatesRegister.accept_info), F.text.lower() == "да")
async def cheking_correct_name(message: Message, state: FSMContext):
    team_name: str = FSMContext.get_data()["name"]
    game_info.add_team(team_name)

    next_station: str = game_info.get_next_free_station(team_name)
    game_info.lock_station(next_station, team_name)

    await state.clear()
    await message.answer(f"Вы успешно зарегистрировали команду {team_name}\n, она отправлена на станцию {next_station}"
                         f"Чтобы посмотреть список зарегистрированных команд напишите /showteams")

@admin_router.message(Command("showteams"))
async def cmd_show_teams(message: Message):
    string_teams_presentation: str = ""
    for team in game_info.teams:
        string_teams_presentation += team
        string_teams_presentation += " "
    if (len(string_teams_presentation) > 0 ):
        await message.answer(f"{string_teams_presentation}")
    else:
        await message.answer(f"Пока что не было зарегистрировано ни одной команды")

@admin_router.message(StateFilter(FSMStatesRegister.accept_info), F.text.lower() == "нет")
async def cheking_correct_name(message: Message, state: FSMContext):
    state.clear()
    await message.answer(f"Процесс регистрации был отменен, чтобы повторить напишите /register")

@admin_router.message(StateFilter(FSMStatesRegister.accept_info))
async def cheking_not_correct_name(message: Message, state: FSMContext):
     await message.answer(
        f'Вы отправили что-то некорректное\n\n'
        f'Пожалуйста, напишите Да, если название верно, иначе напишите Нет\n\n'
        f'Если вы хотите прервать заполнение - '
        f'отправьте команду /cancel'
    )

    








