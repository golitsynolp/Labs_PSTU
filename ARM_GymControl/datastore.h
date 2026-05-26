#ifndef DATASTORE_H
#define DATASTORE_H

#include <QDate>
#include <QDateTime>
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QVector>

struct User
{
    QString login;
    QString password;
    QString role;
    QString card;
    QDate abonementUntil;
    int groupLeft = 0;
    int personalLeft = 0;
    double spent = 0.0;

    QJsonObject toJson() const;
    static User fromJson(const QJsonObject &obj);
};

struct Equipment
{
    QString name;
    QString hall;
    QString status;

    QJsonObject toJson() const;
    static Equipment fromJson(const QJsonObject &obj);
};

class DataStore
{
public:
    DataStore();

    bool load();
    bool save() const;

    // Пользователи
    bool hasUser(const QString &login) const;
    int userIndex(const QString &login) const;
    User user(const QString &login) const;
    bool addUser(const User &user);
    bool updateUser(const User &user);
    bool deleteUser(const QString &login);
    bool checkPassword(const QString &login, const QString &password) const;

    QVector<User> users() const;
    QStringList clients() const;
    QStringList trainers() const;
    QStringList clientsWithCards() const;

    // Посещения
    void addVisit(const QString &clientLogin, const QString &type, const QString &className,
                  bool deductLesson, double price, const QString &comment);
    QVector<QJsonObject> visits() const;
    bool deleteVisit(int index);

    // Покупки (только для абонементов и разовых занятий после посещения)
    void addPurchase(const QString &clientLogin, const QString &name, double price, int groupAdd, int personalAdd, int monthsAdd);
    QVector<QJsonObject> purchases() const;
    bool deletePurchase(int index);

    // Тренировки
    void addTraining(const QString &clientLogin, const QString &trainerLogin, const QString &type,
                     const QString &className, const QDateTime &dateTime, const QString &note);
    QVector<QJsonObject> trainings() const;
    bool removeTraining(const QString &clientLogin, const QDateTime &dateTime, const QString &trainerLogin, const QString &type, const QString &className);
    bool updateTrainingDateTime(const QString &clientLogin, const QDateTime &oldDateTime,
                                const QDateTime &newDateTime, const QString &trainerLogin,
                                const QString &type, const QString &className);

    // Заметки тренера
    void addCoachNote(const QString &trainerLogin, const QString &clientLogin,
                      const QString &kind, const QString &text, const QDateTime &dateTime);
    QVector<QJsonObject> coachNotes() const;

    // Оборудование
    QVector<Equipment> equipmentList() const;
    bool addEquipment(const Equipment &eq);
    bool removeEquipment(int index);
    bool updateEquipment(int index, const Equipment &eq);

    // Аналитика
    double totalRevenue() const;
    int totalVisits() const;
    QString popularTrainingText() const;
    int churnClients() const;

    QString filePath() const;

    // Проверка занятости тренера
    bool isTrainerBusy(const QString &trainerLogin, const QDateTime &dateTime) const;
    bool isTrainerBusyExcept(const QString &trainerLogin, const QDateTime &dateTime,
                             const QString &excludeClientLogin, const QDateTime &excludeDateTime) const;
    QDateTime getNextAvailableSlot(const QString &trainerLogin, const QDateTime &desiredTime) const;

private:
    QString m_filePath;
    QVector<User> m_users;
    QVector<QJsonObject> m_visits;
    QVector<QJsonObject> m_purchases;
    QVector<QJsonObject> m_trainings;
    QVector<QJsonObject> m_coachNotes;
    QVector<Equipment> m_equipment;
};

#endif // DATASTORE_H