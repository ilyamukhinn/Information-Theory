/********************************************************************************
** Form generated from reading UI file 'qr.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QR_H
#define UI_QR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QR
{
public:
    QWidget *centralwidget;
    QPushButton *EncodepushButton;
    QTextEdit *DatatextEdit;
    QLabel *label;
    QPushButton *ExitpushButton;
    QTextBrowser *InfotextBrowser;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QR)
    {
        if (QR->objectName().isEmpty())
            QR->setObjectName(QString::fromUtf8("QR"));
        QR->resize(507, 349);
        centralwidget = new QWidget(QR);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        EncodepushButton = new QPushButton(centralwidget);
        EncodepushButton->setObjectName(QString::fromUtf8("EncodepushButton"));
        EncodepushButton->setGeometry(QRect(30, 191, 212, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(11);
        EncodepushButton->setFont(font);
        DatatextEdit = new QTextEdit(centralwidget);
        DatatextEdit->setObjectName(QString::fromUtf8("DatatextEdit"));
        DatatextEdit->setGeometry(QRect(30, 10, 212, 171));
        DatatextEdit->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 10, 212, 212));
        ExitpushButton = new QPushButton(centralwidget);
        ExitpushButton->setObjectName(QString::fromUtf8("ExitpushButton"));
        ExitpushButton->setGeometry(QRect(30, 248, 212, 51));
        ExitpushButton->setFont(font);
        InfotextBrowser = new QTextBrowser(centralwidget);
        InfotextBrowser->setObjectName(QString::fromUtf8("InfotextBrowser"));
        InfotextBrowser->setGeometry(QRect(260, 230, 212, 68));
        InfotextBrowser->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 294, 465, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(11, 4, 20, 299));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(20, 4, 464, 3));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(475, 4, 20, 299));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(240, 4, 20, 299));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        QR->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QR);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 507, 21));
        QR->setMenuBar(menubar);
        statusbar = new QStatusBar(QR);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QR->setStatusBar(statusbar);

        retranslateUi(QR);

        QMetaObject::connectSlotsByName(QR);
    } // setupUi

    void retranslateUi(QMainWindow *QR)
    {
        QR->setWindowTitle(QCoreApplication::translate("QR", "QR", nullptr));
        EncodepushButton->setText(QCoreApplication::translate("QR", "\320\227\320\260\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        label->setText(QString());
        ExitpushButton->setText(QCoreApplication::translate("QR", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        InfotextBrowser->setHtml(QCoreApplication::translate("QR", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Calibri'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QR: public Ui_QR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QR_H
