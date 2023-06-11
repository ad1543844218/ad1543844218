#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H
#include <QString>
#include <QMap>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
class WeatherTool{
public:
    static QString getCityCode(QString cityName)
    {
        if(mCityMap.isEmpty())
        {
            initCityMap();
        }
        QMap<QString,QString>::iterator it = mCityMap.find(cityName);
        if(it==mCityMap.end())
        {
            it=mCityMap.find(cityName + "市");
        }
        if(it!=mCityMap.end())
        {
            return it.value();
        }
        return "";
    }
private:
    static QMap<QString,QString> mCityMap;
    static void initCityMap()
    {
        //1.读取文件
        QString filePath = "E:/citycode.json";
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json=file.readAll();
        file.close();
//        qDebug()<<json;
        //2.解析文件，并写入map
        QJsonParseError err;
        QJsonDocument doc =QJsonDocument::fromJson(json,&err);
        if(err.error!=QJsonParseError::NoError)
        {
            return;
        }
        if(!doc.isArray())
        {
            return;
        }
        QJsonArray cities=doc.array();
        for(int i=0;i<cities.size();i++)
        {
            QString city=cities[i].toObject().value("city_name").toString();
            QString code=cities[i].toObject().value("city_code").toString();
            if(code.size()>0)
            {
                mCityMap.insert(city,code);
            }
        }
    }
};
QMap<QString,QString> WeatherTool::mCityMap={};
#endif // WEATHERTOOL_H
