#include "datastore.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMap>

// ---------- User ----------
QJsonObject User::toJson() const
{
    QJsonObject obj;
    obj["login"] = login;
    obj["password"] = password;
    obj["role"] = role;
    obj["card"] = card;
    obj["abonementUntil"] = abonementUntil.toString(Qt::ISODate);
    obj["groupLeft"] = groupLeft;
    obj["personalLeft"] = personalLeft;
    obj["spent"] = spent;
    return obj;
}

User User::fromJson(const QJsonObject &obj)
{
    User u;
    u.login = obj["login"].toString();
    u.password = obj["password"].toString();
    u.role = obj["role"].toString();
    u.card = obj["card"].toString();
    u.abonementUntil = QDate::fromString(obj["abonementUntil"].toString(), Qt::ISODate);
    u.groupLeft = obj["groupLeft"].toInt(0);
    u.personalLeft = obj["personalLeft"].toInt(0);
    u.spent = obj["spent"].toDouble(0.0);
    return u;
}

// ---------- Equipment ----------
QJsonObject Equipment::toJson() const
{
    QJsonObject obj;
    obj["name"] = name;
    obj["hall"] = hall;
    obj["status"] = status;
    return obj;
}

Equipment Equipment::fromJson(const QJsonObject &obj)
{
    Equipment eq;
    eq.name = obj["name"].toString();
    eq.hall = obj["hall"].toString();
    eq.status = obj["status"].toString();
    return eq;
}

// ---------- DataStore ----------
DataStore::DataStore()
{
    m_filePath = QCoreApplication::applicationDirPath() + QDir::separator() + "gym_data.json";
    load();
}

bool DataStore::load()
{
    m_users.clear();
    m_visits.clear();
    m_purchases.clear();
    m_trainings.clear();
    m_coachNotes.clear();
    m_equipment.clear();

    QFile file(m_filePath);
    if (!file.exists()) {
        Equipment eq1{"Беговая дорожка", "Основной зал", "Доступно"};
        Equipment eq2{"Велотренажёр", "Малый зал", "Доступно"};
        Equipment eq3{"Силовая рама", "Основной зал", "Доступно"};
        Equipment eq4{"Гантели", "Малый зал", "Доступно"};
        Equipment eq5{"Коврики", "Основной зал", "Доступно"};
        Equipment eq6{"TRX", "Малый зал", "Доступно"};
        Equipment eq7{"Боксёрская груша", "Основной зал", "Доступно"};
        m_equipment = {eq1, eq2, eq3, eq4, eq5, eq6, eq7};
        return save();
    }

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    const QByteArray data = file.readAll();
    file.close();

    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        return false;
    }

    const QJsonObject root = doc.object();

    const QJsonArray usersArray = root["users"].toArray();
    for (const QJsonValue &value : usersArray) {
        if (value.isObject()) {
            m_users.append(User::fromJson(value.toObject()));
        }
    }

    const QJsonArray visitsArray = root["visits"].toArray();
    for (const QJsonValue &value : visitsArray) {
        if (value.isObject()) {
            m_visits.append(value.toObject());
        }
    }

    const QJsonArray purchasesArray = root["purchases"].toArray();
    for (const QJsonValue &value : purchasesArray) {
        if (value.isObject()) {
            m_purchases.append(value.toObject());
        }
    }

    const QJsonArray trainingsArray = root["trainings"].toArray();
    for (const QJsonValue &value : trainingsArray) {
        if (value.isObject()) {
            m_trainings.append(value.toObject());
        }
    }

    const QJsonArray notesArray = root["coachNotes"].toArray();
    for (const QJsonValue &value : notesArray) {
        if (value.isObject()) {
            m_coachNotes.append(value.toObject());
        }
    }

    const QJsonArray equipmentArray = root["equipment"].toArray();
    if (!equipmentArray.isEmpty()) {
        for (const QJsonValue &value : equipmentArray) {
            if (value.isObject()) {
                m_equipment.append(Equipment::fromJson(value.toObject()));
            }
        }
    } else {
        Equipment eq1{"Беговая дорожка", "Основной зал", "Доступно"};
        Equipment eq2{"Велотренажёр", "Малый зал", "Доступно"};
        Equipment eq3{"Силовая рама", "Основной зал", "Доступно"};
        Equipment eq4{"Гантели", "Малый зал", "Доступно"};
        Equipment eq5{"Коврики", "Основной зал", "Доступно"};
        Equipment eq6{"TRX", "Малый зал", "Доступно"};
        Equipment eq7{"Боксёрская груша", "Основной зал", "Доступно"};
        m_equipment = {eq1, eq2, eq3, eq4, eq5, eq6, eq7};
    }

    return true;
}

bool DataStore::save() const
{
    QJsonArray usersArray;
    for (const User &user : m_users) {
        usersArray.append(user.toJson());
    }

    QJsonArray visitsArray;
    for (const QJsonObject &obj : m_visits) {
        visitsArray.append(obj);
    }

    QJsonArray purchasesArray;
    for (const QJsonObject &obj : m_purchases) {
        purchasesArray.append(obj);
    }

    QJsonArray trainingsArray;
    for (const QJsonObject &obj : m_trainings) {
        trainingsArray.append(obj);
    }

    QJsonArray notesArray;
    for (const QJsonObject &obj : m_coachNotes) {
        notesArray.append(obj);
    }

    QJsonArray equipmentArray;
    for (const Equipment &eq : m_equipment) {
        equipmentArray.append(eq.toJson());
    }

    QJsonObject root;
    root["users"] = usersArray;
    root["visits"] = visitsArray;
    root["purchases"] = purchasesArray;
    root["trainings"] = trainingsArray;
    root["coachNotes"] = notesArray;
    root["equipment"] = equipmentArray;

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

// ----- Пользователи -----
bool DataStore::hasUser(const QString &login) const
{
    return userIndex(login) >= 0;
}

int DataStore::userIndex(const QString &login) const
{
    for (int i = 0; i < m_users.size(); ++i) {
        if (m_users[i].login.compare(login, Qt::CaseInsensitive) == 0) {
            return i;
        }
    }
    return -1;
}

User DataStore::user(const QString &login) const
{
    const int index = userIndex(login);
    if (index >= 0) {
        return m_users[index];
    }
    return User();
}

bool DataStore::addUser(const User &user)
{
    if (user.login.trimmed().isEmpty() || hasUser(user.login)) {
        return false;
    }
    m_users.append(user);
    return save();
}

bool DataStore::updateUser(const User &user)
{
    const int index = userIndex(user.login);
    if (index < 0) {
        return false;
    }
    m_users[index] = user;
    return save();
}

bool DataStore::deleteUser(const QString &login)
{
    const int index = userIndex(login);
    if (index < 0) {
        return false;
    }
    m_users.remove(index);
    return save();
}

bool DataStore::checkPassword(const QString &login, const QString &password) const
{
    const int index = userIndex(login);
    if (index < 0) {
        return false;
    }
    return m_users[index].password == password;
}

QVector<User> DataStore::users() const
{
    return m_users;
}

QStringList DataStore::clients() const
{
    QStringList result;
    for (const User &u : m_users) {
        if (u.role == "Клиент") {
            result << u.login;
        }
    }
    result.sort(Qt::CaseInsensitive);
    return result;
}

QStringList DataStore::trainers() const
{
    QStringList result;
    for (const User &u : m_users) {
        if (u.role == "Тренер") {
            result << u.login;
        }
    }
    result.sort(Qt::CaseInsensitive);
    return result;
}

QStringList DataStore::clientsWithCards() const
{
    QStringList result;
    for (const User &u : m_users) {
        if (u.role == "Клиент") {
            result << QString("%1 / ID: %2").arg(u.login, u.card.isEmpty() ? "нет" : u.card);
        }
    }
    result.sort(Qt::CaseInsensitive);
    return result;
}

// ----- Посещения -----
// ... все остальные методы без изменений, меняется только addVisit:

void DataStore::addVisit(const QString &clientLogin, const QString &type, const QString &className,
                         bool deductLesson, double price, const QString &comment)
{
    Q_UNUSED(deductLesson);
    User u = user(clientLogin);
    QString writeOff = "нет";

    bool isPaidLesson = type.contains("Групп", Qt::CaseInsensitive) || type.contains("Персон", Qt::CaseInsensitive);

    if (isPaidLesson && price > 0) {
        // Всегда списываем деньги за занятие, абонемент не влияет
        QString purchaseName = QString("%1 (%2)").arg(className, type);
        QJsonObject obj;
        obj["client"] = clientLogin;
        obj["name"] = purchaseName;
        obj["price"] = price;
        obj["groupAdd"] = 0;
        obj["personalAdd"] = 0;
        obj["monthsAdd"] = 0;
        obj["dateTime"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        m_purchases.prepend(obj);
        u.spent += price;
        updateUser(u);
        writeOff = QString("Списано %1 ₽").arg(price);
    } else {
        writeOff = "нет";
    }

    QJsonObject obj;
    obj["client"] = clientLogin;
    obj["type"] = type;
    obj["className"] = className;
    obj["writeOff"] = writeOff;
    obj["comment"] = comment;
    obj["dateTime"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    m_visits.prepend(obj);
    save();
}

QVector<QJsonObject> DataStore::visits() const
{
    return m_visits;
}

bool DataStore::deleteVisit(int index)
{
    if (index < 0 || index >= m_visits.size()) return false;
    m_visits.remove(index);
    return save();
}

// ----- Покупки -----
void DataStore::addPurchase(const QString &clientLogin, const QString &name, double price, int groupAdd, int personalAdd, int monthsAdd)
{
    User u = user(clientLogin);
    if (!u.login.isEmpty()) {
        u.groupLeft += groupAdd;
        u.personalLeft += personalAdd;
        u.spent += price;

        const QDate today = QDate::currentDate();
        QDate base = u.abonementUntil.isValid() && u.abonementUntil > today ? u.abonementUntil : today;
        if (monthsAdd > 0) {
            u.abonementUntil = base.addMonths(monthsAdd);
        }
        updateUser(u);
    }

    QJsonObject obj;
    obj["client"] = clientLogin;
    obj["name"] = name;
    obj["price"] = price;
    obj["groupAdd"] = groupAdd;
    obj["personalAdd"] = personalAdd;
    obj["monthsAdd"] = monthsAdd;
    obj["dateTime"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    m_purchases.prepend(obj);
    save();
}

QVector<QJsonObject> DataStore::purchases() const
{
    return m_purchases;
}

bool DataStore::deletePurchase(int index)
{
    if (index < 0 || index >= m_purchases.size()) return false;
    m_purchases.remove(index);
    return save();
}

// ----- Тренировки -----
void DataStore::addTraining(const QString &clientLogin, const QString &trainerLogin, const QString &type,
                            const QString &className, const QDateTime &dateTime, const QString &note)
{
    QJsonObject obj;
    obj["client"] = clientLogin;
    obj["trainer"] = trainerLogin;
    obj["type"] = type;
    obj["className"] = className;
    obj["dateTime"] = dateTime.toString(Qt::ISODate);
    obj["note"] = note;
    m_trainings.prepend(obj);
    save();
}

QVector<QJsonObject> DataStore::trainings() const
{
    return m_trainings;
}

bool DataStore::removeTraining(const QString &clientLogin, const QDateTime &dateTime, const QString &trainerLogin, const QString &type, const QString &className)
{
    QDateTime dtRounded = dateTime;
    dtRounded.setTime(QTime(dtRounded.time().hour(), dtRounded.time().minute(), 0, 0));
    for (int i = 0; i < m_trainings.size(); ++i) {
        const QJsonObject obj = m_trainings[i];
        QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        dt.setTime(QTime(dt.time().hour(), dt.time().minute(), 0, 0));
        if (obj["client"].toString() == clientLogin &&
            dt == dtRounded &&
            obj["trainer"].toString() == trainerLogin &&
            obj["type"].toString() == type &&
            obj["className"].toString() == className) {
            m_trainings.remove(i);
            return save();
        }
    }
    return false;
}

bool DataStore::updateTrainingDateTime(const QString &clientLogin, const QDateTime &oldDateTime,
                                       const QDateTime &newDateTime, const QString &trainerLogin,
                                       const QString &type, const QString &className)
{
    QDateTime oldRounded = oldDateTime;
    oldRounded.setTime(QTime(oldRounded.time().hour(), oldRounded.time().minute(), 0, 0));
    for (int i = 0; i < m_trainings.size(); ++i) {
        QJsonObject obj = m_trainings[i];
        QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        dt.setTime(QTime(dt.time().hour(), dt.time().minute(), 0, 0));
        if (obj["client"].toString() == clientLogin &&
            dt == oldRounded &&
            obj["trainer"].toString() == trainerLogin &&
            obj["type"].toString() == type &&
            obj["className"].toString() == className) {
            QDateTime newRounded = newDateTime;
            newRounded.setTime(QTime(newRounded.time().hour(), newRounded.time().minute(), 0, 0));
            obj["dateTime"] = newRounded.toString(Qt::ISODate);
            m_trainings[i] = obj;
            return save();
        }
    }
    return false;
}
// ----- Заметки -----
void DataStore::addCoachNote(const QString &trainerLogin, const QString &clientLogin,
                             const QString &kind, const QString &text, const QDateTime &dateTime)
{
    QJsonObject obj;
    obj["trainer"] = trainerLogin;
    obj["client"] = clientLogin;
    obj["kind"] = kind;
    obj["text"] = text;
    obj["dateTime"] = dateTime.toString(Qt::ISODate);
    m_coachNotes.prepend(obj);
    save();
}

QVector<QJsonObject> DataStore::coachNotes() const
{
    return m_coachNotes;
}

// ----- Оборудование -----
QVector<Equipment> DataStore::equipmentList() const
{
    return m_equipment;
}

bool DataStore::addEquipment(const Equipment &eq)
{
    m_equipment.append(eq);
    return save();
}

bool DataStore::removeEquipment(int index)
{
    if (index < 0 || index >= m_equipment.size()) return false;
    m_equipment.remove(index);
    return save();
}

bool DataStore::updateEquipment(int index, const Equipment &eq)
{
    if (index < 0 || index >= m_equipment.size()) return false;
    m_equipment[index] = eq;
    return save();
}

// ----- Аналитика -----
double DataStore::totalRevenue() const
{
    double sum = 0.0;
    for (const QJsonObject &obj : m_purchases) {
        sum += obj["price"].toDouble(0.0);
    }
    return sum;
}

int DataStore::totalVisits() const
{
    return m_visits.size();
}

QString DataStore::popularTrainingText() const
{
    QMap<QString, int> counter;
    for (const QJsonObject &obj : m_visits) {
        const QString className = obj["className"].toString().trimmed();
        if (!className.isEmpty()) {
            counter[className] += 1;
        }
    }

    QString bestName = "нет данных";
    int bestCount = 0;
    for (auto it = counter.constBegin(); it != counter.constEnd(); ++it) {
        if (it.value() > bestCount) {
            bestName = it.key();
            bestCount = it.value();
        }
    }

    if (bestCount == 0) {
        return bestName;
    }
    return QString("%1 (%2 записей)").arg(bestName).arg(bestCount);
}

int DataStore::churnClients() const
{
    int count = 0;
    const QDate today = QDate::currentDate();
    for (const User &u : m_users) {
        if (u.role == "Клиент" && u.abonementUntil.isValid() && u.abonementUntil < today) {
            ++count;
        }
    }
    return count;
}

QString DataStore::filePath() const
{
    return m_filePath;
}

// ----- Проверка занятости тренера (интервал 1 час) -----
bool DataStore::isTrainerBusy(const QString &trainerLogin, const QDateTime &dateTime) const
{
    QDateTime start = dateTime;
    QDateTime end = start.addSecs(3600);

    for (const QJsonObject &obj : m_trainings) {
        if (obj["trainer"].toString() != trainerLogin) continue;
        QDateTime existingStart = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        QDateTime existingEnd = existingStart.addSecs(3600);
        if (start < existingEnd && end > existingStart) {
            return true;
        }
    }
    return false;
}

bool DataStore::isTrainerBusyExcept(const QString &trainerLogin, const QDateTime &dateTime,
                                    const QString &excludeClientLogin, const QDateTime &excludeDateTime) const
{
    QDateTime start = dateTime;
    QDateTime end = start.addSecs(3600);

    for (const QJsonObject &obj : m_trainings) {
        if (obj["trainer"].toString() != trainerLogin) continue;
        if (obj["client"].toString() == excludeClientLogin &&
            QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate) == excludeDateTime) {
            continue;
        }
        QDateTime existingStart = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        QDateTime existingEnd = existingStart.addSecs(3600);
        if (start < existingEnd && end > existingStart) {
            return true;
        }
    }
    return false;
}

QDateTime DataStore::getNextAvailableSlot(const QString &trainerLogin, const QDateTime &desiredTime) const
{
    QDateTime candidate = desiredTime;
    // Округляем до следующего часа, если минуты или секунды не равны нулю
    if (candidate.time().minute() != 0 || candidate.time().second() != 0) {
        candidate = candidate.addSecs(3600 - candidate.time().minute()*60 - candidate.time().second());
        candidate.setTime(QTime(candidate.time().hour(), 0, 0));
    }
    while (isTrainerBusy(trainerLogin, candidate)) {
        candidate = candidate.addSecs(3600);
    }
    return candidate;
}