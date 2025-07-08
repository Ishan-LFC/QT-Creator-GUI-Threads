#ifndef PRIMEFINDER_H
#define PRIMEFINDER_H
#include <QWidget>
#include <QMutex>
#include <QThread>

class PrimeFinder : public QThread
{
    Q_OBJECT
public:
    PrimeFinder(int start, int end);
    void run() override;
    void stop();
signals:
    void primeFound(int prime);
    void finished();
private:
    int start_;
    int end_;
    bool isRunning_;
    QMutex mutex_;
};
#endif // PRIMEFINDER_H
