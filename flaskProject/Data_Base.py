import sqlite3
from datetime import datetime, timedelta

""" Контекстный менеджер для создания соединения с базой данных"""
class DatabaseConnection:
    def __enter__(self):
        try:
            self.conn = sqlite3.connect('data/data_base_file.db')
            return self.conn
        except Exception as e:
            print(e)
            return None

    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.conn:
            self.conn.close()

def create_table():
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                sql = '''CREATE TABLE IF NOT EXISTS codes_base (
                    id INTEGER PRIMARY KEY,
                    title TEXT NOT NULL,
                    description TEXT,
                    language TEXT,
                    code TEXT NOT NULL,
                    hash TEXT UNIQUE NOT NULL,
                    creation_time TEXT NOT NULL,
                    expiration_time TEXT,
                    bananas INTEGER DEFAULT 0
                )'''
                conn.execute(sql)
                print("Таблица 'codes_base' успешно создана или уже существует.")
            except sqlite3.Error as e:
                print(f"Не удалось создать таблицу: {e}")

def insert_code(title, description, language, code, code_hash, expiration_hours=9999):
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                now = datetime.now()
                expiration = now + timedelta(hours=expiration_hours)
                sql = '''INSERT INTO codes_base(title, description, language, code, hash, creation_time, expiration_time)
                         VALUES(?,?,?,?,?,?,?)'''
                cur = conn.cursor()
                cur.execute(sql, (title, description, language, code, code_hash, now, expiration))
                conn.commit()
                return cur.lastrowid
            except Exception as e:
                print(e)

def update_bananas_by_hash(code_hash):
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                sql = '''UPDATE codes_base SET bananas = bananas + 1 WHERE hash = ?'''
                cur = conn.cursor()
                cur.execute(sql, (code_hash,))
                conn.commit()
            except Exception as e:
                print(e)

def give_banana_from_client(code_hash, client_ip):
    if not banana_was_given(client_ip, code_hash):
        with DatabaseConnection() as conn:
            if conn is not None:
                try:
                    sql = '''INSERT INTO client_bananas(client_ip, hash) VALUES(?, ?)'''
                    cur = conn.cursor()
                    cur.execute(sql, (client_ip, code_hash))
                    conn.commit()
                    update_bananas_by_hash(code_hash)
                except Exception as e:
                    print(e)

def get_top_codes_by_bananas():
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                cur = conn.cursor()
                cur.execute("SELECT * FROM codes_base ORDER BY bananas DESC LIMIT 10")
                results = cur.fetchall()
                return results
            except Exception as e:
                print(f"Не удалось получить топ кодов: {e}")

def delete_expired_codes():
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                now = datetime.now()
                sql_codes_base = '''DELETE FROM codes_base WHERE expiration_time < ?'''
                cur = conn.cursor()
                cur.execute(sql_codes_base, (now,))
                print(f"Удалено {cur.rowcount} истекших кодов из codes_base.")

                sql_client_bananas = '''DELETE FROM client_bananas WHERE hash NOT IN (SELECT hash FROM codes_base)'''
                cur.execute(sql_client_bananas)
                conn.commit()
                print(f"Удалено {cur.rowcount} истекших записей из client_bananas.")
            except Exception as e:
                print(f"Не удалось удалить истекшие коды: {e}")
def delete_code_by_hash_if_expired(code_hash):
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                now = datetime.now()
                sql = '''DELETE FROM codes_base WHERE hash = ? AND expiration_time < ?'''
                cur = conn.cursor()
                cur.execute(sql, (code_hash, now))
                conn.commit()
                if cur.rowcount > 0:
                    print(f"Код с хешем {code_hash} удален, так как срок его действия истек.")
                else:
                    print(f"Не найдено истекших кодов с хешем {code_hash} для удаления.")
            except Exception as e:
                print(f"Не удалось удалить код по хешу, если срок его действия истек: {e}")

last_cleanup_time = None

def access_code_by_hash(code_hash):
    global last_cleanup_time
    current_time = datetime.now()

    if last_cleanup_time is None or (current_time - last_cleanup_time).total_seconds() >= 7200:
        delete_expired_codes()
        last_cleanup_time = current_time

    delete_code_by_hash_if_expired(code_hash)
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                sql = '''SELECT * FROM codes_base WHERE hash = ?'''
                cur = conn.cursor()
                cur.execute(sql, (code_hash,))
                code = cur.fetchone()
                if code:
                    print("Получен код:", code)
                    return code
                else:
                    print("Не нашлось ни одного кода, возможно он был удален.")
            except Exception as e:
                print(f"Не смог получить доступ к коду по хешу {code_hash} ошибка : {e}")

def create_client_bananas_table():
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                sql = '''CREATE TABLE IF NOT EXISTS client_bananas (
                    client_ip TEXT NOT NULL,
                    hash TEXT NOT NULL,
                    FOREIGN KEY (hash) REFERENCES codes_base(hash),
                    PRIMARY KEY (client_ip, hash)
                )'''
                conn.execute(sql)
                print("Таблица 'client_bananas' успешно создана.")
            except sqlite3.Error as e:
                print(f"Не удалось создать таблицу 'client_bananas': {e}")

def banana_was_given(client_ip, code_hash):
    with DatabaseConnection() as conn:
        if conn is not None:
            try:
                sql = '''SELECT 1 FROM client_bananas WHERE client_ip = ? AND hash = ?'''
                cur = conn.cursor()
                cur.execute(sql, (client_ip, code_hash))
                return cur.fetchone() is not None
            except Exception as e:
                print(e)
                return False