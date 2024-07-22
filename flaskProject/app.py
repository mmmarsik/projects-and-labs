from flask import Flask, render_template, request
from random import randint
import hashlib
from Data_Base import *

app = Flask(__name__)
with DatabaseConnection() as conn:
    create_client_bananas_table()

# Откючение логгирования
# app.logger.disabled = True
# log = logging.getLogger('werkzeug')
# log.disabled = True

def parse_codes():
    list_of_codes = []
    codes = get_top_codes_by_bananas()
    for code in codes:
        list_of_codes.append({'title': code[1], 'hash': code[5], 'bananas': code[8]})
    return list_of_codes


@app.route('/')
def home():
    top_codes = parse_codes()
    return render_template('index.html',
                           top_codes_=top_codes)


@app.route('/submit-code', methods=['POST'])
def submit_code():
    title = request.form['name']
    if not title:
        title = 'Без имени'
    description = request.form['description']
    if not description:
        description = 'Нет описания'
    language = request.form['language']
    code = request.form['code']
    try:
        hours = int(request.form['time'])
    except Exception:
        hours = 0

    language_real, language_display = language.split('/')

    hash_string = f"{title}{description}{language}{code}"
    code_hash = hashlib.sha1(hash_string.encode()).hexdigest()[:8]

    insert_code(title, description, language, code, code_hash, expiration_hours=hours)

    top_codes = parse_codes()
    icon = f"makaka{randint(2, 10)}"
    return render_template('copy_link.html',
                           language_display_=language_display,
                           code_hash_=code_hash,
                           icon_=icon,
                           top_codes_=top_codes)


@app.route('/give_banana/<code_hash>', methods=['POST'])
def give_banana(code_hash):
    client_ip = request.headers.get('X-Forwarded-For', request.remote_addr)
    if not banana_was_given(client_ip, code_hash):
        give_banana_from_client(code_hash, client_ip)
        return "Банан добавлен"
    else:
        return "Вы уже давали банан на этот код"

@app.route('/<code_hash>')
def view_code(code_hash):
    client_ip = request.headers.get('X-Forwarded-For', request.remote_addr)
    print(client_ip)
    top_codes = parse_codes()
    code_info = access_code_by_hash(code_hash)
    if code_info:
        title = code_info[1]
        code_description = code_info[2]
        language = code_info[3].split('/')[0]
        code_text = code_info[4]
        bananas = code_info[8]
        if banana_was_given(client_ip, code_hash):
            give_banana = "Вы уже давали банан"
        else:
            give_banana = "Дать банан"
        icon = f"makaka{randint(2, 10)}"
        return render_template('code.html', code_=code_text, language_=language, title_=title, icon_=icon, code_description_=code_description, bananas_=bananas, top_codes_=top_codes, code_hash_=code_hash, give_banana_=give_banana)
    else:
        broken = f"broken{randint(1, 3)}"
        return render_template('error.html', broken_=broken, top_codes_=top_codes)

if __name__ == '__main__':
    app.run(debug=True, port=8080, host="0.0.0.0")
