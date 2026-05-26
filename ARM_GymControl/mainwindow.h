#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datastore.h"

#include <QMainWindow>

class QComboBox;
class QDateTimeEdit;
class QLabel;
class QLineEdit;
class QListWidget;
class QSpinBox;
class QTableWidget;
class QTextEdit;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    DataStore store;
    User currentUser;

    void showAuthPage();
    void showLoginPage();
    void showRegistrationPage();
    void showDashboard();

    QWidget *buildAdminTabs();
    QWidget *buildTrainerTabs();
    QWidget *buildClientTabs();

    void fillVisitsTable(QTableWidget *table);
    void fillTrainingsTable(QTableWidget *table, bool onlyCurrentTrainer, bool onlyCurrentClient);
    void fillCoachNotesList(QListWidget *list, const QString &filterKind = QString());
    void fillPurchaseTable(QTableWidget *table, const QString &clientFilter = QString());

    void updateClientInfoLabel(QLabel *label, const QString &clientLogin);
    void updateAnalyticsLabels(QLabel *revenueLabel, QLabel *visitsLabel, QLabel *popularLabel, QLabel *churnLabel);

    QStringList clientsOrPlaceholder() const;
    QStringList trainersOrPlaceholder() const;
    QString selectedRealValue(QComboBox *combo) const;
};

#endif // MAINWINDOW_H