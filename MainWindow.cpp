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

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    updateCtrl();

    QStringList pages;
    int totalPage = ui.tableView->totalPage();
    for( int i = 1; i <= totalPage; ++i)
        pages.append( QString("%1").arg(i) );
    ui.gotoPageBox->addItems(pages);

    connect(ui.tableView, SIGNAL(insertAct()), this, SLOT(insert()) );
    connect(ui.tableView, SIGNAL(removeAct()), this, SLOT(remove()) );

    connect(ui.prePageBtn, SIGNAL(clicked()), this, SLOT(prevPage()) );
    connect(ui.nextPageBtn, SIGNAL(clicked()), this, SLOT(nextPage()) );
    connect(ui.gotoPageBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(gotoPage(int)) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateCtrl()
{
    int total = ui.tableView->totalSize();
    ui.totalLabel->setText( tr("Total %1").arg(total) );

    int curPage = ui.tableView->currentPage();
    int totalPage = ui.tableView->totalPage();
    ui.curPageLabel->setText( tr("Page %1/%2").arg(curPage).arg(totalPage));

    ui.nextPageBtn->setEnabled(true);
    ui.prePageBtn->setEnabled(true);

    if (curPage >= totalPage)
        ui.nextPageBtn->setEnabled(false);
    else if( curPage <= 1)
        ui.prePageBtn->setEnabled(false);
    else
        ;
}

void MainWindow::insert()
{
    QList<QVariant> list;
    QString mmsi = "TEST MMSI";
    QString num_point = "TEST NUM_POINT";
    QString min_lat = "TEST MIN_LAT";
    QString max_lat = "TEST MAX_LAT";
    QString min_lon = "TEST MIN_LON";
    QString max_lon = "TEST MAX_LON";
    list.append({mmsi, num_point, min_lat, max_lat, min_lon, max_lon});

    ui.tableView->insert(list);
    updateCtrl();

    int totalPage = ui.tableView->totalPage();
    int count = ui.gotoPageBox->count();
    if( count < totalPage)
    {
        ui.gotoPageBox->addItem(QString("%1").arg(count+1));
    }
}

void MainWindow::remove()
{
    ui.tableView->remove();
    updateCtrl();
    int totalPage = ui.tableView->totalPage();

    int count = ui.gotoPageBox->count();
    if( count > totalPage)
    {
        ui.gotoPageBox->removeItem(count-1);
    }
}

void MainWindow::gotoPage(int index)
{
    index++;
    ui.tableView->gotoPage(index);
    updateCtrl();
}

void MainWindow::nextPage()
{
    ui.tableView->nextPage();
    updateCtrl();
}

void MainWindow::prevPage()
{
    ui.tableView->previousPage();
    updateCtrl();
}
