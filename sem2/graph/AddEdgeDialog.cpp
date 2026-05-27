#include "AddEdgeDialog.h"
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QDialogButtonBox>

AddEdgeDialog::AddEdgeDialog(int maxVertex, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Добавить ребро");
    fromCombo = new QComboBox;
    toCombo = new QComboBox;
    for (int i = 0; i < maxVertex; ++i) {
        fromCombo->addItem(QString::number(i + 1), i);
        toCombo->addItem(QString::number(i + 1), i);
    }
    weightSpin = new QSpinBox;
    weightSpin->setRange(1, 9999);
    weightSpin->setValue(1);

    QFormLayout* layout = new QFormLayout;
    layout->addRow("От вершины:", fromCombo);
    layout->addRow("До вершины:", toCombo);
    layout->addRow("Вес:", weightSpin);
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttons);
    setLayout(layout);
}

int AddEdgeDialog::getFrom() const { return fromCombo->currentData().toInt(); }
int AddEdgeDialog::getTo() const { return toCombo->currentData().toInt(); }
int AddEdgeDialog::getWeight() const { return weightSpin->value(); }
