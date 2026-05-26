#include "mainwindow.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QFont>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVariant>
#include <QAbstractItemView>
#include <QSpinBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QStyledItemDelegate>
#include <algorithm>

class ComboBoxDelegate : public QStyledItemDelegate
{
public:
    explicit ComboBoxDelegate(const QStringList &items, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), m_items(items) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        Q_UNUSED(option);
        Q_UNUSED(index);
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_items);
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int idx = comboBox->findText(value);
        if (idx >= 0) comboBox->setCurrentIndex(idx);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        Q_UNUSED(index);
        editor->setGeometry(option.rect);
    }

private:
    QStringList m_items;
};

static double getLessonPrice(const QString &className, const QString &type) {
    QHash<QString, double> groupPrices;
    groupPrices["Йога"] = 500.0;
    groupPrices["Силовая"] = 450.0;
    groupPrices["Кардио"] = 400.0;
    groupPrices["Бокс"] = 600.0;
    groupPrices["Растяжка"] = 450.0;
    groupPrices["Функциональная"] = 550.0;

    QHash<QString, double> personalPrices;
    personalPrices["Йога"] = 1500.0;
    personalPrices["Силовая"] = 1800.0;
    personalPrices["Кардио"] = 1500.0;
    personalPrices["Бокс"] = 2000.0;
    personalPrices["Растяжка"] = 1500.0;
    personalPrices["Функциональная"] = 1800.0;

    if (type.contains("Групповая", Qt::CaseInsensitive) || type.contains("Групповое", Qt::CaseInsensitive)) {
        return groupPrices.value(className, 0.0);
    } else if (type.contains("Персональная", Qt::CaseInsensitive) || type.contains("Персональное", Qt::CaseInsensitive)) {
        return personalPrices.value(className, 0.0);
    }
    return 0.0;
}

static QString getLessonDisplayString(const QString &className, const QString &type) {
    double price = getLessonPrice(className, type);
    if (price > 0) {
        return QString("%1 (%2 ₽)").arg(className).arg(price);
    }
    return className;
}

static QLabel *makeTitle(const QString &text)
{
    QLabel *label = new QLabel(text);
    QFont font = label->font();
    font.setPointSize(16);
    font.setBold(true);
    label->setFont(font);
    return label;
}

static QTableWidget *makeTable(const QStringList &headers)
{
    QTableWidget *table = new QTableWidget;
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    return table;
}

static QTableWidgetItem *item(const QString &text)
{
    return new QTableWidgetItem(text);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1100, 720);
    setWindowTitle("GymControl");
    showAuthPage();
}

void MainWindow::showAuthPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *root = new QVBoxLayout(page);
    root->setContentsMargins(40, 35, 40, 35);
    root->setSpacing(18);

    QLabel *title = makeTitle("Фитнес-зал GymControl");
    QLabel *subtitle = new QLabel("Добро пожаловать! Пожалуйста, войдите в систему или зарегистрируйтесь.");
    subtitle->setWordWrap(true);

    QStackedWidget *stacked = new QStackedWidget;

    QWidget *loginPage = new QWidget;
    QVBoxLayout *loginLayout = new QVBoxLayout(loginPage);
    QGroupBox *loginBox = new QGroupBox("Вход");
    QFormLayout *loginForm = new QFormLayout(loginBox);
    QLineEdit *loginEdit = new QLineEdit;
    QLineEdit *passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    QPushButton *loginButton = new QPushButton("Войти");
    QPushButton *toRegButton = new QPushButton("Зарегистрироваться");
    loginForm->addRow("Логин:", loginEdit);
    loginForm->addRow("Пароль:", passwordEdit);
    loginForm->addRow(loginButton);
    loginLayout->addWidget(loginBox);
    loginLayout->addWidget(toRegButton);
    loginLayout->addStretch();

    QWidget *regPage = new QWidget;
    QVBoxLayout *regLayout = new QVBoxLayout(regPage);
    QGroupBox *regBox = new QGroupBox("Регистрация нового пользователя");
    QFormLayout *regForm = new QFormLayout(regBox);
    QLineEdit *regLoginEdit = new QLineEdit;
    QLineEdit *regPasswordEdit = new QLineEdit;
    regPasswordEdit->setEchoMode(QLineEdit::Password);
    QComboBox *roleCombo = new QComboBox;
    roleCombo->addItems(QStringList() << "Администратор" << "Тренер" << "Клиент");
    QLineEdit *cardEdit = new QLineEdit;
    cardEdit->setPlaceholderText("ID / номер (для клиента)");
    QPushButton *regButton = new QPushButton("Зарегистрироваться");
    QPushButton *toLoginButton = new QPushButton("Войти");
    regForm->addRow("Логин:", regLoginEdit);
    regForm->addRow("Пароль:", regPasswordEdit);
    regForm->addRow("Роль:", roleCombo);
    regForm->addRow("ID:", cardEdit);
    regForm->addRow(regButton);
    regLayout->addWidget(regBox);
    regLayout->addWidget(toLoginButton);
    regLayout->addStretch();

    stacked->addWidget(loginPage);
    stacked->addWidget(regPage);
    stacked->setCurrentIndex(0);

    root->addWidget(title);
    root->addWidget(subtitle);
    root->addWidget(stacked);
    root->addStretch();

    connect(toRegButton, &QPushButton::clicked, this, [=]() { stacked->setCurrentIndex(1); });
    connect(toLoginButton, &QPushButton::clicked, this, [=]() { stacked->setCurrentIndex(0); });

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        const QString login = loginEdit->text().trimmed();
        const QString password = passwordEdit->text();
        if (login.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
            return;
        }
        if (!store.hasUser(login)) {
            QMessageBox::warning(this, "Ошибка", "Пользователь не найден. Зарегистрируйтесь.");
            return;
        }
        if (!store.checkPassword(login, password)) {
            QMessageBox::warning(this, "Ошибка", "Неверный пароль.");
            return;
        }
        currentUser = store.user(login);
        showDashboard();
    });

    connect(regButton, &QPushButton::clicked, this, [=]() {
        const QString login = regLoginEdit->text().trimmed();
        const QString password = regPasswordEdit->text();
        const QString role = roleCombo->currentText();
        QString card = cardEdit->text().trimmed();

        if (login.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
            return;
        }
        if (store.hasUser(login)) {
            QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует.");
            return;
        }

        if (role == "Клиент" && card.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Для регистрации клиента необходимо указать ID.");
            return;
        }

        if (!card.isEmpty()) {
            bool idExists = false;
            for (const User &u : store.users()) {
                if (u.card.compare(card, Qt::CaseInsensitive) == 0) {
                    idExists = true;
                    break;
                }
            }
            if (idExists) {
                QMessageBox::warning(this, "Ошибка", "Пользователь с таким ID уже существует. Введите другой ID.");
                return;
            }
        }

        if (card.isEmpty()) {
            card = "";
        }

        User user;
        user.login = login;
        user.password = password;
        user.role = role;
        user.card = card;
        user.abonementUntil = QDate();
        user.groupLeft = 0;
        user.personalLeft = 0;
        user.spent = 0.0;

        if (!store.addUser(user)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать пользователя.");
            return;
        }

        currentUser = store.user(login);
        QMessageBox::information(this, "Готово", "Аккаунт создан. Сейчас откроется личный кабинет.");
        showDashboard();
    });

    setCentralWidget(page);
}

void MainWindow::showDashboard()
{
    QWidget *page = new QWidget;
    QVBoxLayout *root = new QVBoxLayout(page);
    root->setContentsMargins(16, 16, 16, 16);

    QHBoxLayout *header = new QHBoxLayout;
    QPushButton *logoutButton = new QPushButton("Выйти");
    header->addStretch();
    header->addWidget(logoutButton);

    root->addLayout(header);

    if (currentUser.role == "Администратор") {
        root->addWidget(buildAdminTabs());
    } else if (currentUser.role == "Тренер") {
        root->addWidget(buildTrainerTabs());
    } else {
        root->addWidget(buildClientTabs());
    }

    connect(logoutButton, &QPushButton::clicked, this, [=]() {
        currentUser = User();
        showAuthPage();
    });

    setCentralWidget(page);
}

QWidget *MainWindow::buildAdminTabs()
{
    QTabWidget *tabs = new QTabWidget;

    // -------- Фиксация посещений --------
    QWidget *visitsTab = new QWidget;
    QVBoxLayout *visitsLayout = new QVBoxLayout(visitsTab);

    QGroupBox *visitBox = new QGroupBox("Фиксация посещения клиента");
    QFormLayout *visitForm = new QFormLayout(visitBox);
    QComboBox *clientCombo = new QComboBox;
    clientCombo->addItems(clientsOrPlaceholder());

    QComboBox *scheduledCombo = new QComboBox;
    // Чекбокс удалён
    QLineEdit *commentEdit = new QLineEdit;
    commentEdit->setPlaceholderText("комментарий администратора");
    QPushButton *addVisitButton = new QPushButton("Зафиксировать посещение");

    visitForm->addRow("Клиент:", clientCombo);
    visitForm->addRow("Запланированное занятие:", scheduledCombo);
    visitForm->addRow("Комментарий:", commentEdit);
    visitForm->addRow(addVisitButton);

    QTableWidget *visitsTable = makeTable(QStringList() << "Дата и время" << "Клиент" << "Тип" << "Списание" << "Комментарий");
    fillVisitsTable(visitsTable);

    auto updateScheduledTrainings = [=]() {
        scheduledCombo->clear();
        QString client = selectedRealValue(clientCombo);
        if (client.isEmpty()) {
            scheduledCombo->addItem("Нет выбранного клиента");
            return;
        }

        QDateTime now = QDateTime::currentDateTime();
        QVector<QJsonObject> futureTrainings;
        for (const QJsonObject &obj : store.trainings()) {
            if (obj["client"].toString() != client) continue;
            QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
            if (dt >= now) {
                futureTrainings.append(obj);
            }
        }

        if (futureTrainings.isEmpty()) {
            scheduledCombo->addItem("Нет запланированных занятий");
            return;
        }

        std::sort(futureTrainings.begin(), futureTrainings.end(),
                  [](const QJsonObject &a, const QJsonObject &b) {
                      return QDateTime::fromString(a["dateTime"].toString(), Qt::ISODate) <
                             QDateTime::fromString(b["dateTime"].toString(), Qt::ISODate);
                  });

        for (const QJsonObject &obj : futureTrainings) {
            QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
            QString display = QString("%1 | %2 | %3 | тренер: %4")
                                  .arg(dt.toString("dd.MM.yyyy HH:mm"))
                                  .arg(obj["type"].toString())
                                  .arg(obj["className"].toString())
                                  .arg(obj["trainer"].toString());
            scheduledCombo->addItem(display, obj);
        }
    };

    connect(clientCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, updateScheduledTrainings);
    updateScheduledTrainings();

    connect(addVisitButton, &QPushButton::clicked, this, [=]() {
        QString client = selectedRealValue(clientCombo);
        if (client.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Выберите клиента.");
            return;
        }
        if (scheduledCombo->currentText().startsWith("Нет") || scheduledCombo->count() == 0) {
            QMessageBox::warning(this, "Ошибка", "Нет запланированных занятий для этого клиента.");
            return;
        }
        QJsonObject selectedTraining = scheduledCombo->currentData().toJsonObject();
        if (selectedTraining.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Выберите занятие из списка.");
            return;
        }
        QString type = selectedTraining["type"].toString();
        QString className = selectedTraining["className"].toString();
        QDateTime dt = QDateTime::fromString(selectedTraining["dateTime"].toString(), Qt::ISODate);
        QString trainer = selectedTraining["trainer"].toString();

        double price = getLessonPrice(className, type);
        store.addVisit(client, type, className, false, price, commentEdit->text().trimmed());
        store.removeTraining(client, dt, trainer, type, className);

        fillVisitsTable(visitsTable);
        updateScheduledTrainings();
        commentEdit->clear();
    });

    QHBoxLayout *visitsButtonLayout = new QHBoxLayout;
    visitsButtonLayout->addStretch();
    QPushButton *deleteVisitButton = new QPushButton("Удалить выбранное посещение");
    deleteVisitButton->setStyleSheet("QPushButton { color: red; }");
    connect(deleteVisitButton, &QPushButton::clicked, this, [=]() {
        int row = visitsTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.");
            return;
        }
        if (store.deleteVisit(row)) {
            fillVisitsTable(visitsTable);
            QMessageBox::information(this, "Успех", "Запись посещения удалена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись.");
        }
    });
    visitsButtonLayout->addWidget(deleteVisitButton);

    visitsLayout->addWidget(visitBox);
    visitsLayout->addWidget(visitsTable);
    visitsLayout->addLayout(visitsButtonLayout);
    tabs->addTab(visitsTab, "Фиксация посещений");

    // -------- Аналитика и отчёт --------
    QWidget *analyticsTab = new QWidget;
    QVBoxLayout *analyticsLayout = new QVBoxLayout(analyticsTab);
    QGroupBox *statBox = new QGroupBox("Показатели зала");
    QFormLayout *statForm = new QFormLayout(statBox);
    QLabel *revenueLabel = new QLabel;
    QLabel *visitsLabel = new QLabel;
    QLabel *popularLabel = new QLabel;
    QLabel *churnLabel = new QLabel;
    QPushButton *refreshAnalyticsButton = new QPushButton("Обновить отчёт");
    statForm->addRow("Выручка:", revenueLabel);
    statForm->addRow("Общее посещение:", visitsLabel);
    statForm->addRow("Популярность занятий:", popularLabel);
    statForm->addRow("Отток клиентов:", churnLabel);
    statForm->addRow(refreshAnalyticsButton);

    // Переименован столбец "Абонемент" -> "Услуга"
    QTableWidget *purchaseTable = makeTable(QStringList() << "Дата" << "Клиент" << "Услуга" << "Цена");
    fillPurchaseTable(purchaseTable);
    updateAnalyticsLabels(revenueLabel, visitsLabel, popularLabel, churnLabel);

    connect(refreshAnalyticsButton, &QPushButton::clicked, this, [=]() {
        updateAnalyticsLabels(revenueLabel, visitsLabel, popularLabel, churnLabel);
        fillPurchaseTable(purchaseTable);
    });

    QHBoxLayout *purchasesButtonLayout = new QHBoxLayout;
    purchasesButtonLayout->addStretch();
    QPushButton *deletePurchaseButton = new QPushButton("Удалить выбранную покупку");
    deletePurchaseButton->setStyleSheet("QPushButton { color: red; }");
    connect(deletePurchaseButton, &QPushButton::clicked, this, [=]() {
        int row = purchaseTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.");
            return;
        }
        if (store.deletePurchase(row)) {
            fillPurchaseTable(purchaseTable);
            updateAnalyticsLabels(revenueLabel, visitsLabel, popularLabel, churnLabel);
            QMessageBox::information(this, "Успех", "Запись покупки удалена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись.");
        }
    });
    purchasesButtonLayout->addWidget(deletePurchaseButton);

    analyticsLayout->addWidget(statBox);
    analyticsLayout->addWidget(new QLabel("История покупок:"));
    analyticsLayout->addWidget(purchaseTable);
    analyticsLayout->addLayout(purchasesButtonLayout);
    tabs->addTab(analyticsTab, "Аналитика и отчёт");

    // -------- Контроль доступа --------
    QWidget *accessTab = new QWidget;
    QVBoxLayout *accessLayout = new QVBoxLayout(accessTab);
    QGroupBox *accessBox = new QGroupBox("Поиск по ID");
    QFormLayout *accessForm = new QFormLayout(accessBox);
    QLineEdit *cardInput = new QLineEdit;
    cardInput->setPlaceholderText("введите логин клиента или ID");
    QPushButton *checkButton = new QPushButton("Проверить доступ");
    QLabel *accessResult = new QLabel("Ожидание проверки...");
    accessResult->setWordWrap(true);
    accessForm->addRow("ID:", cardInput);
    accessForm->addRow(checkButton);
    accessForm->addRow("Результат:", accessResult);

    QTableWidget *clientsTable = makeTable(QStringList() << "Клиент" << "ID" << "Абонемент до");
    QPushButton *deleteUserButton = new QPushButton("Удалить выбранного клиента");
    deleteUserButton->setStyleSheet("QPushButton { color: red; }");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(deleteUserButton);
    accessLayout->addWidget(accessBox);
    accessLayout->addWidget(new QLabel("Клиенты и срок действия абонемента:"));
    accessLayout->addWidget(clientsTable);
    accessLayout->addLayout(buttonLayout);

    auto refreshClientsTable = [=]() {
        clientsTable->setRowCount(store.users().size());
        int row = 0;
        for (const User &u : store.users()) {
            if (u.role != "Клиент") continue;
            clientsTable->setItem(row, 0, item(u.login));
            clientsTable->setItem(row, 1, item(u.card.isEmpty() ? "нет" : u.card));
            clientsTable->setItem(row, 2, item(u.abonementUntil.isValid() ? u.abonementUntil.toString("dd.MM.yyyy") : "нет"));
            ++row;
        }
        clientsTable->setRowCount(row);
    };
    refreshClientsTable();

    connect(checkButton, &QPushButton::clicked, this, [=]() {
        const QString code = cardInput->text().trimmed();
        if (code.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите ID или логин клиента.");
            return;
        }
        User found;
        for (const User &u : store.users()) {
            if (u.role == "Клиент" &&
                (u.login.compare(code, Qt::CaseInsensitive) == 0 || u.card.compare(code, Qt::CaseInsensitive) == 0)) {
                found = u;
                break;
            }
        }
        if (found.login.isEmpty()) {
            accessResult->setText("Доступ запрещён: клиент не найден.");
            return;
        }

        const QDate today = QDate::currentDate();
        bool abonementValid = found.abonementUntil.isValid() && found.abonementUntil >= today;
        bool hasFutureTrainings = false;
        QDateTime now = QDateTime::currentDateTime();
        for (const QJsonObject &obj : store.trainings()) {
            if (obj["client"].toString() == found.login) {
                QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
                if (dt >= now) {
                    hasFutureTrainings = true;
                    break;
                }
            }
        }

        if (abonementValid || hasFutureTrainings) {
            QString reason;
            if (abonementValid && hasFutureTrainings)
                reason = "Абонемент активен и есть запланированные занятия.";
            else if (abonementValid)
                reason = "Абонемент активен.";
            else
                reason = "Есть запланированные занятия.";

            accessResult->setText(QString("Доступ разрешён. Клиент: %1. Время входа: %2. %3")
                                  .arg(found.login,
                                       QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"),
                                       reason));
            store.addVisit(found.login, "Поиск по ID", "", false, 0.0, "контроль доступа");
            fillVisitsTable(visitsTable);
        } else {
            accessResult->setText(QString("Доступ запрещён. Клиент: %1. Нет активного абонемента и нет запланированных занятий.").arg(found.login));
        }
    });

    connect(deleteUserButton, &QPushButton::clicked, this, [=]() {
        int currentRow = clientsTable->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите клиента для удаления.");
            return;
        }
        QString loginToDelete = clientsTable->item(currentRow, 0)->text();
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтверждение",
            QString("Удалить клиента '%1'?").arg(loginToDelete),
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (store.deleteUser(loginToDelete)) {
                QMessageBox::information(this, "Успех", "Клиент удалён.");
                refreshClientsTable();
                fillVisitsTable(visitsTable);
                fillPurchaseTable(purchaseTable);
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить клиента.");
            }
        }
    });

    tabs->addTab(accessTab, "Контроль доступа");
    return tabs;
}

QWidget *MainWindow::buildTrainerTabs()
{
    QTabWidget *tabs = new QTabWidget;

    // 1. График тренировок
    QWidget *scheduleTab = new QWidget;
    QVBoxLayout *scheduleLayout = new QVBoxLayout(scheduleTab);
    QGroupBox *addBox = new QGroupBox("Добавить тренировку в график");
    QFormLayout *addForm = new QFormLayout(addBox);

    QComboBox *clientCombo = new QComboBox;
    clientCombo->addItems(clientsOrPlaceholder());
    QComboBox *typeCombo = new QComboBox;
    typeCombo->addItems(QStringList() << "Групповая тренировка" << "Персональная тренировка");

    QComboBox *classCombo = new QComboBox;
    QStringList classNames = {"Йога", "Силовая", "Кардио", "Бокс", "Растяжка", "Функциональная"};

    auto fillClassCombo = [=]() {
        QString type = typeCombo->currentText();
        classCombo->clear();
        for (const QString &cn : classNames) {
            double price = getLessonPrice(cn, type);
            QString display = (price > 0) ? QString("%1 (%2 ₽)").arg(cn).arg(price) : cn;
            classCombo->addItem(display, cn);
        }
    };
    fillClassCombo();
    connect(typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, fillClassCombo);

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addDays(1));
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setDisplayFormat("dd.MM.yyyy HH:mm");
    QLineEdit *noteEdit = new QLineEdit;
    QPushButton *addTrainingButton = new QPushButton("Добавить тренировку");

    addForm->addRow("Клиент:", clientCombo);
    addForm->addRow("Тип:", typeCombo);
    addForm->addRow("Занятие:", classCombo);
    addForm->addRow("Дата и время:", dateTimeEdit);
    addForm->addRow("Заметка:", noteEdit);
    addForm->addRow(addTrainingButton);

    QTableWidget *scheduleTable = makeTable(QStringList() << "Дата" << "Клиент" << "Тренер" << "Тип" << "Занятие" << "Заметка" << "Цена");
    fillTrainingsTable(scheduleTable, true, false);

    connect(addTrainingButton, &QPushButton::clicked, this, [=]() {
        const QString client = selectedRealValue(clientCombo);
        if (client.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Сначала зарегистрируйте клиента.");
            return;
        }
        QString type = typeCombo->currentText();
        QString className = classCombo->currentData().toString();
        QDateTime dt = dateTimeEdit->dateTime();

        if (store.isTrainerBusy(currentUser.login, dt)) {
            QDateTime nextSlot = store.getNextAvailableSlot(currentUser.login, dt);
            QString msg = QString("Тренер уже занят в это время.\nБлижайшее доступное время: %1")
                             .arg(nextSlot.toString("dd.MM.yyyy HH:mm"));
            QMessageBox::warning(this, "Ошибка", msg);
            return;
        }

        store.addTraining(client, currentUser.login, type, className, dt, noteEdit->text().trimmed());
        noteEdit->clear();
        fillTrainingsTable(scheduleTable, true, false);
        QMessageBox::information(this, "Успех", "Тренировка добавлена в график.");
    });

    scheduleLayout->addWidget(addBox);
    scheduleLayout->addWidget(scheduleTable);
    tabs->addTab(scheduleTab, "График тренировок");

    // 2. Зал и оборудование
    QWidget *equipmentTab = new QWidget;
    QVBoxLayout *equipmentLayout = new QVBoxLayout(equipmentTab);

    QTableWidget *equipmentTable = makeTable(QStringList() << "Название" << "Зал" << "Статус");
    equipmentTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    equipmentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ComboBoxDelegate *hallDelegate = new ComboBoxDelegate({"Основной зал", "Малый зал"}, this);
    ComboBoxDelegate *statusDelegate = new ComboBoxDelegate({"Доступно", "В ремонте"}, this);
    equipmentTable->setItemDelegateForColumn(1, hallDelegate);
    equipmentTable->setItemDelegateForColumn(2, statusDelegate);

    auto refreshEquipmentTable = [=]() {
        equipmentTable->blockSignals(true);
        QVector<Equipment> eqList = store.equipmentList();
        QVector<Equipment> sorted;
        for (const Equipment &eq : eqList) {
            if (eq.hall == "Основной зал") sorted.append(eq);
        }
        std::sort(sorted.begin(), sorted.end(), [](const Equipment &a, const Equipment &b) {
            return a.name < b.name;
        });
        int mainCount = sorted.size();
        for (const Equipment &eq : eqList) {
            if (eq.hall == "Малый зал") sorted.append(eq);
        }
        std::sort(sorted.begin() + mainCount, sorted.end(), [](const Equipment &a, const Equipment &b) {
            return a.name < b.name;
        });

        equipmentTable->setRowCount(sorted.size());
        for (int i = 0; i < sorted.size(); ++i) {
            equipmentTable->setItem(i, 0, item(sorted[i].name));
            equipmentTable->setItem(i, 1, item(sorted[i].hall));
            equipmentTable->setItem(i, 2, item(sorted[i].status));
        }
        equipmentTable->blockSignals(false);
    };
    refreshEquipmentTable();

    connect(equipmentTable, &QTableWidget::cellChanged, this, [=](int row, int column) {
        if (column == 0) return;
        QString name = equipmentTable->item(row, 0)->text();
        QVector<Equipment> eqList = store.equipmentList();
        int realIndex = -1;
        for (int i = 0; i < eqList.size(); ++i) {
            if (eqList[i].name == name) {
                realIndex = i;
                break;
            }
        }
        if (realIndex == -1) return;

        Equipment eq = eqList[realIndex];
        if (column == 1) {
            eq.hall = equipmentTable->item(row, column)->text();
        } else if (column == 2) {
            eq.status = equipmentTable->item(row, column)->text();
        }
        if (store.updateEquipment(realIndex, eq)) {
            refreshEquipmentTable();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить изменения.");
            refreshEquipmentTable();
        }
    });

    QGroupBox *addEquipBox = new QGroupBox("Добавить оборудование");
    QFormLayout *addEquipForm = new QFormLayout(addEquipBox);
    QLineEdit *equipNameEdit = new QLineEdit;
    QComboBox *hallCombo = new QComboBox;
    hallCombo->addItems({"Основной зал", "Малый зал"});
    QComboBox *statusCombo = new QComboBox;
    statusCombo->addItems({"Доступно", "В ремонте"});
    QPushButton *addEquipButton = new QPushButton("Добавить");

    addEquipForm->addRow("Название:", equipNameEdit);
    addEquipForm->addRow("Зал:", hallCombo);
    addEquipForm->addRow("Статус:", statusCombo);
    addEquipForm->addRow(addEquipButton);

    QHBoxLayout *equipButtonLayout = new QHBoxLayout;
    equipButtonLayout->addStretch();
    QPushButton *deleteEquipButton = new QPushButton("Удалить выбранное оборудование");
    deleteEquipButton->setStyleSheet("QPushButton { color: red; }");

    connect(addEquipButton, &QPushButton::clicked, this, [=]() {
        QString name = equipNameEdit->text().trimmed();
        if (name.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите название тренажёра.");
            return;
        }
        Equipment newEq{name, hallCombo->currentText(), statusCombo->currentText()};
        if (store.addEquipment(newEq)) {
            refreshEquipmentTable();
            equipNameEdit->clear();
            QMessageBox::information(this, "Успех", "Оборудование добавлено.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить оборудование.");
        }
    });

    connect(deleteEquipButton, &QPushButton::clicked, this, [=]() {
        int row = equipmentTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.");
            return;
        }
        QString name = equipmentTable->item(row, 0)->text();
        QVector<Equipment> eqList = store.equipmentList();
        int realIndex = -1;
        for (int i = 0; i < eqList.size(); ++i) {
            if (eqList[i].name == name) {
                realIndex = i;
                break;
            }
        }
        if (realIndex >= 0 && store.removeEquipment(realIndex)) {
            refreshEquipmentTable();
            QMessageBox::information(this, "Успех", "Оборудование удалено.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить оборудование.");
        }
    });
    equipButtonLayout->addWidget(deleteEquipButton);

    equipmentLayout->addWidget(equipmentTable);
    equipmentLayout->addWidget(addEquipBox);
    equipmentLayout->addLayout(equipButtonLayout);
    tabs->addTab(equipmentTab, "Зал и оборудование");

    return tabs;
}

QWidget *MainWindow::buildClientTabs()
{
    QTabWidget *tabs = new QTabWidget;

    // -------- Покупка абонемента --------
    QWidget *purchaseTab = new QWidget;
    QVBoxLayout *purchaseLayout = new QVBoxLayout(purchaseTab);
    QLabel *clientInfo = new QLabel;
    clientInfo->setWordWrap(true);
    updateClientInfoLabel(clientInfo, currentUser.login);

    QGroupBox *planBox = new QGroupBox("Покупка / продление абонемента");
    QFormLayout *planForm = new QFormLayout(planBox);
    QComboBox *planCombo = new QComboBox;
    planCombo->addItem("1 месяц — 1500 ₽", QVariantList() << QVariant(1500.0) << QVariant(0) << QVariant(0) << QVariant(1));
    planCombo->addItem("3 месяца — 5000 ₽", QVariantList() << QVariant(5000.0) << QVariant(0) << QVariant(0) << QVariant(3));
    planCombo->addItem("6 месяцев — 8500 ₽", QVariantList() << QVariant(8500.0) << QVariant(0) << QVariant(0) << QVariant(6));
    planCombo->addItem("12 месяцев — 11000 ₽", QVariantList() << QVariant(11000.0) << QVariant(0) << QVariant(0) << QVariant(12));
    QPushButton *buyButton = new QPushButton("Купить / продлить");
    planForm->addRow("Тариф:", planCombo);
    planForm->addRow(buyButton);

    // Переименован столбец "Абонемент" -> "Услуга"
    QTableWidget *myPurchasesTable = makeTable(QStringList() << "Дата" << "Клиент" << "Услуга" << "Цена");
    fillPurchaseTable(myPurchasesTable, currentUser.login);

    connect(buyButton, &QPushButton::clicked, this, [=]() {
        const QVariantList data = planCombo->currentData().toList();
        const double price = data.value(0).toDouble();
        const int monthsAdd = data.value(3).toInt();
        store.addPurchase(currentUser.login, planCombo->currentText(), price, 0, 0, monthsAdd);
        currentUser = store.user(currentUser.login);
        updateClientInfoLabel(clientInfo, currentUser.login);
        fillPurchaseTable(myPurchasesTable, currentUser.login);
        QMessageBox::information(this, "Покупка", "Абонемент обновлён. Данные сохранены оффлайн.");
    });

    QHBoxLayout *purchasesButtonLayout = new QHBoxLayout;
    purchasesButtonLayout->addStretch();
    QPushButton *deleteMyPurchaseButton = new QPushButton("Удалить выбранную покупку");
    deleteMyPurchaseButton->setStyleSheet("QPushButton { color: red; }");
    connect(deleteMyPurchaseButton, &QPushButton::clicked, this, [=]() {
        int row = myPurchasesTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.");
            return;
        }
        const QVector<QJsonObject> allPurchases = store.purchases();
        int globalIndex = -1;
        int filteredIndex = 0;
        for (int i = 0; i < allPurchases.size(); ++i) {
            if (allPurchases[i]["client"].toString() == currentUser.login) {
                if (filteredIndex == row) {
                    globalIndex = i;
                    break;
                }
                ++filteredIndex;
            }
        }
        if (globalIndex >= 0 && store.deletePurchase(globalIndex)) {
            fillPurchaseTable(myPurchasesTable, currentUser.login);
            currentUser = store.user(currentUser.login);
            updateClientInfoLabel(clientInfo, currentUser.login);
            QMessageBox::information(this, "Успех", "Запись покупки удалена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись.");
        }
    });
    purchasesButtonLayout->addWidget(deleteMyPurchaseButton);

    purchaseLayout->addWidget(clientInfo);
    purchaseLayout->addWidget(planBox);
    purchaseLayout->addWidget(new QLabel("Мои покупки:"));
    purchaseLayout->addWidget(myPurchasesTable);
    purchaseLayout->addLayout(purchasesButtonLayout);
    tabs->addTab(purchaseTab, "Покупка абонемента");

    // -------- Запись на тренировку --------
    QWidget *bookingTab = new QWidget;
    QVBoxLayout *bookingLayout = new QVBoxLayout(bookingTab);
    QGroupBox *bookingBox = new QGroupBox("Запись на тренировку");
    QFormLayout *bookingForm = new QFormLayout(bookingBox);

    QComboBox *bookingTypeCombo = new QComboBox;
    bookingTypeCombo->addItems(QStringList() << "Групповое занятие" << "Персональное занятие");

    QComboBox *classCombo = new QComboBox;
    QStringList classNames = {"Йога", "Силовая", "Кардио", "Бокс", "Растяжка", "Функциональная"};

    auto fillClassCombo = [=]() {
        QString type = bookingTypeCombo->currentText();
        classCombo->clear();
        for (const QString &cn : classNames) {
            classCombo->addItem(getLessonDisplayString(cn, type), cn);
        }
    };
    fillClassCombo();
    connect(bookingTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, fillClassCombo);

    QComboBox *trainerCombo = new QComboBox;
    trainerCombo->addItems(trainersOrPlaceholder());
    QDateTimeEdit *bookingDateEdit = new QDateTimeEdit(QDateTime::currentDateTime().addDays(1));
    bookingDateEdit->setCalendarPopup(true);
    bookingDateEdit->setDisplayFormat("dd.MM.yyyy HH:mm");
    QPushButton *bookButton = new QPushButton("Записаться");

    bookingForm->addRow("Тип:", bookingTypeCombo);
    bookingForm->addRow("Занятие:", classCombo);
    bookingForm->addRow("Тренер:", trainerCombo);
    bookingForm->addRow("Дата и время:", bookingDateEdit);
    bookingForm->addRow(bookButton);

    QTableWidget *myScheduleTable = makeTable(QStringList() << "Дата" << "Клиент" << "Тренер" << "Тип" << "Занятие" << "Заметка" << "Цена");
    fillTrainingsTable(myScheduleTable, false, true);

    connect(bookButton, &QPushButton::clicked, this, [=]() {
        const QString trainer = selectedRealValue(trainerCombo);
        if (trainer.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Сначала зарегистрируйте тренера.");
            return;
        }
        QString type = bookingTypeCombo->currentText();
        QString className = classCombo->currentData().toString();
        QString trainingType = (type == "Групповое занятие") ? "Групповая тренировка" : "Персональная тренировка";
        QDateTime dt = bookingDateEdit->dateTime();

        if (store.isTrainerBusy(trainer, dt)) {
            QDateTime nextSlot = store.getNextAvailableSlot(trainer, dt);
            QString msg = QString("Тренер уже занят в это время.\nБлижайшее доступное время: %1")
                             .arg(nextSlot.toString("dd.MM.yyyy HH:mm"));
            QMessageBox::warning(this, "Ошибка", msg);
            return;
        }

        store.addTraining(currentUser.login, trainer, trainingType, className, dt, "запись клиента");
        fillTrainingsTable(myScheduleTable, false, true);
        QMessageBox::information(this, "Запись", QString("Вы записаны на тренировку.\nОплата будет списана при посещении."));
    });

    // ---- Кнопка переноса тренировки ----
    QHBoxLayout *transferLayout = new QHBoxLayout;
    transferLayout->addStretch();
    QPushButton *transferButton = new QPushButton("Перенести выбранную тренировку");
    transferButton->setStyleSheet("QPushButton { color: blue; }");
    transferLayout->addWidget(transferButton);

    connect(transferButton, &QPushButton::clicked, this, [=]() {
        int row = myScheduleTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите тренировку для переноса.");
            return;
        }
        QDateTime oldDateTime = QDateTime::fromString(myScheduleTable->item(row, 0)->text(), "dd.MM.yyyy HH:mm");
        QString trainer = myScheduleTable->item(row, 2)->text();
        QString type = myScheduleTable->item(row, 3)->text();
        QString className = myScheduleTable->item(row, 4)->text();

        QDialog dialog(this);
        dialog.setWindowTitle("Перенос тренировки");
        QVBoxLayout *dlgLayout = new QVBoxLayout(&dialog);
        QFormLayout *form = new QFormLayout;
        QDateTimeEdit *newDateTimeEdit = new QDateTimeEdit(oldDateTime.addDays(1));
        newDateTimeEdit->setCalendarPopup(true);
        newDateTimeEdit->setDisplayFormat("dd.MM.yyyy HH:mm");
        newDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
        form->addRow("Новая дата и время:", newDateTimeEdit);
        QLabel *infoLabel = new QLabel;
        infoLabel->setWordWrap(true);
        infoLabel->setStyleSheet("color: gray;");
        form->addRow(infoLabel);
        dlgLayout->addLayout(form);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        dlgLayout->addWidget(buttonBox);
        connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        auto checkBusy = [=]() {
            QDateTime newDt = newDateTimeEdit->dateTime();
            if (store.isTrainerBusyExcept(trainer, newDt, currentUser.login, oldDateTime)) {
                infoLabel->setText("❌ Это время уже занято у тренера. Выберите другое.");
                return false;
            }
            infoLabel->setText("✅ Тренер свободен в это время.");
            return true;
        };
        connect(newDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](){ checkBusy(); });
        checkBusy();

        if (dialog.exec() == QDialog::Accepted) {
            QDateTime newDateTime = newDateTimeEdit->dateTime();
            if (store.isTrainerBusyExcept(trainer, newDateTime, currentUser.login, oldDateTime)) {
                QDateTime nextSlot = store.getNextAvailableSlot(trainer, newDateTime);
                QString msg = QString("Тренер занят в выбранное время.\nБлижайшее доступное время: %1")
                                 .arg(nextSlot.toString("dd.MM.yyyy HH:mm"));
                QMessageBox::warning(this, "Ошибка", msg);
                return;
            }
            if (store.updateTrainingDateTime(currentUser.login, oldDateTime, newDateTime, trainer, type, className)) {
                fillTrainingsTable(myScheduleTable, false, true);
                QMessageBox::information(this, "Успех", "Тренировка перенесена.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось перенести тренировку (запись не найдена).");
            }
        }
    });

    bookingLayout->addWidget(bookingBox);
    bookingLayout->addWidget(new QLabel("Мои записи:"));
    bookingLayout->addWidget(myScheduleTable);
    bookingLayout->addLayout(transferLayout);
    tabs->addTab(bookingTab, "Записаться на тренировку");

    return tabs;
}

void MainWindow::fillVisitsTable(QTableWidget *table)
{
    const QVector<QJsonObject> data = store.visits();
    table->setRowCount(data.size());
    for (int i = 0; i < data.size(); ++i) {
        const QJsonObject obj = data[i];
        const QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        table->setItem(i, 0, item(dt.isValid() ? dt.toString("dd.MM.yyyy HH:mm:ss") : obj["dateTime"].toString()));
        table->setItem(i, 1, item(obj["client"].toString()));
        table->setItem(i, 2, item(obj["type"].toString()));
        table->setItem(i, 3, item(obj["writeOff"].toString()));
        table->setItem(i, 4, item(obj["comment"].toString()));
    }
}

void MainWindow::fillTrainingsTable(QTableWidget *table, bool onlyCurrentTrainer, bool onlyCurrentClient)
{
    QVector<QJsonObject> filtered;
    for (const QJsonObject &obj : store.trainings()) {
        if (onlyCurrentTrainer && obj["trainer"].toString() != currentUser.login) continue;
        if (onlyCurrentClient && obj["client"].toString() != currentUser.login) continue;
        filtered.append(obj);
    }

    table->setRowCount(filtered.size());
    for (int i = 0; i < filtered.size(); ++i) {
        const QJsonObject obj = filtered[i];
        const QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        const QString className = obj["className"].toString();
        const QString type = obj["type"].toString();
        double price = getLessonPrice(className, type);
        QString priceStr = (price > 0) ? QString::number(price, 'f', 2) + " ₽" : "не указана";

        table->setItem(i, 0, item(dt.isValid() ? dt.toString("dd.MM.yyyy HH:mm") : obj["dateTime"].toString()));
        table->setItem(i, 1, item(obj["client"].toString()));
        table->setItem(i, 2, item(obj["trainer"].toString()));
        table->setItem(i, 3, item(obj["type"].toString()));
        table->setItem(i, 4, item(className));
        table->setItem(i, 5, item(obj["note"].toString()));
        table->setItem(i, 6, item(priceStr));
    }
}

void MainWindow::fillCoachNotesList(QListWidget *list, const QString &filterKind)
{
    list->clear();
    for (const QJsonObject &obj : store.coachNotes()) {
        if (obj["trainer"].toString() != currentUser.login) continue;
        if (!filterKind.isEmpty() && obj["kind"].toString() != filterKind) continue;
        const QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        const QString line = QString("%1 | %2 | клиент: %3 | %4")
                .arg(dt.isValid() ? dt.toString("dd.MM.yyyy HH:mm") : obj["dateTime"].toString(),
                     obj["kind"].toString(),
                     obj["client"].toString(),
                     obj["text"].toString());
        list->addItem(line);
    }
    if (list->count() == 0) list->addItem("Записей пока нет.");
}

void MainWindow::fillPurchaseTable(QTableWidget *table, const QString &clientFilter)
{
    QVector<QJsonObject> filtered;
    for (const QJsonObject &obj : store.purchases()) {
        if (!clientFilter.isEmpty() && obj["client"].toString() != clientFilter) continue;
        filtered.append(obj);
    }

    table->setRowCount(filtered.size());
    for (int i = 0; i < filtered.size(); ++i) {
        const QJsonObject obj = filtered[i];
        const QDateTime dt = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
        table->setItem(i, 0, item(dt.isValid() ? dt.toString("dd.MM.yyyy HH:mm") : obj["dateTime"].toString()));
        table->setItem(i, 1, item(obj["client"].toString()));
        table->setItem(i, 2, item(obj["name"].toString()));
        table->setItem(i, 3, item(QString::number(obj["price"].toDouble(), 'f', 2) + " ₽"));
    }
}

void MainWindow::updateClientInfoLabel(QLabel *label, const QString &clientLogin)
{
    const User u = store.user(clientLogin);
    const QString until = u.abonementUntil.isValid() ? u.abonementUntil.toString("dd.MM.yyyy") : "абонемент не куплен";
    label->setText(QString("Клиент: %1\nАбонемент действует до: %2\nОстаток групповых занятий: %3\nОстаток персональных занятий: %4")
                   .arg(u.login, until, QString::number(u.groupLeft), QString::number(u.personalLeft)));
}

void MainWindow::updateAnalyticsLabels(QLabel *revenueLabel, QLabel *visitsLabel, QLabel *popularLabel, QLabel *churnLabel)
{
    revenueLabel->setText(QString::number(store.totalRevenue(), 'f', 2) + " ₽");
    visitsLabel->setText(QString::number(store.totalVisits()));
    popularLabel->setText(store.popularTrainingText());
    churnLabel->setText(QString("%1 клиентов с истёкшим абонементом").arg(store.churnClients()));
}

QStringList MainWindow::clientsOrPlaceholder() const
{
    QStringList clients = store.clients();
    if (clients.isEmpty()) clients << "Нет зарегистрированных клиентов";
    return clients;
}

QStringList MainWindow::trainersOrPlaceholder() const
{
    QStringList trainers = store.trainers();
    if (trainers.isEmpty()) trainers << "Нет зарегистрированных тренеров";
    return trainers;
}

QString MainWindow::selectedRealValue(QComboBox *combo) const
{
    const QString value = combo->currentText();
    if (value.startsWith("Нет зарегистрированных")) return QString();
    return value;
}