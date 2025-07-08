#include "primefindergui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

PrimeFinderGui::PrimeFinderGui(QWidget* parent)
    : QWidget(parent)
{
    //Display Gui
    Gui();
}

PrimeFinderGui::~PrimeFinderGui()
{

}

void PrimeFinderGui::startFindingPrimes()
{
    int start = startInput_->text().toInt();
    int end = endInput_->text().toInt();
    int numThreads = threadsInput_->text().toInt();

    // Ensure proper number of threads
    if(numThreads > 4 || numThreads < 1)
    {
        QMessageBox::warning(this, "Error", "Number of threads must be between 1 and 4.");
        return;
    }

    // Divide the range into equal parts for the threads
    int chunkSize = (end - start) / numThreads;
    clearOutputs();

    // Clean up any existing threads
    for (auto& thread : threads_)
    {
        thread->stop();
        thread->wait();
        delete thread;
    }
    threads_.clear();

    for (int i = 0; i < numThreads; ++i)
    {
        int threadStart = start + i * chunkSize;
        int threadEnd = (i < numThreads - 1) ? threadStart + chunkSize : end;

        PrimeFinder* primeFinder = new PrimeFinder(threadStart, threadEnd);
        connect(primeFinder, &PrimeFinder::primeFound, this, [this, i](int prime)
        {
            outputTexts_[i]->append(QString::number(prime));
        });
        connect(primeFinder, &PrimeFinder::finished, this, &PrimeFinderGui::threadFinished);
        threads_.push_back(primeFinder);
        primeFinder->start();
    }
}

void PrimeFinderGui::clearOutputs()
{
    for (auto& textEdit : outputTexts_)
    {
        textEdit->clear();
    }
}

void PrimeFinderGui::closeEvent(QCloseEvent* event)
{
    for (auto& thread : threads_)
    {
        thread->stop();
    }
    for (auto& thread : threads_)
    {
        thread->wait();  // Wait for threads to finish
    }
    event->accept();

    int response;
    response = QMessageBox::warning(this, "Exit", "Are you sure you want to Exit ?", QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void PrimeFinderGui::threadFinished()
{
    bool allFinished = true;
    for (auto& thread : threads_)
    {
        if(thread->isRunning())
        {
            allFinished = false;
            break;
        }
    }
    if (allFinished)
    {
        QMessageBox::information(this, "Done", "All threads have finished processing.");
    }
}

void PrimeFinderGui::Gui()
{
    this->setWindowTitle("Prime Finder");
    this->setGeometry(100, 100, 600, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Input fields
    QHBoxLayout* inputLayout = new QHBoxLayout();

    startLabel_ = new QLabel("Start:", this);
    startInput_ = new QLineEdit(this);
    endLabel_ = new QLabel("End:", this);
    endInput_ = new QLineEdit(this);
    threadsLabel_ = new QLabel("Threads:", this);
    threadsInput_ = new QLineEdit(this);

    inputLayout->addWidget(startLabel_);
    inputLayout->addWidget(startInput_);
    inputLayout->addWidget(endLabel_);
    inputLayout->addWidget(endInput_);
    inputLayout->addWidget(threadsLabel_);
    inputLayout->addWidget(threadsInput_);

    layout->addLayout(inputLayout);

    // Start button
    startButton_ = new QPushButton("Start", this);
    connect(startButton_, &QPushButton::clicked, this, &PrimeFinderGui::startFindingPrimes);
    layout->addWidget(startButton_);

    // Output fields for each thread
    for (int i = 0; i < 4; ++i)
    {
        QTextEdit* textEdit = new QTextEdit(this);
        textEdit->setReadOnly(true);
        textEdit->setPlaceholderText(QString("Thread %1 Output").arg(i + 1));
        layout->addWidget(textEdit);
        outputTexts_.push_back(textEdit);
    }
}
