#ifndef QR_H
#define QR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QBitArray>
#include <bitset>
#include <math.h>
#include <QPainter>
#include <fstream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class QR; }
QT_END_NAMESPACE

class QR : public QMainWindow
{
    Q_OBJECT

public:
    QR(QWidget *parent = nullptr);
    ~QR();

    void matrix_to_bytes(QVector <QVector <int>>ask, int h, int w, unsigned char*res, int length, int height_actual);

private slots:
    void on_ReadDatapushButton_clicked();

    void on_EncodepushButton_clicked();

    void on_ExitpushButton_clicked();

    void on_DatatextEdit_textChanged();

private:
    QVector <int> Max_Info;
    QVector <int> Gen_Poly_10;
    QVector <int> Gen_Poly_16;
    QVector <int> Gen_Poly_18;
    QVector <int> Gen_Poly_22;
    QVector <int> Gen_Poly_24;
    QVector <int> Gen_Poly_26;
    QVector <int> Max_Info_Ec;
    int Version;
    QVector <QVector <int>> Data_Size;
    QString Data;
    QVector <bool> Encoding_Mode;
    QVector <int> Blocks_Amount;
    QString Alphabet;
    QVector <int> Galua_Field;
    QVector <int> Reverse_Galua_Field;
    QVector <QVector <int>> Alignment_Info;
    Ui::QR *ui;
};
#endif // QR_H
