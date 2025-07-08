#ifndef PRIMEFINDERGUI_H
#define PRIMEFINDERGUI_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QCloseEvent>
#include "primefinder.h"
#include <vector>

class PrimeFinderGui : public QWidget
{
    Q_OBJECT

public:
    PrimeFinderGui(QWidget* parent = nullptr);
    ~PrimeFinderGui();
protected:
    void closeEvent(QCloseEvent* event) override;
private:
    void Gui();
    void clearOutputs();
    void startFindingPrimes();

private slots:
    void threadFinished();
private:
    QLabel* startLabel_;
    QLineEdit* startInput_;
    QLabel* endLabel_;
    QLineEdit* endInput_;
    QLabel* threadsLabel_;
    QLineEdit* threadsInput_;
    QPushButton* startButton_;
    std::vector<QTextEdit*> outputTexts_;
    std::vector<PrimeFinder*> threads_;
};

#endif // PRIMEFINDERGUI_H
