#ifndef WEATHERFETCHER_H
#define WEATHERFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class WeatherFetcher : public QObject {
    Q_OBJECT

public:
    explicit WeatherFetcher(QObject *parent = nullptr);
    void fetchWeather(const QString &city);

signals:
    void weatherFetched(const QString &weather, double temp, const QString &location);

private slots:
    void onWeatherDataReceived(QNetworkReply *reply);
    QString translateWeatherDescription(const QString &englishDescription); // 添加函数声明

private:
    QNetworkAccessManager *manager;
};

#endif // WEATHERFETCHER_H
