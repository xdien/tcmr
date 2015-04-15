#include "reportbenhtruyennhiem.h"
#include "ui_reportbenhtruyennhiem.h"

#include <QMessageBox>
#include <QTextCursor>
#include <QTextDocument>

ReportBenhTruyenNhiem::ReportBenhTruyenNhiem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportBenhTruyenNhiem)
{
    ui->setupUi(this);
    htmltemp = new HtmlTemp();
   table_benh.setQuery("select ten_benh,ma_benh from benh where la_vx = TRUE");
   ui->treeView_benh->setModel(&table_benh);
   ui->treeView_benhDChon->setModel(&itemModel_benhDChon);
}

ReportBenhTruyenNhiem::~ReportBenhTruyenNhiem()
{
    delete ui;
}

void ReportBenhTruyenNhiem::on_pushButton_clicked()
{
    QString mau;
    //this->tcdd("TH_00000001","00001",200);
    QTextDocument *document = new QTextDocument();
    QTextCursor cursor(document);
    //truyen tr td vao bien conntent
    for(int i =0;i<itemModel_benhDChon.rowCount();i++)
    {
        ma_benh = itemModel_benhDChon.index(i,1).data().toString();
        ma_thuoc = "TH_00000001";
        mau = mau + "<tr>\
                    <td>"+itemModel_benhDChon.index(i,0).data().toString()+"</td>\
                    <td>"+tcdd(ma_thuoc,"00001",200)+"</td>\
                    <td></td>\
                    <td>"+this->ktc(ma_thuoc,"00001",200000)+"</td>\
                    <td>"+this->kr(ma_thuoc,"00001",11)+"</td>\
                    <!-- khoi 2-->"
                "<td>"+tcdd(ma_thuoc,"00001",200)+"</td>\
                <td></td>\
                <td>"+this->ktc(ma_thuoc,"00001",200000)+"</td>\
                <td>"+this->kr(ma_thuoc,"00001",11)+"</td>\
                    </tr>";
    }
    //qDebug() << this->kiemtraDungHen(22,"TH_00000001","00001");
    cursor.insertHtml(htmltemp->header1+mau);
#ifdef __MINGW32__
    //thu su dung webview tren windows
    QWebView *view = new QWebView();
    view->setHtml(document->toHtml());
    view->show();
#endif
#ifdef __linux
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    report->setReportFile("report/ket_qua_tiem_chung_tre_em.ncr"); //set the report filename fullpath or relative to dir
    report->addParameter("aaa",document->toHtml());
    report->runReportToPreview(); // run to preview output

    if( report->hasError())
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Report error: ") + report->lastErrorMsg());
        msgBox.exec();
    }
    else
    {
        // show preview
        NCReportPreviewWindow *pv = new NCReportPreviewWindow();    // create preview window
        pv->setOutput( (NCReportPreviewOutput*)report->output() );  // add output to the window
        pv->setReport(report);
        pv->setWindowModality(Qt::ApplicationModal );    // set modality
        pv->setAttribute( Qt::WA_DeleteOnClose );    // set attrib
        pv->exec();  // run like modal dialog
    }
#endif
}

QString ReportBenhTruyenNhiem::tcdd(QString mathuoc, QString madc, int sothangtuoinhonhon)
{
    //query.exec("select * from somuitiem where ma_thuoc ='"+mathuoc+"'");//1 danh sach cac benh nhan tiem thuoc nao do
    query_tmp.exec("select count( distinct tiem.ma_bn) from tt_benh_nhan "
                   "right join tiem on tt_benh_nhan.ma_bn = tiem.ma_bn where ma_thuoc ='"+mathuoc+"' and ma_dc ='"+madc+"' and ngay_hen_kt = 'Du lieu' and extract(year from age(sn))*12+extract(month from age(sn)) <= "+QString::number(sothangtuoinhonhon)+"");
    //qDebug() << query_tmp.lastQuery();
    if(query_tmp.next())
    {
        return query_tmp.value(0).toString();
    }else
        return "LOI: "+query_tmp.lastError().text();
}

//add item model
QList<QStandardItem *> ReportBenhTruyenNhiem::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

void ReportBenhTruyenNhiem::on_treeView_benh_clicked(const QModelIndex &index)
{
    ma_benh = table_benh.index(index.row(),1).data().toString();
    tmp = itemModel_benhDChon.findItems(ma_benh,Qt::MatchExactly,1);
    if(tmp.count() < 1 && itemModel_benhDChon.rowCount() < 5)
        this->itemModel_benhDChon.appendRow(this->prepareRow(table_benh.index(index.row(),0).data().toString(),ma_benh,""));
   // itemModel_benhDChon.appendRow(this->prepareRow(table_benh.index(index.row(),0).data().toString(),table_benh.index(index.row(),1).data().toString(),""));
}

void ReportBenhTruyenNhiem::on_pushButton_2_clicked()
{
    if(ui->treeView_benhDChon->currentIndex().isValid())
         itemModel_benhDChon.removeRow(ui->treeView_benhDChon->currentIndex().row());
}
QString ReportBenhTruyenNhiem::ktcdd(QString mathuoc, QString madc, int sothangtuoinhonhon)
{
    //query_tmp.exec("")
}

QString ReportBenhTruyenNhiem::ktc(QString mabenh, QString madc, int sothangtuoinhohon)
{
    query_tmp.exec("select count(distinct tt_benh_nhan.ma_bn) from tt_benh_nhan "
                   "full outer join tiem on tt_benh_nhan.ma_bn = tiem.ma_bn "
                   "right join (select distinct ma_bn from co_benh where ma_benh = '"+mabenh+"') as aac on aac.ma_bn = tt_benh_nhan.ma_bn "
                   "where tiem.ma_bn is null and ma_dc ='"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) <= "+QString::number(sothangtuoinhohon)+"");
    qDebug() << query_tmp.lastQuery();
    if(query_tmp.next())
    {
        return query_tmp.value(0).toString();
    }else
        return "LOI: "+query_tmp.lastError().text();
}
QString ReportBenhTruyenNhiem::kr(QString mathuoc, QString madc, int sothangtuoinhohon)
{
    query_tmp.exec("select count(distinct aa.ma_bn) from "
                   "(select tiem.ma_bn,max(stt_lieu),ma_thuoc from tt_benh_nhan "
                   "right join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn "
                   "where tiem.ma_thuoc = '"+mathuoc+"' and ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) <= "+QString::number(sothangtuoinhohon)+" group by tiem.ma_bn,ma_thuoc) as aa, tongsolantiem where aa.ma_thuoc = tongsolantiem.ma_thuoc and max < sl_nhac_lai");
    if(query_tmp.next())
    {
        return query_tmp.value(0).toString();
    }else
        return "LOI: "+query_tmp.lastError().text();
}
