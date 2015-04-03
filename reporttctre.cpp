#include "reporttctre.h"
#include "ui_reporttctre.h"

#include <QMessageBox>

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
    NCReport *report = new NCReport();
    report->setReportSource( NCReportSource::File ); // set report source type
    //report->addItemModel(querymodel_room,"myModel");
    report->setReportFile("/home/xdien/ProjectsQT/qlsv_ktx/lietkeDSSV.ncr"); //set the report filename fullpath or relative to dir
    report->runReportToPreview(); // run to preview output
    // error handling
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
    delete report;
}
