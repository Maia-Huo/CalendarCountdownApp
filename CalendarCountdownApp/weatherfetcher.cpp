#include "weatherfetcher.h"
#include <QDebug>
#include <QUrlQuery>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

WeatherFetcher::WeatherFetcher(QObject *parent)
    : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void WeatherFetcher::fetchWeather(const QString &city)
{
    QUrl url("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;
    query.addQueryItem("q", city);
    query.addQueryItem("appid", "c9d987698dc51ee050a9c60970d8f03b");  // 替换为有效的 API 密钥
    query.addQueryItem("units", "metric");       // 设置单位为摄氏度
    url.setQuery(query);

    QNetworkRequest request(url);
    connect(manager, &QNetworkAccessManager::finished, this, &WeatherFetcher::onWeatherDataReceived);
    manager->get(request);
}

void WeatherFetcher::onWeatherDataReceived(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        // 解析 JSON 响应
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = doc.object();

        QString weather = jsonObj["weather"].toArray().first().toObject()["description"].toString();
        QString translatedWeather = translateWeatherDescription(weather); // 天气转换为中文
        double temp = jsonObj["main"].toObject()["temp"].toDouble();
        QString location = jsonObj["name"].toString();  // 获取位置名称（如“北京”）

        emit weatherFetched(translatedWeather, temp, location);  // 发射信号并传递数据
    } else {
        qDebug() << "Error fetching weather data: " << reply->errorString();
    }
    reply->deleteLater();
}

// 翻译函数，将英文描述转换为中文
QString WeatherFetcher::translateWeatherDescription(const QString &englishDescription) {
    static QMap<QString, QString> weatherTranslations = {
        {"clear sky", "晴天"},
        {"few clouds", "少云"},
        {"scattered clouds", "散云"},
        {"broken clouds", "多云"},
        {"shower rain", "阵雨"},
        {"rain", "雨"},
        {"thunderstorm", "雷暴"},
        {"snow", "雪"},
        {"mist", "雾霾"}
    };

    // 如果存在对应的中文翻译，返回中文；否则返回原始英文
    return weatherTranslations.value(englishDescription.toLower(), englishDescription);
}
