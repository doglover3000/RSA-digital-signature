# Qt RSA Digital Signature System

Кроссплатформенное настольное приложение для генерации и проверки электронной цифровой подписи (ЭЦП), реализованное на C++ с использованием фреймворка Qt. Поддерживает регистрацию пользователей, создание ключей RSA, формирование подписи и проверку подлинности файлов. Данные пользователей хранятся в базе данных MS SQL.

## 🔧 Функциональные возможности

- Регистрация пользователя с генерацией пары ключей RSA
- Хэширование файла (SHA1/MD5)
- Создание цифровой подписи на основе RSA
- Проверка подлинности подписи
- Хранение открытых ключей на сервере
- Поддержка ОС: Windows, Linux (возможность переноса на MacOS)

## 🖼 Интерфейс

Приложение реализовано на Qt (Widgets):
- Формы регистрации и авторизации
- Загрузка и отображение выбранного файла
- Вывод результатов проверки подписи
- Работа с базой данных через MS SQL

## 💡 Алгоритмы и технологии

- Алгоритм RSA
- SHA1 и MD5 для хэширования
- Алгоритм Миллера–Рабина (проверка на простоту)
- Быстрое возведение в степень по модулю
- Расширенный алгоритм Евклида
- Qt 5 / 6
- MS SQL (через QSqlDatabase)

## 📦 Зависимости

- Qt 5.15+ или Qt 6
- MS SQL Server (локально или в локальной сети)
- CMake или qmake

## 📸 Скриншоты

### Главный экран
![Главная страница](main_screen.PNG)

### Регистрация
![Страница регистрации](login_screen.PNG)

### Окно проверки
![Страница проверки подписи](checker_screen.PNG)

## 📝 Лицензия

Проект создан в рамках дипломной работы и распространяется под лицензией MIT.

## 📧 Контакты

Автор: **Ханнанова Эвелина Руслановна**
Email: [evelinkah@yandex.ru](mailto:evelinkah@yandex.ru)
