#ifndef ADDEDGEDIALOG_H
#define ADDEDGEDIALOG_H

#include <QDialog>

class QSpinBox;
class QComboBox;

class AddEdgeDialog : public QDialog {
    Q_OBJECT
public:
    AddEdgeDialog(int maxVertex, QWidget *parent = nullptr);
    int getFrom() const;
    int getTo() const;
    int getWeight() const;

private:
    QComboBox* fromCombo;
    QComboBox* toCombo;
    QSpinBox* weightSpin;
};

#endif // ADDEDGEDIALOG_H
