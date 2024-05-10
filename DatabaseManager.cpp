/**************************************************************************
** Copyright (C) 2013 Southgis Co.,Ltd. Written by Young Yori, All rights reserved.
**--------------------------------------------------------------------------------
**   Filename:LinearList.h
**   Author: Young Yori
**   Data: Administrator 2013/12/25 2013
**   Description:
**          This file is part of the Data Development Department Project and shall
**      only be used, modified, and distributed under the terms of the Data
**      Development Department this Source.
**
**      Included in the build system of the FreeType library.
**--------------------------------------------------------------------------------
**                      www.newdebug.com, 12319597@qq.com
**************************************************************************/

#include "DatabaseManager.h"
#include "GlobalConstances.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QMessageBox>

#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent),
    m_status(Read)
{
}

//여기에서는 SQLITECIPHER 데이터베이스 드라이버가 사용됩니다.
// Qt와 함께 제공되는 기본 SQlite 데이터베이스를 사용하는 경우 이를 수정합니다.
// 데이터베이스 드라이버 이름은 SQLITE입니다. 그렇지 않으면 데이터베이스 엔진을 정상적으로 사용할 수 없습니다.
bool DatabaseManager::createConnect()
{
    switch( m_status )
    {
    case Read:
        {
            if(QSqlDatabase::contains("READ"))
                m_db = QSqlDatabase::database("READ");
            else
            {
                m_db = QSqlDatabase::addDatabase("QSQLITE", "READ");
                if (TABLE_SAVE_DATA)
                    m_db.setDatabaseName(g_dbFileName);
            }
        };
        break;
    case Write:
        {
            if(QSqlDatabase::contains("WRITE"))
                m_db = QSqlDatabase::database("WRITE");
            else
            {
                m_db = QSqlDatabase::addDatabase("QSQLITE", "WRITE");
                m_db.setDatabaseName(g_dbFileName);
            }
        };
        break;
    }

    if( !m_db.isOpen() )
    {
        if ( !m_db.open() )
        {
            qDebug()<< QString(" can't open database >>>>>> data.sqlite");
            qDebug() << "error code: " << m_db.lastError();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::createTable()
{
    QStringList tableList = m_db.tables();
    QSqlQuery query(m_db);
    if( !tableList.contains(g_dbTableName) )
    {
        QString createTable = QString("CREATE TABLE %1 (ID integer PRIMARY KEY AUTOINCREMENT,"
                                      "MMSI text, NUM_POINT text, MIN_LAT text, MAX_LAT text, MIN_LON text, MAX_LON text)"
                                      ).arg(g_dbTableName);
        if(!query.exec(createTable))
        {
            QMessageBox::warning(0, QObject::tr("Create table error"), QObject::tr("Error: ")+ query.lastError().text(), QMessageBox::Ok);
            qDebug()<< "Create table error: " << query.lastError();
            return false;
        }
        qDebug()<< "Create table Succeed.";
    }

    return true;
}
