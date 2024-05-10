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

#ifndef GLOBALCONSTANCES_H
#define GLOBALCONSTANCES_H

#include <QString>
static const QString g_dbFileName = "data.dat";
static const QString g_dbTableName = "daily";

static const QString g_mmsiLabel = "MMSI";
static const QString g_numPointLabel = "NUM_POINT";
static const QString g_minLatLabel = "MIN_LAT";
static const QString g_maxLatLabel = "MAX_LAT";
static const QString g_minLonLabel = "MIN_LON";
static const QString g_maxLonLabel = "MAX_LON";

#define MAX_ITEM        100

#define MMSI            1  // ID: 0
#define NUM_POINT       2
#define MIN_LAT         3
#define MAX_LAT         4
#define MIN_LON         5
#define MAX_LON         6

#endif // GLOBALCONSTANCES_H

