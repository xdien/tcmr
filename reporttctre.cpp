#include "reporttctre.h"
#include "ui_reporttctre.h"
#include <QPrintDialog>

#include <QMessageBox>
#include <QTextEdit>
#include <QWebView>
//#include <QtPrintSupport>
#include <QtWebKit/QtWebKit>



ReportTCTRE::ReportTCTRE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportTCTRE)
{
    ui->setupUi(this);
    //khoi dong
    diachi = new QSqlQueryModel();
    diachiDC = new QSqlQueryModel();
    diachiComBox = new QSqlQueryModel();
    ui->listView__diaphuong->setModel(diachi);
    //ui->listView_dsdiaphuongDChon->setModel(diachiDC);
    ui->listView_dsdiaphuongDChon->setModel(&item_tinhthanh);
    //load cac bien default cho dia cap bat de chon
    ui->comboBox->addItem("Xa/phuong","ward");
    ui->comboBox->addItem("Quan/huyen","district");
    ui->comboBox->addItem("Tinh/Thannh","province");
    //ui->comboBox_2->setEnabled(false);
    ui->comboBox_2->setModel(diachiComBox);
     connect(this,SIGNAL(setvalue(QString,QString,QString)),this,SLOT(setbang(QString,QString,QString)));
    htmltemp = new HtmlTemp();
}

ReportTCTRE::~ReportTCTRE()
{
    delete ui;
}


void ReportTCTRE::on_comboBox_activated(int index)
{
    diachi->clear();
    diachiComBox->clear();
    ten_bang =  ui->comboBox->itemData(index).toString();
    if(!state){
        diachi->setQuery("select name,"+ten_bang+"id from "+ten_bang+"");
    }else{
         if(ten_bang =="ward")
         {
             diachiComBox->setQuery("select name,districtid from district");
         }else{
             if(ten_bang == "district")
                 diachiComBox->setQuery("select name,provinceid from province");
         }
    }
}

void ReportTCTRE::on_checkBox_toggled(bool checked)
{
    state = checked;
    diachi->clear();
    ui->comboBox_2->setEnabled(state);
    if(ten_bang =="ward")
    {
        diachi->setQuery("select ward.name,ward.wardid from ward left join district on district.districtid = ward.districtid");
    }else{
        if(ten_bang == "district")
            diachiComBox->setQuery("select name,provinceid from province");
    }
}

void ReportTCTRE::on_comboBox_2_activated(int index)
{
    if(ten_bang =="ward")
    {

        emit this->setvalue("ward","district",diachiComBox->index(index,1).data().toString());
        //diachi->setQuery("select ward.name,ward.wardid from ward left join district on district.districtid = ward.districtid where districtid ='"+ui->comboBox_2->currentData(index).toString()+"'");
    }else{
        if(ten_bang == "district")
           emit this->setvalue("district","province",diachiComBox->index(index,1).data().toString());
    }
}
void ReportTCTRE::setbang(QString tenbang, QString captren, QString mavung)
{

    diachi->setQuery("select "+tenbang+".name,"+tenbang+"id from "+tenbang+" left join "+captren+" on "+captren+"."+captren+"id = "+tenbang+"."+captren+"id where "+tenbang+"."+captren+"id = '"+mavung+"'");
}

void ReportTCTRE::on_listView__diaphuong_clicked(const QModelIndex &index)
{
    ma_dc = diachi->index(index.row(),1).data().toString();
    tmp = item_tinhthanh.findItems(ma_dc,Qt::MatchExactly,1);
    if(tmp.count() < 1 && item_tinhthanh.rowCount() < 5)
        this->item_tinhthanh.appendRow(this->prepareRow(diachi->index(index.row(),0).data().toString(),ma_dc,""));
}
QList<QStandardItem *> ReportTCTRE::prepareRow(const QString &first,
                                                const QString &second,
                                                const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

void ReportTCTRE::on_pushButton_clicked()
{
    if(ui->listView_dsdiaphuongDChon->currentIndex().isValid())
        item_tinhthanh.removeRow(ui->listView_dsdiaphuongDChon->currentIndex().row());
}

void ReportTCTRE::on_pushButton_2_clicked()
{
    QString mau;
    QTextDocument *document = new QTextDocument();
    QTextCursor cursor(document);
    //truyen tr td vao bien conntent
    for(int i =0;i<item_tinhthanh.rowCount();i++)
    {

        ma_dc = item_tinhthanh.index(i,1).data().toString();
        mau = mau + "<tr><td>"+QString::number(i+1)+"</td>\
                                <td>"+ item_tinhthanh.index(i,0).data().toString() +"</td><!-- hen thi stt-->\
                                <!-- danh cho khoi 1-->\
                                <td>"+this->tongsoTreTheoThang(18,ma_dc)+"</td>\
                                <td>"+QString::number(this->tongsotre("0",ma_dc,"TH_00000001"))+"</td>\
                                <td>"+this->tongsoTreTiemTheoThuoc("TH_00000000",ma_dc,200)+"</td>\
                                <!-- danh cho khoi 2 dua vao do tuoi tinh so doi tuong vd: 1-2,4-10 la 2-->\
                                <td>"+tongsoDoiTuongTheoThuoc2("TH_00000001",ma_dc,200)+"</td>\
                                <td>"+tongSoNguoiTiem(1, "TH_00000001",ma_dc,200)+"</td>\
                                <td>"+tongSoNguoiTiem(2, "TH_00000001",ma_dc,200)+"</td>\
                                 <td>"+tongsoDoiTuongTheoThuoc3("TH_00000001",ma_dc,200)+"</td>\
                                <td>"+tongSoNguoiTiem(3, "TH_00000001",ma_dc,200)+"</td>\
                                <!-- khoi 3-->\
                                <td>"+tongsodoiTuongVNNB("TH_00000001",ma_dc,200)+"</td>\
                                <td>"+this->tongsoTreTiemTheothuoc("TH_00000001",ma_dc,200)+"</td>\
                                </tr>";
    }
    cursor.insertHtml(htmltemp->header+mau);
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

int ReportTCTRE::tongsotre(QString sothang,QString madc,QString mathuoc)
{
    query.exec("select count(distinct tt_benh_nhan.ma_bn) from tt_benh_nhan left join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where extract(month from age(sn)) > "+sothang+" and ma_dc = '"+madc+"' and (select distinct ma_bn from tiem where ngay_tiem is not null and tiem.ma_thuoc = '"+mathuoc+"') = tt_benh_nhan.ma_bn");
    qDebug() << query.lastQuery();
    if(query.next())
    return query.value(0).toInt();
    else
        return -1;
}
QString ReportTCTRE::tongsoTreTheoThang(int sothang, QString madc)
{
    query.exec("select count(distinct tt_benh_nhan.ma_bn) from tt_benh_nhan where extract(year from age(sn))*12+extract(month from age(sn)) = "+QString::number(sothang)+" and ma_dc = '"+madc+"'");
    if(query.next())
    {
        return query.value(0).toString();
    }else{
        return query.lastError().text();
    }
}
QString ReportTCTRE::tongsoTreTiemTheoThuoc(QString mathuoc, QString madc, int sothangtuoinhohon)
{
    query.exec("select count(distinct tt_benh_nhan.ma_bn) from tt_benh_nhan left join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) < "+QString::number(sothangtuoinhohon)+" and (select distinct ma_bn from tiem where ngay_tiem is not null and tiem.ma_thuoc = '"+mathuoc+"') = tt_benh_nhan.ma_bn");
    if(query.next())
        return query.value(0).toString();
    else
        return query.lastError().text();
}
QString ReportTCTRE::tongsoDoiTuongTheoThuoc2(QString mathuoc, QString madc, int sothangtuoinhohon)//so doi tuong tiem mui 1 va 2, Viem nao nhat ban
{
    //query.exec("select count(distinct ma_dotuoi) from tt_benh_nhan,(select count(ma_thuoc) as somui,tiem.ma_bn "
    //           "from tt_benh_nhan right join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where ngay_tiem is not null "
    //           "and tiem.ma_thuoc = '"+mathuoc+"' group by tiem.ma_bn) as demui where demui.somui "+dk+""+somui+" and ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) < "+QString::number(sothangtuoinhohon)+"");
    query.exec("select count(distinct tiem.ma_bn) from tt_benh_nhan right join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where tiem.ma_thuoc = '"+mathuoc+"' and ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) < "+QString::number(sothangtuoinhohon)+" and stt_lieu <= 2 and tiem.ma_bn not in(select ma_bn from tiem where stt_lieu = 3)");
    qDebug() << query.lastQuery();
    if(query.next())
        return query.value(0).toString();
    else
        return query.lastError().text();
}
QString ReportTCTRE::tongsoDoiTuongTheoThuoc3(QString mathuoc, QString madc, int sothangtuoinhohon)//viem nao nhat ban mui 3
{
    query.exec("select count(distinct tiem.ma_bn) from tt_benh_nhan right join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where tiem.ma_thuoc = '"+mathuoc+"' and ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) < "+QString::number(sothangtuoinhohon)+" and stt_lieu = 3");
    qDebug() << query.lastQuery();
    if(query.next())
        return query.value(0).toString();
    else
        return query.lastError().text();
}
QString ReportTCTRE::tongsodoiTuongVNNB(QString mathuoc, QString madc, int sothangtuoinhohon)
{
    query.exec("select count(distinct tiem.ma_bn) from tt_benh_nhan right join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where tiem.ma_thuoc = '"+mathuoc+"' and ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) < "+QString::number(sothangtuoinhohon)+"");
    qDebug() << query.lastQuery();
    if(query.next())
        return query.value(0).toString();
    else
        return query.lastError().text();
}

QString ReportTCTRE::tongSoNguoiTiem(int somui, QString mathuoc, QString madc,  int sothangtuoinhohon)
{
    query.exec("select count(ma_thuoc) from somuitiem where ma_dc = '"+madc+"' and somui = "+QString::number(somui)+" and ma_thuoc ='"+mathuoc+"'");

    if(query.next())
        return query.value(0).toString();
    else
        return query.lastError().text();
}
QString ReportTCTRE::tongsoTreTiemTheothuoc(QString mathuoc, QString madc, int sothangtuoinhohon)
{
    query.exec("select count(distinct tt_benh_nhan.ma_bn) from tt_benh_nhan left join tiem on tiem.ma_bn = tt_benh_nhan.ma_bn where tiem.ma_thuoc = '"+mathuoc+"' and ma_dc = '"+madc+"' and extract(year from age(sn))*12+extract(month from age(sn)) < "+QString::number(sothangtuoinhohon)+"");
            if(query.next())
                return query.value(0).toString();
            else
                return query.lastError().text();
}

void ReportTCTRE::on_pushButton_3_clicked()
{
#ifdef __MINGW32__
    QString mau;
    QTextDocument *document = new QTextDocument();
    QTextCursor cursor(document);
    //truyen tr td vao bien conntent
    for(int i =0;i<item_tinhthanh.rowCount();i++)
    {

        ma_dc = item_tinhthanh.index(i,1).data().toString();
        mau = mau + "<tr><td>"+QString::number(i+1)+"</td>\
                                <td>"+ item_tinhthanh.index(i,0).data().toString() +"</td><!-- hen thi stt-->\
                                <!-- danh cho khoi 1-->\
                                <td>"+this->tongsoTreTheoThang(18,ma_dc)+"</td>\
                                <td>"+QString::number(this->tongsotre("0",ma_dc,"TH_00000001"))+"</td>\
                                <td>"+this->tongsoTreTiemTheoThuoc("TH_00000000",ma_dc,200)+"</td>\
                                <!-- danh cho khoi 2 dua vao do tuoi tinh so doi tuong vd: 1-2,4-10 la 2-->\
                                <td>"+tongsoDoiTuongTheoThuoc2("TH_00000001",ma_dc,200)+"</td>\
                                <td>"+tongSoNguoiTiem(1, "TH_00000001",ma_dc,200)+"</td>\
                                <td>"+tongSoNguoiTiem(2, "TH_00000001",ma_dc,200)+"</td>\
                                 <td>"+tongsoDoiTuongTheoThuoc3("TH_00000001",ma_dc,200)+"</td>\
                                <td>"+tongSoNguoiTiem(3, "TH_00000001",ma_dc,200)+"</td>\
                                <!-- khoi 3-->\
                                <td>"+tongsodoiTuongVNNB("TH_00000001",ma_dc,200)+"</td>\
                                <td>"+this->tongsoTreTiemTheothuoc("TH_00000001",ma_dc,200)+"</td>\
                                </tr>";
    }
    cursor.insertHtml(htmltemp->header+mau);
    QPrinter printer;
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);//giay nam ngang
    printer.setOutputFileName("file.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);
    QWebView *view = new QWebView();
    view->setHtml(document->toHtml());
    view->print(&printer);
    printer.newPage();
    QMessageBox *thongbao = new QMessageBox();
    thongbao->setText("Tinh nang nay chua hoan thien\n File pdf da luu tai thu muc goc cua chuong trinh.");
    thongbao->show();
    view->~QObject();
#endif
#ifdef __linux
    QMessageBox *thongbao = new QMessageBox();
    thongbao->setText("Tinh nang nay chi su dung tren Windows\n Hay dung tinh nang xem truoc va in");
    thongbao->show();
#endif
}
