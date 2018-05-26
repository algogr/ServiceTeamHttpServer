#include "datacollection.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

DataCollection::DataCollection(QObject* parent)
    :HttpRequestHandler(parent)
{

}



void DataCollection::service(HttpRequest &request, HttpResponse &response,QSqlDatabase* ldb)
{



    QString settingsFile=QCoreApplication::applicationDirPath() +"/settings.ini";
    QSettings *settings=new QSettings(settingsFile,QSettings::IniFormat);
    QString scanpath=settings->value("scanpath").toString();
    QByteArray jsonraw=request.getParameter("jsondata");
    QJsonDocument jsondoc=QJsonDocument::fromJson(jsonraw);

    qDebug()<<"JSON is an Array?"<<jsondoc.isArray();
    QJsonArray json_array=jsondoc.array();
    qDebug()<<"Array sixe:"<<json_array.size();
    QByteArray requestid;
    QByteArray uid;
    QSqlQuery qry1(*db),qry2(*db);

    for (int i=0;i<json_array.count();++i)
    {
        QJsonObject obj=json_array.at(i).toObject();
        QVariantMap map=obj.toVariantMap();
        qDebug()<<map;
        requestid=map["requestid"].toByteArray();
        uid=map["techid"].toByteArray();
        QString query="select ccctechnician from ccctechnician where username='"+uid+"'";
        qry1.exec(query);
        qry1.next();
        QString techid=qry1.value(0).toString();


        query="UPDATE findoc SET ccckatastash="+map["status"].toString()+",ccctechnician="+techid+\
                ",cccversion="+map["version"].toString()+",ccclastchangeuser="+techid+",cccischanged="+map["ischanged"].toString()+",ccclastchangeddatetime=NOW(),cccnewappointmentdate='"+map["newappointmentdate"].toString()+"' WHERE findoc="+map["mysqlid"].toString();
        qry1.exec(query);
        qDebug()<<query;
        query="INSERT INTO cccvisitdetails\
                (ticketid,imagepath,breakdownid,comments,oldserial,newserial,\
                 meas1,\
                 meas2,\
                 meas3,\
                 meas4,\
                 meas5,\
                 meas6,\
                 meas7,\
                 meas8,\
                 meas9,\
                 meas10,\
                 meas11,\
                 meas12,\
                 meas13,\
                 meas14,\
                 meas15,\
                 meas16,\
                 meas17,\
                 meas18,\
                 meas19,\
                 meas20,\
                 meas21,\
                 meas22,\
                 meas23,\
                 meas24,\
                 meas25,\
                 meas26,\
                 meas27,\
                 meas28,\
                 meas29,\
                 meas30,\
                 meas31,\
                 meas32,\
                 meas33,\
                 meas34,\
                 meas35,\
                 meas36,\
                 meas37,\
                 meas38,\
                 meas39,\
                 meas40,\
                 meas41,\
                 meas42,\
                 meas43,\
                 meas44,\
                 meas45,\
                 meas46,\
                 meas47,\
                 meas48,\
                 meas49,\
                 meas50,\
                 meas51,\
                 meas52,\
                 meas53,\
                 meas54,\
                 meas55,\
                 meas56,\
                 meas57,\
                 meas58,\
                 meas59,\
                 meas60,\
                 meas61,\
                 meas62,\
                 meas63,\
                 meas64,\
                 meas65,\
                 meas66,\
                 meas67,\
                 meas68,\
                 meas69,\
                 meas70,\
                 meas71,\
                 meas72,\
                 meas73,\
                 meas74,\
                 meas75,\
                 meas76,\
                 meas77,\
                 meas78,\
                 meas79,\
                 meas80,\
                 meas81,\
                 meas82,\
                 meas83,\
                 meas84,\
                 meas85,\
                 meas86,\
                 meas87,\
                 meas88,\
                 meas89,\
                 meas90,\
                 meas91,\
                 meas92,\
                 meas93,\
                 meas94,\
                 meas95,\
                 meas96,\
                 meas97,\
                 meas98,\
                 meas99,\
                 meas100,\
                 meas101,\
                 meas102,\
                 meas103,\
                 meas104,\
                 meas105,\
                 meas106,\
                 meas107,\
                 meas108,\
                 meas109,\
                 meas110,\
                 meas111,\
                 meas112,\
                 meas113,\
                 meas114,\
                 meas115,\
                 meas116,\
                 meas117,\
                 meas118,\
                 meas119,\
                 meas120,\
                 meas121,\
                 meas122,\
                 meas123,\
                 meas124,\
                 meas125,\
                 meas126,\
                 meas127,\
                 meas128,\
                 meas129,\
                 meas130,\
                 meas131,\
                 meas132,\
                 meas133,\
                 meas134,\
                 meas135,\
                 meas136,\
                 meas137,\
                 meas138,\
                 meas139,\
                 meas140,\
                 meas141,\
                 meas142,\
                 meas143,\
                 meas144,\
                 meas145,\
                 meas146,\
                 meas147,\
                 meas148,\
                 meas149,\
                 meas150,\
                 meas151,\
                 meas152,\
                 meas153,\
                 meas154,\
                 meas155,\
                 meas156,\
                 meas157,\
                 meas158,\
                 meas159,\
                 meas160,\
                 meas161,\
                 meas162,\
                 meas163,\
                 meas164,\
                 meas165,\
                 meas166,\
                 meas167,\
                 meas168,\
                 meas169,\
                 meas170,\
                 meas171,\
                 meas172,\
                 meas173,\
                 meas174,\
                 meas175,\
                 meas176,\
                 meas177,\
                 meas178,\
                 meas179,\
                 meas180,\
                 meas181,\
                 meas182,\
                 meas183,\
                 meas184,\
                 meas185,\
                 meas186,\
                 meas187,\
                 meas188,\
                 meas189,\
                 meas190,\
                 meas191,\
                 meas192,\
                 meas193,\
                 meas194,\
                 meas195,\
                 meas196,\
                 meas197,\
                 meas198,\
                 meas199,\
                 meas200,\
                 meas201,\
                 meas202,\
                 meas203,\
                 meas204,\
                 meas205,\
                 meas206,\
                 meas207,\
                 meas208,\
                 meas209,\
                 meas210,\
                 meas211,\
                 meas212,\
                 meas213,\
                 meas214,\
                 meas215,\
                 meas216,\
                 meas217,\
                 meas218,\
                 meas219,\
                 meas220,\
                 meas221,\
                 meas222,\
                 meas223,\
                 meas224,\
                 meas225,\
                 meas226,\
                 meas227,\
                 meas228,\
                 meas229,\
                 meas230,\
                 meas231,\
                 meas232,\
                 meas233,\
                 meas234,\
                 meas235,\
                 meas236,\
                 meas237,\
                 meas238,\
                 meas239,\
                 meas240,\
                 meas241,\
                 meas242,\
                 meas243,\
                 meas244,\
                 meas245,\
                 meas246,\
                 meas247,\
                 meas248,\
                 meas249,\
                 meas250,\
                 meas251,\
                 meas252,\
                 meas253,\
                 meas254,\
                 meas255,\
                 meas256,\
                 meas257,\
                 meas258,\
                 meas259,\
                 meas260,\
                 meas261,\
                 meas262,\
                 meas263,\
                 meas264,\
                 meas265,\
                 meas266,\
                 meas267,\
                 meas268,\
                 meas269,\
                 meas270,\
                 meas271,\
                 meas272,\
                 meas273,\
                 meas274,\
                 meas275,\
                 meas276,\
                 meas277,\
                 meas278,\
                 meas279,\
                 meas280,\
                 meas281,\
                 meas282,\
                 meas283,\
                 meas284,\
                 meas285,\
                 meas286,\
                 meas287,\
                 meas288,\
                 meas289,\
                 meas290,\
                 meas291,\
                 meas292,\
                 meas293,\
                 meas294,\
                 meas295,\
                 meas296,\
                 meas297,\
                 meas298,\
                 meas299,\
                 meas300,\
                 meas301,\
                 meas302,\
                 meas303,\
                 meas304,\
                 meas305,\
                 meas306,\
                 meas307,\
                 meas308,\
                 meas309,\
                 meas310,\
                 meas311,\
                 meas312,\
                 meas313,\
                 meas314,\
                 meas315,\
                 meas316,\
                 meas317,\
                 stoid)\
                VALUES\
                ("+map["mysqlid"].toString()+",'"+map["imagepath"].toString()+"',"+map["breakdownid"].toString()+",'"+map["comments"].toString()+"','"+\
                 map["oldserial"].toString()+"','"+map["newserial"].toString()+"','"+\
                map["meas1"].toString()+"','"+\
                map["meas2"].toString()+"','"+\
                map["meas3"].toString()+"','"+\
                map["meas4"].toString()+"','"+\
                map["meas5"].toString()+"','"+\
                map["meas6"].toString()+"','"+\
                map["meas7"].toString()+"','"+\
                map["meas8"].toString()+"','"+\
                map["meas9"].toString()+"','"+\
                map["meas10"].toString()+"','"+\
                map["meas11"].toString()+"','"+\
                map["meas12"].toString()+"','"+\
                map["meas13"].toString()+"','"+\
                map["meas14"].toString()+"','"+\
                map["meas15"].toString()+"','"+\
                map["meas16"].toString()+"','"+\
                map["meas17"].toString()+"','"+\
                map["meas18"].toString()+"','"+\
                map["meas19"].toString()+"','"+\
                map["meas20"].toString()+"','"+\
                map["meas21"].toString()+"','"+\
                map["meas22"].toString()+"','"+\
                map["meas23"].toString()+"','"+\
                map["meas24"].toString()+"','"+\
                map["meas25"].toString()+"','"+\
                map["meas26"].toString()+"','"+\
                map["meas27"].toString()+"','"+\
                map["meas28"].toString()+"','"+\
                map["meas29"].toString()+"','"+\
                map["meas30"].toString()+"','"+\
                map["meas31"].toString()+"','"+\
                map["meas32"].toString()+"','"+\
                map["meas33"].toString()+"','"+\
                map["meas34"].toString()+"','"+\
                map["meas35"].toString()+"','"+\
                map["meas36"].toString()+"','"+\
                map["meas37"].toString()+"','"+\
                map["meas38"].toString()+"','"+\
                map["meas39"].toString()+"','"+\
                map["meas40"].toString()+"','"+\
                map["meas41"].toString()+"','"+\
                map["meas42"].toString()+"','"+\
                map["meas43"].toString()+"','"+\
                map["meas44"].toString()+"','"+\
                map["meas45"].toString()+"','"+\
                map["meas46"].toString()+"','"+\
                map["meas47"].toString()+"','"+\
                map["meas48"].toString()+"','"+\
                map["meas49"].toString()+"','"+\
                map["meas50"].toString()+"','"+\
                map["meas51"].toString()+"','"+\
                map["meas52"].toString()+"','"+\
                map["meas53"].toString()+"','"+\
                map["meas54"].toString()+"','"+\
                map["meas55"].toString()+"','"+\
                map["meas56"].toString()+"','"+\
                map["meas57"].toString()+"','"+\
                map["meas58"].toString()+"','"+\
                map["meas59"].toString()+"','"+\
                map["meas60"].toString()+"','"+\
                map["meas61"].toString()+"','"+\
                map["meas62"].toString()+"','"+\
                map["meas63"].toString()+"','"+\
                map["meas64"].toString()+"','"+\
                map["meas65"].toString()+"','"+\
                map["meas66"].toString()+"','"+\
                map["meas67"].toString()+"','"+\
                map["meas68"].toString()+"','"+\
                map["meas69"].toString()+"','"+\
                map["meas70"].toString()+"','"+\
                map["meas71"].toString()+"','"+\
                map["meas72"].toString()+"','"+\
                map["meas73"].toString()+"','"+\
                map["meas74"].toString()+"','"+\
                map["meas75"].toString()+"','"+\
                map["meas76"].toString()+"','"+\
                map["meas77"].toString()+"','"+\
                map["meas78"].toString()+"','"+\
                map["meas79"].toString()+"','"+\
                map["meas80"].toString()+"','"+\
                map["meas81"].toString()+"','"+\
                map["meas82"].toString()+"','"+\
                map["meas83"].toString()+"','"+\
                map["meas84"].toString()+"','"+\
                map["meas85"].toString()+"','"+\
                map["meas86"].toString()+"','"+\
                map["meas87"].toString()+"','"+\
                map["meas88"].toString()+"','"+\
                map["meas89"].toString()+"','"+\
                map["meas90"].toString()+"','"+\
                map["meas91"].toString()+"','"+\
                map["meas92"].toString()+"','"+\
                map["meas93"].toString()+"','"+\
                map["meas94"].toString()+"','"+\
                map["meas95"].toString()+"','"+\
                map["meas96"].toString()+"','"+\
                map["meas97"].toString()+"','"+\
                map["meas98"].toString()+"','"+\
                map["meas99"].toString()+"','"+\
                map["meas100"].toString()+"','"+\
                map["meas101"].toString()+"','"+\
                map["meas102"].toString()+"','"+\
                map["meas103"].toString()+"','"+\
                map["meas104"].toString()+"','"+\
                map["meas105"].toString()+"','"+\
                map["meas106"].toString()+"','"+\
                map["meas107"].toString()+"','"+\
                map["meas108"].toString()+"','"+\
                map["meas109"].toString()+"','"+\
                map["meas110"].toString()+"','"+\
                map["meas111"].toString()+"','"+\
                map["meas112"].toString()+"','"+\
                map["meas113"].toString()+"','"+\
                map["meas114"].toString()+"','"+\
                map["meas115"].toString()+"','"+\
                map["meas116"].toString()+"','"+\
                map["meas117"].toString()+"','"+\
                map["meas118"].toString()+"','"+\
                map["meas119"].toString()+"','"+\
                map["meas120"].toString()+"','"+\
                map["meas121"].toString()+"','"+\
                map["meas122"].toString()+"','"+\
                map["meas123"].toString()+"','"+\
                map["meas124"].toString()+"','"+\
                map["meas125"].toString()+"','"+\
                map["meas126"].toString()+"','"+\
                map["meas127"].toString()+"','"+\
                map["meas128"].toString()+"','"+\
                map["meas129"].toString()+"','"+\
                map["meas130"].toString()+"','"+\
                map["meas131"].toString()+"','"+\
                map["meas132"].toString()+"','"+\
                map["meas133"].toString()+"','"+\
                map["meas134"].toString()+"','"+\
                map["meas135"].toString()+"','"+\
                map["meas136"].toString()+"','"+\
                map["meas137"].toString()+"','"+\
                map["meas138"].toString()+"','"+\
                map["meas139"].toString()+"','"+\
                map["meas140"].toString()+"','"+\
                map["meas141"].toString()+"','"+\
                map["meas142"].toString()+"','"+\
                map["meas143"].toString()+"','"+\
                map["meas144"].toString()+"','"+\
                map["meas145"].toString()+"','"+\
                map["meas146"].toString()+"','"+\
                map["meas147"].toString()+"','"+\
                map["meas148"].toString()+"','"+\
                map["meas149"].toString()+"','"+\
                map["meas150"].toString()+"','"+\
                map["meas151"].toString()+"','"+\
                map["meas152"].toString()+"','"+\
                map["meas153"].toString()+"','"+\
                map["meas154"].toString()+"','"+\
                map["meas155"].toString()+"','"+\
                map["meas156"].toString()+"','"+\
                map["meas157"].toString()+"','"+\
                map["meas158"].toString()+"','"+\
                map["meas159"].toString()+"','"+\
                map["meas160"].toString()+"','"+\
                map["meas161"].toString()+"','"+\
                map["meas162"].toString()+"','"+\
                map["meas163"].toString()+"','"+\
                map["meas164"].toString()+"','"+\
                map["meas165"].toString()+"','"+\
                map["meas166"].toString()+"','"+\
                map["meas167"].toString()+"','"+\
                map["meas168"].toString()+"','"+\
                map["meas169"].toString()+"','"+\
                map["meas170"].toString()+"','"+\
                map["meas171"].toString()+"','"+\
                map["meas172"].toString()+"','"+\
                map["meas173"].toString()+"','"+\
                map["meas174"].toString()+"','"+\
                map["meas175"].toString()+"','"+\
                map["meas176"].toString()+"','"+\
                map["meas177"].toString()+"','"+\
                map["meas178"].toString()+"','"+\
                map["meas179"].toString()+"','"+\
                map["meas180"].toString()+"','"+\
                map["meas181"].toString()+"','"+\
                map["meas182"].toString()+"','"+\
                map["meas183"].toString()+"','"+\
                map["meas184"].toString()+"','"+\
                map["meas185"].toString()+"','"+\
                map["meas186"].toString()+"','"+\
                map["meas187"].toString()+"','"+\
                map["meas188"].toString()+"','"+\
                map["meas189"].toString()+"','"+\
                map["meas190"].toString()+"','"+\
                map["meas191"].toString()+"','"+\
                map["meas192"].toString()+"','"+\
                map["meas193"].toString()+"','"+\
                map["meas194"].toString()+"','"+\
                map["meas195"].toString()+"','"+\
                map["meas196"].toString()+"','"+\
                map["meas197"].toString()+"','"+\
                map["meas198"].toString()+"','"+\
                map["meas199"].toString()+"','"+\
                map["meas200"].toString()+"','"+\
                map["meas201"].toString()+"','"+\
                map["meas202"].toString()+"','"+\
                map["meas203"].toString()+"','"+\
                map["meas204"].toString()+"','"+\
                map["meas205"].toString()+"','"+\
                map["meas206"].toString()+"','"+\
                map["meas207"].toString()+"','"+\
                map["meas208"].toString()+"','"+\
                map["meas209"].toString()+"','"+\
                map["meas210"].toString()+"','"+\
                map["meas211"].toString()+"','"+\
                map["meas212"].toString()+"','"+\
                map["meas213"].toString()+"','"+\
                map["meas214"].toString()+"','"+\
                map["meas215"].toString()+"','"+\
                map["meas216"].toString()+"','"+\
                map["meas217"].toString()+"','"+\
                map["meas218"].toString()+"','"+\
                map["meas219"].toString()+"','"+\
                map["meas220"].toString()+"','"+\
                map["meas221"].toString()+"','"+\
                map["meas222"].toString()+"','"+\
                map["meas223"].toString()+"','"+\
                map["meas224"].toString()+"','"+\
                map["meas225"].toString()+"','"+\
                map["meas226"].toString()+"','"+\
                map["meas227"].toString()+"','"+\
                map["meas228"].toString()+"','"+\
                map["meas229"].toString()+"','"+\
                map["meas230"].toString()+"','"+\
                map["meas231"].toString()+"','"+\
                map["meas232"].toString()+"','"+\
                map["meas233"].toString()+"','"+\
                map["meas234"].toString()+"','"+\
                map["meas235"].toString()+"','"+\
                map["meas236"].toString()+"','"+\
                map["meas237"].toString()+"','"+\
                map["meas238"].toString()+"','"+\
                map["meas239"].toString()+"','"+\
                map["meas240"].toString()+"','"+\
                map["meas241"].toString()+"','"+\
                map["meas242"].toString()+"','"+\
                map["meas243"].toString()+"','"+\
                map["meas244"].toString()+"','"+\
                map["meas245"].toString()+"','"+\
                map["meas246"].toString()+"','"+\
                map["meas247"].toString()+"','"+\
                map["meas248"].toString()+"','"+\
                map["meas249"].toString()+"','"+\
                map["meas250"].toString()+"','"+\
                map["meas251"].toString()+"','"+\
                map["meas252"].toString()+"','"+\
                map["meas253"].toString()+"','"+\
                map["meas254"].toString()+"','"+\
                map["meas255"].toString()+"','"+\
                map["meas256"].toString()+"','"+\
                map["meas257"].toString()+"','"+\
                map["meas258"].toString()+"','"+\
                map["meas259"].toString()+"','"+\
                map["meas260"].toString()+"','"+\
                map["meas261"].toString()+"','"+\
                map["meas262"].toString()+"','"+\
                map["meas263"].toString()+"','"+\
                map["meas264"].toString()+"','"+\
                map["meas265"].toString()+"','"+\
                map["meas266"].toString()+"','"+\
                map["meas267"].toString()+"','"+\
                map["meas268"].toString()+"','"+\
                map["meas269"].toString()+"','"+\
                map["meas270"].toString()+"','"+\
                map["meas271"].toString()+"','"+\
                map["meas272"].toString()+"','"+\
                map["meas273"].toString()+"','"+\
                map["meas274"].toString()+"','"+\
                map["meas275"].toString()+"','"+\
                map["meas276"].toString()+"','"+\
                map["meas277"].toString()+"','"+\
                map["meas278"].toString()+"','"+\
                map["meas279"].toString()+"','"+\
                map["meas280"].toString()+"','"+\
                map["meas281"].toString()+"','"+\
                map["meas282"].toString()+"','"+\
                map["meas283"].toString()+"','"+\
                map["meas284"].toString()+"','"+\
                map["meas285"].toString()+"','"+\
                map["meas286"].toString()+"','"+\
                map["meas287"].toString()+"','"+\
                map["meas288"].toString()+"','"+\
                map["meas289"].toString()+"','"+\
                map["meas290"].toString()+"','"+\
                map["meas291"].toString()+"','"+\
                map["meas292"].toString()+"','"+\
                map["meas293"].toString()+"','"+\
                map["meas294"].toString()+"','"+\
                map["meas295"].toString()+"','"+\
                map["meas296"].toString()+"','"+\
                map["meas297"].toString()+"','"+\
                map["meas298"].toString()+"','"+\
                map["meas299"].toString()+"','"+\
                map["meas300"].toString()+"','"+\
                map["meas301"].toString()+"','"+\
                map["meas302"].toString()+"','"+\
                map["meas303"].toString()+"','"+\
                map["meas304"].toString()+"','"+\
                map["meas305"].toString()+"','"+\
                map["meas306"].toString()+"','"+\
                map["meas307"].toString()+"','"+\
                map["meas308"].toString()+"','"+\
                map["meas309"].toString()+"','"+\
                map["meas310"].toString()+"','"+\
                map["meas311"].toString()+"','"+\
                map["meas312"].toString()+"','"+\
                map["meas313"].toString()+"','"+\
                map["meas314"].toString()+"','"+\
                map["meas315"].toString()+"','"+\
                map["meas316"].toString()+"','"+\
                map["meas317"].toString()+"','"+\
                map["stoid"].toString()+")";
        qDebug()<<query;
        qry1.exec(query);
///edv
        query="select fincode,trdr from findoc where findoc="+map["mysqlid"].toString();
        qry1.exec(query);
        qry1.next();
        QString fincode=qry1.value(0).toString();

        query="UPDATE findoc set status="+map["status"].toString()+" where findoc="+map["mysqlid"].toString();
        qry2.exec(query);
        query="select code from trdr where trdr="+qry1.value(1).toString();
        qry2.exec(query);
        qry2.next();
        QString cuscode=qry2.value(0).toString();
        query="select top 1 mtrl from snlines where code='"+map["newserial"].toString()+"'";
        qry2.exec(query);
        qry2.next();
        QString newserialmtrl=qry2.value(0).toString();
        query="select top 1 mtrl from snlines where code='"+map["oldserial"].toString()+"'";
        qry2.exec(query);
        qry2.next();
        QString oldserialmtrl=qry2.value(0).toString();
        query="select code from mtrl where mtrl='"+newserialmtrl+"'";
        qry2.exec(query);
        qry2.next();
        QString newserialmtrlcode=qry2.value(0).toString();
        query="select code from mtrl where mtrl='"+oldserialmtrl+"'";
        qry2.exec(query);
        qry2.next();
        QString oldserialmtrlcode=qry2.value(0).toString();
        QString settingsFile=QCoreApplication::applicationDirPath() +"/settings.ini";
        QSettings *settings=new QSettings(settingsFile,QSettings::IniFormat);
        QString dap=settings->value("dapdocseries").toString();
        QString dep=settings->value("depdocseries").toString();
        QString trndate=QDate::currentDate().toString("yyyy-MM-dd");
        delete settings;
        query="INSERT INTO ccctempdeltia (ccccuscode,cccitecode,ccctrndate,cccseries,cccserialnumber,cccstoid,isins) VALUES ('"+cuscode+"','"+newserialmtrlcode+"','"+trndate+"',"+dap+\
                ",'"+map["newserial"].toString()+"',"+map["stoid"].toString()+",0)";

        qry2.exec(query);
        query="INSERT INTO ccctempdeltia (ccccuscode,cccitecode,ccctrndate,cccseries,cccserialnumber,cccstoid,isins) VALUES ('"+cuscode+"','"+oldserialmtrlcode+"','"+trndate+"',"+dep+\
                ",'"+map["oldserial"].toString()+"',"+map["stoid"].toString()+",0)";

        qry2.exec(query);
        QDir::setCurrent("c:\\algo\\autoimport");
        system("AutoRunSnImport.bat");
        //    QJsonObject jsonobj=jsondoc.object();
        //  QVariant map = jsonobj.toVariantMap();
        //qDebug()<<"Map"<<map;


        //qDebug()<<"KIND:"<<request.getParameter("kind");
        //qDebug()<<"title:"<<request.getParameter("title");
        qDebug()<<"text:"<<request.getParameter("text");

        QByteArray buffer=request.getParameter("image");
        QFile* file=new QFile(scanpath+map["imagepath"].toString());
        file->open(QIODevice::WriteOnly);
        file->write(buffer);
        response.write("REQUESTID:"+requestid,true);
    }
}
