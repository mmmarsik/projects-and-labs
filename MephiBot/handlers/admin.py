from aiogram import Router, F
from aiogram.filters.command import Command
from aiogram.types import Message
from aiogram.filters import BaseFilter
from aiogram.fsm.context import FSMContext
from aiogram.fsm.state import default_state, State, StatesGroup
from aiogram.filters import StateFilter


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


@admin_router.message(StateFilter(FSMStatesRegister.choose_name), F.text.isalpha())
async def process_name_sent(message: Message, state: FSMContext):
    await state.update_data(name=message.text)
    await message.answer(f"Вы ввели название команды: {message.text}\n"
                         f"Подтверждаете?")
    await state.set_state(FSMStatesRegister.accept_info)


@admin_router.message(StateFilter(FSMStatesRegister.fill_name))
async def warning_not_name(message: Message):
    await message.answer(
        f'То, что вы отправили не похоже на название команды\n\n'
        f'Пожалуйста, верное название\n\n'
        f'Если вы хотите прервать заполнение - '
        f'отправьте команду /cancel'
    )

