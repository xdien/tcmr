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
}

ReportBenhTruyenNhiem::~ReportBenhTruyenNhiem()
{
    delete ui;
}

void ReportBenhTruyenNhiem::on_pushButton_clicked()
{
    QString mau;
    QTextDocument *document = new QTextDocument();
    QTextCursor cursor(document);
    //truyen tr td vao bien conntent
//    for(int i =0;i<item_tinhthanh.rowCount();i++)
//    {

//    }
    cursor.insertHtml(htmltemp->header1+mau);
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
}

bool ReportBenhTruyenNhiem::kiemtraDungHen(int somui, QString mathuoc, QString madc)
{
    query.exec("select * from somuitiem");
}
