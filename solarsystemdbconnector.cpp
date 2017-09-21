#include "solarsystemdbconnector.h"
#include <QGuiApplication>
#include <Parser/solarparser.h>

//pseydo name
using SolarS = SolarSystem::SolarStrings;
using SolarV = SolarSystem::SolarValues;
using Types = SolarSystem::SolarFields;

SolarSystem::SolarSystemDBConnector::SolarSystemDBConnector(QObject* parent):
    QObject(parent),
    _database(QSqlDatabase::addDatabase(SolarS::qSqlLite))
{    
#ifdef WIN32
    if (!QFile::exists(QGuiApplication::applicationDirPath() + "/Database/SolarDB.db"))
    {
        QDir dir;
        dir.mkdir(QGuiApplication::applicationDirPath() + "/Database/");

        QFile file(":/Resources/Database/SolarDB.db");
        file.copy(QGuiApplication::applicationDirPath() + "/Database/SolarDB.db");
    }

    _database.setDatabaseName(QGuiApplication::applicationDirPath() + "/Database/SolarDB.db");
#endif

#ifdef ANDROID
    QFile file("assets:/SolarDB.db");
    file.copy("./SolarDB.db");
    QFile::setPermissions("./MyFile1",QFile::WriteOwner | QFile::ReadOwner);
    _database.setDatabaseName("./SolarDB.db");
#endif

    _database.open();
}

SolarSystem::SolarSystemDBConnector::~SolarSystemDBConnector()
{
    if (_database.isOpen())
        _database.close();
}

SolarSystem::SolarSystemDBConnector& SolarSystem::SolarSystemDBConnector::instance()
{
    static SolarSystemDBConnector connector;
    return connector;
}

bool SolarSystem::SolarSystemDBConnector::isOpen()
{
    return _database.isOpen();
}

int SolarSystem::SolarSystemDBConnector::elementsCount()
{
    QStringList list;

    if (_database.isOpen())
    {
        //make a query
        QSqlQuery query(SolarS::select + SolarS::nameField + SolarS::from + SolarS::dbName);

        while (query.next()) {
            list << query.value(SolarV::zero).toString();
        }
    }

    return list.size();
}

const SolarSystem::SolarSystemObjectPtr SolarSystem::SolarSystemDBConnector::info(const QString& objectName) const
{
    SolarSystem::SolarSystemObjectPtr object(new SolarSystem::SolarSystemObject());

    if (_database.isOpen())
    {
        //make a query
        QSqlQuery query(SolarS::select + SolarS::all + SolarS::from + SolarS::dbName + SolarS::where + SolarS::nameField +
                        SolarS::like + SolarS::likeObject(objectName));

        if (query.first())
            //collecting query data to local object
            createObjectFromQuery(query, object);
    }

    return object;
}

QStringList SolarSystem::SolarSystemDBConnector::allSolarObjects() const
{
    QStringList objectList;

    if (_database.isOpen()) {

        //make a query
        QSqlQuery query(SolarS::select + SolarS::nameField + SolarS::from + SolarS::dbName);

        while (query.next()) {
            objectList << query.value(SolarV::zero).toString();
        }

    }

    return objectList;
}

QStringList SolarSystem::SolarSystemDBConnector::allPlanetsNames() const
{
    QStringList list;

    if (_database.isOpen()) {

        //make a query
        QSqlQuery query(SolarS::select + SolarS::nameField + SolarS::from + SolarS::dbName + SolarS::where + SolarS::type +
                        SolarS::like + SolarS::likeObject(SolarStrings::planet));

        while (query.next()) {
            list << query.value(SolarV::zero).toString();
        }
    }

    return list;
}

QStringList SolarSystem::SolarSystemDBConnector::columnNames() const
{
    QStringList list;

    if (_database.isOpen())
    {
        //make a query
        QSqlQuery query("PRAGMA table_info('SolarSystem')");

        while (query.next())
            list << query.value(1).toString();
    }

    return list;
}

QStringList SolarSystem::SolarSystemDBConnector::info(SolarSystem::SolarObjects object) const
{
    auto objStr = SolarParser::parseSolarObjectToString(object);
    QStringList list;

    if (_database.isOpen())
    {
        //make a query
        QSqlQuery query("SELECT * FROM SolarSystem WHERE Name =" + SolarS::likeObject(objStr));

        //columns count
        auto size = query.record().count();

        while (query.next())
        {
            for (int i = 0; i < size; ++i)
                list << query.value(i).toString();
        }
    }

    return list;
}

void SolarSystem::SolarSystemDBConnector::createObjectFromQuery(QSqlQuery& query, SolarSystemObjectPtr& object) const
{
    object->setStringType(query.value(Types::SolarType).toString());
    object->setSolarObjectName(query.value(Types::Name).toString());
    object->setOrbitalSpeed(query.value(Types::OrbitalSpeed).toFloat());
    object->setMass(query.value(Types::Mass).toDouble());
    object->setMeanRadius(query.value(Types::MeanRadius).toFloat());
    object->setSurfaceTemperature(query.value(Types::Temperature).toInt());
    object->setSurfaceGravity(query.value(Types::Gravity).toFloat());
    object->setVolume(query.value(Types::Volume).toDouble());
    object->setSiderealPeriod(query.value(Types::SiderealPeriod).toDouble());
    object->setOrbitalPeriod(query.value(Types::OrbitalPeriod).toDouble());
    object->setDescription(query.value(Types::Description).toString());

    //programming type
    object->setSolarType(SolarParser::parseString(object->stringType()));
}
