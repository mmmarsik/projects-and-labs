#include "task.h"
#include "logged_command_wrapper.h"
#include <memory>
#include <iostream>
#include <cctype>

class CommandBuilder;

/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        editor.UnselectText();
        if (cursorPosition > 0) {
            --cursorPosition;
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        editor.UnselectText();
        if (cursorPosition < buffer.length()) {
            ++cursorPosition;
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitMoveCursorRightCommand(*this);
    }
};

/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {

        editor.UnselectText();
        size_t start = cursorPosition;

        if (cursorPosition == 0) {
            return;
        }
        --cursorPosition;
        ++cnt_letters_from_str_begin;

        // Посчитали длину нашей строки
        while (cursorPosition > 0 && editor.GetCharUnderCursor() != '\n') {

            ++cnt_letters_from_str_begin;
            --cursorPosition;
        }

        if (cursorPosition == 0) {
            cursorPosition = start;
            return;
        }
        --cursorPosition;
        ++len_of_prev_str;

        while (cursorPosition > 0 && editor.GetCharUnderCursor() != '\n') {
            --cursorPosition;
            ++len_of_prev_str;
        }

        if (cursorPosition != 0) {
            ++cursorPosition;
            --len_of_prev_str;
        }
        --cnt_letters_from_str_begin;

        cursorPosition += std::min(len_of_prev_str, cnt_letters_from_str_begin);
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitMoveCursorUpCommand(*this);
    }

private:
    size_t cnt_letters_from_str_begin = 0;
    size_t len_of_prev_str = 0;
};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        size_t pastPoS = cursorPosition;

        editor.UnselectText();

        while (cursorPosition > 0 && editor.GetCharUnderCursor() != '\n') {
            ++cnt_letters_from_str_begin;
            --cursorPosition;
        }
        if (cursorPosition != 0) {
            --cnt_letters_from_str_begin;
            ++cursorPosition;
        }

        while (cursorPosition < buffer.length() && editor.GetCharUnderCursor() != '\n') {
            ++cursorPosition;
        }

        if (cursorPosition == buffer.length()) {
            cursorPosition = pastPoS;
            return;
        }

        ++cursorPosition;

        for (size_t i = 0;
             i < buffer.length() && i < cnt_letters_from_str_begin && editor.GetCharUnderCursor() != '\n'; ++i) {
            ++cursorPosition;
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitMoveCursorDownCommand(*this);
    }

private:
    size_t cnt_letters_from_str_begin = 0;
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
public:
    SelectTextCommand(size_t sym_size_) : sym_size(sym_size_) {}

    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        editor.SelectText(cursorPosition, cursorPosition + sym_size);
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitSelectCommand(*this);
    }

private:
    size_t sym_size;
};

/* Ввести текст */
class InsertTextCommand : public ICommand {
public:
    explicit InsertTextCommand(std::string &text) : text_(text) {}

    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        if (editor.HasSelection()) {
            buffer.erase(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
            editor.UnselectText();
        }

        buffer.insert(cursorPosition, text_);
        cursorPosition += text_.length();
    }


    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitInsertTextCommand(*this);
    }

private:
    std::string text_;
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
public:

    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        if (editor.HasSelection()) {
            buffer.erase(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first + 1);
            editor.UnselectText();
        } else if (cursorPosition > 0) {
            buffer.erase(cursorPosition, 1);
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitDeleteTextCommand(*this);
    }
};

/* Скопировать текст */
class CopyTextCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        if (editor.HasSelection()) {
            clipboard = buffer.substr(editor.GetSelection().first,
                                      editor.GetSelection().second - editor.GetSelection().first);
            editor.UnselectText();
        } else {
            clipboard = editor.GetCharUnderCursor();
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitCopyTextCommand(*this);
    }
};

/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        if (editor.HasSelection()) {
            buffer.erase(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
            editor.UnselectText();
        }
        buffer.insert(cursorPosition, clipboard);
        cursorPosition += clipboard.length();
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitPasteTextCommand(*this);
    }
};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        if (editor.HasSelection()) {
            std::transform(buffer.begin() + editor.GetSelection().first, buffer.begin() + editor.GetSelection().second,
                           buffer.begin(), ::toupper);
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        if (editor.HasSelection()) {
            std::transform(buffer.begin() + editor.GetSelection().first, buffer.begin() + editor.GetSelection().second,
                           buffer.begin(), ::tolower);
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitLowercaseTextCommand(*this);
    }
};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        editor.UnselectText();
        while (editor.GetCharUnderCursor() != '\n' && cursorPosition < buffer.length()) {
            ++cursorPosition;
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitMoveToEndCommand(*this);
    }
};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {

        editor.UnselectText();

        while (cursorPosition > 0 && editor.GetCharUnderCursor() != '\n') {
            --cursorPosition;
        }
        if (cursorPosition != 0) {
            ++cursorPosition;
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitMoveToStartCommand(*this);
    }
};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {
public:
    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {

        editor.UnselectText();

        size_t len = 0;
        size_t spaceIndex = buffer.find_first_of(' ', cursorPosition);
        size_t endlIndex = buffer.find_first_of('\n', cursorPosition);

        if (spaceIndex == std::string::npos && endlIndex == std::string::npos) {
            len = buffer.length() - cursorPosition;
        } else if (spaceIndex == std::string::npos) {
            len = endlIndex - cursorPosition;
        } else if (endlIndex == std::string::npos) {
            len = spaceIndex - cursorPosition;
        } else {
            len = std::min(endlIndex, spaceIndex) - cursorPosition;
        }

        if (cursorPosition + len >= buffer.length()) {
            len = buffer.length() - cursorPosition;
        }

        buffer.erase(cursorPosition, len);

    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        visitor.VisitDeleteWordCommand(*this);
    }
};

/* Макрос */
class MacroCommand : public ICommand {
public:
    MacroCommand(std::list<CommandPtr> &subcommands) : subcommands_(subcommands) {}

    void Apply(std::string &buffer, size_t &cursorPosition, std::string &clipboard, TextEditor &editor) override {
        for (auto &x: subcommands_) {
            x->Apply(buffer, cursorPosition, clipboard, editor);
        }
    }

    void AcceptVisitor(CommandVisitor &visitor) override {
        for (auto &x: subcommands_) {
            x->AcceptVisitor(visitor);
        }
    }

private:
    std::list<CommandPtr> subcommands_;
};

CommandLoggerVisitor::CommandLoggerVisitor(std::ostream &logStream) : logStream_(logStream) {}

void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand &command) {
    logStream_ << "h";
}

void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand &command) {
    logStream_ << "l";
}

void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand &command) {
    logStream_ << "k";
}

void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand &command) {
    logStream_ << "j";
}

void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand &command) {
    logStream_ << "v";
}

void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand &command) {
    logStream_ << "i";
}

void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand &command) {
    logStream_ << "d";
}

void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand &command) {
    logStream_ << "y";
}

void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand &command) {
    logStream_ << "p";
}

void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand &command) {
    logStream_ << "U";
}

void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand &command) {
    logStream_ << "u";
}

void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand &command) {
    logStream_ << "$";
}

void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand &command) {
    logStream_ << "0";
}

void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand &command) {
    logStream_ << "dE";
}


using CommandPtr = std::shared_ptr<ICommand>;

CommandBuilder::CommandBuilder() : selectionSize_(0), logStreamPtr_(nullptr) {}


CommandPtr CommandBuilder::build() {
    if (type_ == Type::MoveCursorLeft) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MoveCursorLeftCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MoveCursorLeftCommand>());
    }
    if (type_ == Type::MoveCursorRight) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MoveCursorRightCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MoveCursorRightCommand>());
    }
    if (type_ == Type::MoveCursorUp) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MoveCursorUpCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MoveCursorUpCommand>());
    }
    if (type_ == Type::MoveCursorDown) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MoveCursorDownCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MoveCursorDownCommand>());
    }
    if (type_ == Type::SelectText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<SelectTextCommand>(selectionSize_);
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_,
                                                      std::make_shared<SelectTextCommand>(selectionSize_));
    }
    if (type_ == Type::InsertText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<InsertTextCommand>(text_);
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<InsertTextCommand>(text_));
    }
    if (type_ == Type::DeleteText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<DeleteTextCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<DeleteTextCommand>());
    }
    if (type_ == Type::CopyText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<CopyTextCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<CopyTextCommand>());
    }
    if (type_ == Type::PasteText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<PasteTextCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<PasteTextCommand>());
    }
    if (type_ == Type::UppercaseText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<UppercaseTextCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<UppercaseTextCommand>());
    }
    if (type_ == Type::LowercaseText) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<LowercaseTextCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<LowercaseTextCommand>());
    }
    if (type_ == Type::MoveToEnd) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MoveToEndCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MoveToEndCommand>());
    }
    if (type_ == Type::MoveToStart) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MoveToStartCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MoveToStartCommand>());
    }
    if (type_ == Type::DeleteWord) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<DeleteWordCommand>();
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<DeleteWordCommand>());
    }
    if (type_ == Type::Macro) {
        if (logStreamPtr_ == nullptr) {
            return std::make_shared<MacroCommand>(subcommands_);
        }
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, std::make_shared<MacroCommand>(subcommands_));
    }
    return nullptr;
}


CommandBuilder &CommandBuilder::WithType(CommandBuilder::Type type) {
    type_ = type;
    return *this;
}

CommandBuilder &CommandBuilder::SelectionSize(size_t selectionSize) {
    selectionSize_ = selectionSize;
    return *this;
}



CommandBuilder &CommandBuilder::Text(std::string text) {
    text_ = text;
    return *this;
}

CommandBuilder &CommandBuilder::LogTo(std::ostream &logStream) {
    logStreamPtr_ = &logStream;
    return *this;
}

CommandBuilder &CommandBuilder::AddSubcommand(CommandPtr subcommand) {
    subcommands_.push_back(subcommand);
    return *this;
}
