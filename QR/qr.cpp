#include "qr.h"
#include "ui_qr.h"

QR::QR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QR)
{
    ui->setupUi(this);
    Data = ""; //Введенные данные
    Alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:"; //Алфавит для буквенно-цифрового кодирования
    Encoding_Mode = {0, 0, 0, 0};
    Version = 1; //Версия QR
    Max_Info = {128, 224, 352, 512, 688, 864, 992, 1232, 1456}; //Макимальное кол-во кодируемоей информации для
                                                                //Уровеня коррекции M (15%) и версий 1-9 (в битах)
    Data_Size = {{34, 63, 101, 149, 202, 255, 293, 365, 432}, //Максимальное кол-во входных данных (в байтах)
                 {20, 38, 61, 90, 122, 154, 178, 221, 262}};
    Max_Info_Ec = {10, 16, 26, 18, 24, 16, 18, 22, 22}; //Число байтов коррекции на один блок для 9-ти версий

    //Описание байтов коррекции для различных версий
    Gen_Poly_10 = {251, 67, 46, 61, 118, 70, 64, 94, 32, 45};
    Gen_Poly_16 = {120, 104, 107, 109, 102, 161, 76, 3, 91, 191, 147, 169, 182, 194, 225, 120};
    Gen_Poly_18 = {215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153};
    Gen_Poly_22 = {210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160,
                                105, 165, 231};
    Gen_Poly_24 = {229, 121, 135, 48, 211, 117, 251, 126, 159, 180, 169, 152, 192, 226, 228, 218, 111, 0,
                                117, 232, 87, 96, 227, 21};
    Gen_Poly_26 = {173, 125, 158, 2, 103, 182, 118, 17, 145, 201, 111, 28, 165, 53, 161, 21, 245, 142, 13,
                                102, 48, 227, 153, 145, 218, 70};
    Blocks_Amount = {1, 1, 1, 2, 2, 4, 4, 4, 5}; //Кол-во блоков данных для 9-ти версий
    Galua_Field = {1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143,
                   3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70,
                   140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161, 95, 190, 97, 194, 153, 47, 94, 188,
                   101, 202, 137, 15, 30, 60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182,
                   113, 226, 217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206, 129, 31, 62, 124,
                   248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204, 133, 23, 46, 92, 184, 109, 218, 169, 79, 158,
                   33, 66, 132, 21, 42, 84, 168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115, 230,
                   209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171, 75, 150, 49, 98,
                   196, 149, 55, 110, 220, 165, 87, 174, 65, 130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221,
                   167, 83, 166, 81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9, 18, 36, 72, 144,
                   61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22, 44, 88, 176, 125, 250, 233, 207, 131, 27, 54,
                   108, 216, 173, 71, 142};
    Reverse_Galua_Field = {-1, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75, 4, 100, 224, 14, 52, 141, 239,
                           129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218,
                           240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166, 6,
                           191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150,
                           219, 189, 241, 210, 19, 92, 131, 56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84,
                           250, 133, 186, 61, 202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7,
                           112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184,
                           180, 124, 17, 68, 146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151,
                           178, 220, 252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31,
                           45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157,
                           85, 170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22,
                           235, 122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175};
    Alignment_Info = {{6, 18}, {6, 22}, {6, 26}, {6, 30}, {6, 34},
                      {6, 22, 38}, {6, 24, 42}, {6, 26, 46}};
}

QR::~QR()
{
    delete ui;
}


void QR::on_ReadDatapushButton_clicked()
{
    QFileDialog* File = new QFileDialog();

    QString Filename = File->getOpenFileName();

    QFile input(Filename);
    Data = "";

    if(input.open(QIODevice::ReadOnly))
    {
        Data = input.readAll();
        input.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Не удалось открыть/создать файл.");
        msgBox.exec();

        return;
    }
}

void QR::on_EncodepushButton_clicked()
{
    ui->InfotextBrowser->clear();
    if((Data = ui->DatatextEdit->toPlainText()).length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Введите данные!");
        msgBox.exec();

        return;
    }

    Data = Data.toUpper();

    //Определим способ кодирования
    int Check_mode = 0;
    for(int i = 0; i < Data.length(); i++)
    {
        if(Alphabet.indexOf(Data[i]) == -1)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Введены некорректные данные!");
            msgBox.exec();

            return;
        }

        if(Alphabet.indexOf(Data[i]) >= 0 && Alphabet.indexOf(Data[i]) <= 9)
        {
            Check_mode++;
        }
    }

    Encoding_Mode.fill(false);
    int Encode_ID = 0; //0 - цифровое, 1 - буквенно-цифровое
    if(Check_mode == Data.length())
    {
        Encoding_Mode[3] = 1;
    }
    else
    {
        Encoding_Mode[2] = 1;
        Encode_ID = 1;
    }

    ui->InfotextBrowser->insertPlainText("Длина сообщения: " + QString::number(Data.length()) + " символов(а)");

    if(Data.length() > Data_Size[Encode_ID][Data_Size[Encode_ID].length() - 1])
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Данные слишком велики!\nПрограмма работает с версиями\nQR-кода 1-9.");
        msgBox.exec();

        return;
    }

    //Определение версии QR по кол-ву заданных символов
    Version = 1; //Версия QR
    for(int i = 0; i < 9; i++)
    {
        if(Data.length() > Data_Size[Encode_ID][i])
        {
            Version = i + 2;
        }
    }

    ui->InfotextBrowser->insertPlainText("\nВерсия QR-кода: " + QString::number(Version));

    //Создаем поток данных
    QVector <bool> QR_Stream;
    //Добавляем идентификатор способа кодирования
    QR_Stream.append(Encoding_Mode);
    //Добавляем поле количества данных
    bitset<10> Data_Amount_Bits(Data.length());

    if(Encode_ID == 0)
    {
        for(int i = 9; i >= 0; i--)
        {
            QR_Stream.append(Data_Amount_Bits[i]);
        }
    }
    else
    {
        for(int i = 8; i >= 0; i--)
        {
            QR_Stream.append(Data_Amount_Bits[i]);
        }
    }

    //Разбиваем данные на блоки
    //Для цифрвого - по три символа
    //Для буквенно-цифрового по парам
    if(Encode_ID == 0)
    {
        int remains = Data.length() % 3;
        for(int i = 0; i < Data.length() - remains; i += 3)
        {
            QString num = Data.mid(i, 3);
            bitset<10> Data_Bits(num.toInt());
            for(int j = 9; j >= 0; j--)
            {
                QR_Stream.append(Data_Bits[j]);
            }
        }

        if(remains == 2)
        {
            QString num = Data.right(2);
            bitset<7> Data_Last_Bits(num.toInt());
            for(int j = 6; j >= 0; j--)
            {
                QR_Stream.append(Data_Last_Bits[j]);
            }
        }
        else if(remains == 1)
        {
            QString num = Data.right(1);
            bitset<4> Data_Last_Bits(num.toInt());
            for(int j = 3; j >= 0; j--)
            {
                QR_Stream.append(Data_Last_Bits[j]);
            }
        }
    }
    else
    {
        int remains = Data.length() % 2;
        for(int i = 0; i < Data.length() - remains; i += 2)
        {
            bitset<11> Data_Bits(45 * Alphabet.indexOf(Data[i]) + Alphabet.indexOf(Data[i + 1]));
            for(int j = 10; j >= 0; j--)
            {
                QR_Stream.append(Data_Bits[j]);
            }
        }

        if(remains % 2 == 1)
        {
            bitset<6> Data_Last_Bits(Alphabet.indexOf(Data.right(1)));
            for(int j = 5; j >= 0; j--)
            {
                QR_Stream.append(Data_Last_Bits[j]);
            }
        }
    }

    //Добавим в конец потока битов терминатора <= 4
    if(Max_Info[Version - 1] - QR_Stream.length() < 4)
    {
        int Result_len = QR_Stream.length();
        for(int i = 0; i < (Max_Info[Version - 1] - Result_len); i++)
        {
            QR_Stream.append(false);
        }
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            QR_Stream.append(false);
        }
    }

    //Добавляем нули, если кол-во бит данных не кратна 8-ми
    while(QR_Stream.length() % 8 != 0)
    {
        QR_Stream.append(false);
    }

    QVector <bool> byte_236 = {1, 1, 1, 0, 1, 1, 0, 0};
    QVector <bool> byte_17 = {0, 0, 0, 1, 0, 0, 0, 1};

    //Добавляем байты 236 и 17 по-очереди до полного заполнения требуемого объема данных
    int Result_len = QR_Stream.length();
    for(int i = 0; i < ((Max_Info[Version - 1] - Result_len)/8); i++)
    {
        if(i % 2 == 0)
        {
            QR_Stream.append(byte_236);
        }
        else
        {
            QR_Stream.append(byte_17);
        }
    }

    //Заполним массив с генерирующим многочленом
    QVector <int> Gen_Poly(Max_Info_Ec[Version - 1]);
    switch (Version) {
        case 1:
            Gen_Poly = Gen_Poly_10;
            break;
        case 2:
        case 6:
            Gen_Poly = Gen_Poly_16;
            break;
        case 3:
            Gen_Poly = Gen_Poly_26;
            break;
        case 4:
        case 7:
            Gen_Poly = Gen_Poly_18;
           break;
        case 5:
            Gen_Poly = Gen_Poly_24;
            break;
        case 8:
        case 9:
            Gen_Poly = Gen_Poly_22;
            break;
    }


    //Разделим данные на блоки и рассчитаем байты коррекции
    int block_size = (QR_Stream.length()/8) / Blocks_Amount[Version - 1]; //Размер блоков = N
    int block_remains = (QR_Stream.length()/8) % Blocks_Amount[Version - 1]; //Число блоков с размером N + 1

    QVector <QVector <int>> Data_Blocks;
    QVector <QVector <int>> Ec_Blocks;
    int QR_Stream_index = 0;
    for(int i = 0; i < (Blocks_Amount[Version - 1] - block_remains); i++)
    {
        QVector <int> Data_Block;
        for(int j = 0; j < block_size; j++)
        {
            //перевод из набора бит в байт (число)
            int degree = 7;
            int num = 0;
            for(int k = 7; k >= 0; k--)
            {
                if(QR_Stream[QR_Stream_index] == 1)
                {
                    num += pow(2, degree);
                }
                degree--;
                QR_Stream_index++;
            }
            Data_Block.append(num);
        }
        Data_Blocks.append(Data_Block);

        //Подготовим вектор байтов, где первые block_size элементов -
        //байты данных, остальные (если кол-во байтов коррекции
        //> block_size) - нули
        QVector <int> temp_vector;

        for(int j = 0; j < fmax(block_size, Gen_Poly.length()); j++)
        {
            if(j < block_size)
            {
                temp_vector.append(Data_Block[j]);
            }
            else
            {
                temp_vector.append(0);
            }
        }

        for(int j = 0; j < block_size; j++)
        {
            int A = temp_vector[0];
            temp_vector.remove(0);
            temp_vector.append(0);
            if(A != 0)
            {
                int B = Reverse_Galua_Field[A];
                for(int k = 0; k < Gen_Poly.length(); k++)
                {
                    int C = (Gen_Poly[k] + B) % 255;
                    temp_vector[k] ^= Galua_Field[C];
                }
            }
        }

        QVector <int> Ec_Block;
        for(int j = 0; j < Gen_Poly.length(); j++)
        {
            Ec_Block.append(temp_vector[j]);
        }
        Ec_Blocks.append(Ec_Block);

    }

    for(int i = (Blocks_Amount[Version - 1] - block_remains); i < Blocks_Amount[Version - 1]; i++)
    {
        QVector <int> Data_Block;
        for(int j = 0; j < block_size + 1; j++)
        {
            //перевод из набора бит в байт (число)
            int degree = 7;
            int num = 0;
            for(int k = 7; k >= 0; k--)
            {
                if(QR_Stream[QR_Stream_index] == 1)
                {
                    num += pow(2, degree);
                }
                degree--;
                QR_Stream_index++;
            }
            Data_Block.append(num);
        }
        Data_Blocks.append(Data_Block);

        //Подготовим вектор байтов, где первые block_size элементов -
        //байты данных, остальные (если кол-во байтов коррекции
        //> block_size) - нули
        QVector <int> temp_vector;

        for(int j = 0; j < fmax(block_size + 1, Gen_Poly.length()); j++)
        {
            if(j < block_size + 1)
            {
                temp_vector.append(Data_Block[j]);
            }
            else
            {
                temp_vector.append(0);
            }
        }

        for(int j = 0; j < block_size + 1; j++)
        {
            int A = temp_vector[0];
            temp_vector.remove(0);
            temp_vector.append(0);
            if(A != 0)
            {
                int B = Reverse_Galua_Field[A];
                for(int k = 0; k < Gen_Poly.length(); k++)
                {
                    int C = (Gen_Poly[k] + B) % 255;
                    temp_vector[k] ^= Galua_Field[C];
                }
            }
        }

        QVector <int> Ec_Block;
        for(int j = 0; j < Gen_Poly.length(); j++)
        {
            Ec_Block.append(temp_vector[j]);
        }
        Ec_Blocks.append(Ec_Block);
    }

    //Запишем байты данных и байты коррекции в один поток
    QVector <int> QR_Result;

    for(int i = 0; i < block_size + 1; i++)
    {
        for(int j = 0; j < Data_Blocks.length(); j++)
        {
            if(Data_Blocks[j].length() != 0)
            {
                QR_Result.append(Data_Blocks[j][0]);
                Data_Blocks[j].remove(0);
            }
        }
    }

    for(int i = 0; i < Max_Info_Ec[Version - 1]; i++)
    {
        for(int j = 0; j < Ec_Blocks.length(); j++)
        {
            QR_Result.append(Ec_Blocks[j][i]);
        }
    }

    //Переводим байты в биты
    QVector <bool> QR_Result_Bits;
    for(int i = 0; i < QR_Result.length(); i++)
    {
        bitset<8> temp_bits(QR_Result[i]);
        for(int j = 7; j >= 0; j--)
        {
            QR_Result_Bits.append(temp_bits[j]);
        }
    }

    //Добавим 7 остаточных битов, если версия от 2-х до 6-ти
    if(Version >= 2 && Version <= 6)
    {
        for(int i = 0; i < 7; i++)
        {
            QR_Result_Bits.append(false);
        }
    }

    //Считаем высоту и ширину изображения по модулям
    int width = 17 + 4 * Version;
    int height = width;

    //Создаем матрицу, которую будем выводить на холст
    QVector <QVector <int>> QR_Matrix;
    QR_Matrix.resize(height);
    for(int i = 0; i < QR_Matrix.length(); i++)
    {
        QR_Matrix[i].resize(width);
        QR_Matrix[i].fill(2); //2 - пустые модули
    }

    //Обозначим шаблоны поиска и разделители
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //Шаблон поиска сверху слева
            if((i >= 0) && (i < 7) && (j >= 0) && (j < 7))
            {
                if((i > 0) && (i < 6) && (j > 0) && (j < 6))
                {
                    if(!((i > 1) && (i < 5) && (j > 1) && (j < 5)))
                    {
                        QR_Matrix[i][j] = 1;
                    }
                    else
                    {
                        QR_Matrix[i][j] = 0;
                    }
                }
                else
                {
                    QR_Matrix[i][j] = 0;
                }
            }
            //Разделитель для верхнеого левого шаблона поиска
            if((i >= 0) && (i < 8) && (j == 7))
            {
                QR_Matrix[i][j] = 1;
            }
            if((i == 7) && (j >= 0) && (j < 8))
            {
                QR_Matrix[i][j] = 1;
            }
            //Шаблон поиска сверху справа
            if((i >= 0) && (i < 7) && (j >= width - 7) && (j < width))
            {
                if((i > 0) && (i < 6) && (j > width - 7) && (j < width - 1))
                {
                    if(!((i > 1) && (i < 5) && (j > width - 6) && (j < width - 2)))
                    {
                        QR_Matrix[i][j] = 1;
                    }
                    else
                    {
                        QR_Matrix[i][j] = 0;
                    }
                }
                else
                {
                    QR_Matrix[i][j] = 0;
                }
            }
            //Разделитель для верхнего правого шаблона поиска
            if((i >= 0) && (i < 8) && (j == width - 8))
            {
                QR_Matrix[i][j] = 1;
            }
            if((i == 7) && (j >= width - 8) && (j < width))
            {
                QR_Matrix[i][j] = 1;
            }
            //Шаблон поиска снизу слева
            if((i >= height - 7) && (i < height) && (j >= 0) && (j < 7))
            {
                if((i > height - 7) && (i < height - 1) && (j > 0) && (j < 6))
                {
                    if(!((i > height - 6) && (i < height - 2) && (j > 1) && (j < 5)))
                    {
                        QR_Matrix[i][j] = 1;
                    }
                    else
                    {
                        QR_Matrix[i][j] = 0;
                    }
                }
                else
                {
                    QR_Matrix[i][j] = 0;
                }
            }
            //Разделитель для нижнего левого шаблона поиска
            if((i >= height - 8) && (i < height) && (j == 7))
            {
                QR_Matrix[i][j] = 1;
            }
            if((i == height - 8) && (j >= 0) && (j < 8))
            {
                QR_Matrix[i][j] = 1;
            }
        }
    }

    //Добавление шаблонов выравнивания
    if(Version >= 2)
    {
        QVector <int> temp_Alignment = Alignment_Info[Version - 2];
        for(int i = 0; i < Alignment_Info[Version - 2].length(); i++)
        {
            for(int j = 0; j < temp_Alignment.length(); j++)
            {
                if(!(((i == 0) && (j == 0)) ||
                     ((i == Alignment_Info[Version - 2].length() - 1) && (j == 0)) ||
                     ((i == 0) && (j == temp_Alignment.length() - 1))))
                {
                    for(int k = temp_Alignment[i] - 2; k < temp_Alignment[i] + 3; k++)
                    {
                        for(int p = temp_Alignment[j] - 2; p < temp_Alignment[j] + 3; p++)
                        {
                            if((k > temp_Alignment[i] - 2) && (k < temp_Alignment[i] + 2) &&
                                    (p > temp_Alignment[j] - 2) && (p < temp_Alignment[j] + 2))
                            {
                                QR_Matrix[k][p] = 1;
                            }
                            else
                            {
                                QR_Matrix[k][p] = 0;
                            }
                        }
                    }
                    QR_Matrix[Alignment_Info[Version - 2][i]][temp_Alignment[j]] = 0;
                }
            }
        }
    }

    //Добавляем timing patterns (временные шаблоны)
    for(int i = 8; i < height - 8; i++)
    {
        if(i % 2 == 0)
        {
            QR_Matrix[i][6] = 0;
        }
        else
        {
            QR_Matrix[i][6] = 1;
        }
    }

    for(int j = 8; j < width - 8; j++)
    {
        if(j % 2 == 0)
        {
            QR_Matrix[6][j] = 0;
        }
        else
        {
            QR_Matrix[6][j] = 1;
        }
    }

    //Добавляем один черный модуль
    QR_Matrix[height - 8][8] = 0;
    //Добавим индикатор маски
    QVector <bool> Mask_bits = {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0};
    int mask_index = 0;
    //Для верхнего левого края
    mask_index = Mask_bits.length() - 1;
    for(int i = 0; i < 9; i++)
    {
        if(i != 6)
        {
            QR_Matrix[i][8] = !Mask_bits[mask_index];
            mask_index--;
        }
    }
    mask_index = 0;
    for(int j = 0; j < 9; j++)
    {
        if(j != 6)
        {
            QR_Matrix[8][j] = !Mask_bits[mask_index];
            mask_index++;
        }
    }
    //Для вехнего правого края
    mask_index--;
    for(int j = width - 8; j < width; j++)
    {
        QR_Matrix[8][j] = !Mask_bits[mask_index];
        mask_index++;
    }
    //Для нижнего левого края
    mask_index = 0;
    for(int i = height - 1; i >= height - 7; i--)
    {
        QR_Matrix[i][8] = !Mask_bits[mask_index];
        mask_index++;
    }

    //Добавим информацию о версии QR кода
    QVector <QVector <bool>> Versions_Info = {{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
                                              {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
                                              {0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1}};
    if(Version >= 7)
    {
        //Для верхнего правого края
        int Version_index = Versions_Info[Version - 7].length() - 1;
        for(int i = 0; i < 6; i++)
        {
            for(int j = width - 11; j < width - 8; j++)
            {
                QR_Matrix[i][j] = !Versions_Info[Version - 7][Version_index];
                Version_index--;
            }
        }
        //Для нижнего левого края
        Version_index = Versions_Info[Version - 7].length() - 1;
        for(int j = 0; j < 6; j++)
        {
            for(int i = height - 11; i < height - 8; i++)
            {
                QR_Matrix[i][j] = !Versions_Info[Version - 7][Version_index];
                Version_index--;
            }
        }
    }

    //Запишем биты данных в матрицу
    int QR_Result_Bits_index = 0;
    bool up = true;
    for(int j = width - 1; j >= 0; j -= 2)
    {
        if(j == 6)
        {
            j--;
        }

        if(up)
        {
            for(int i = height - 1; i >= 0; i--)
            {
                if(QR_Matrix[i][j] == 2 && QR_Matrix[i][j - 1] == 2)
                {
                    if((i + j) % 2 == 0)
                    {
                        QR_Matrix[i][j] = QR_Result_Bits[QR_Result_Bits_index];
                    }
                    else
                    {
                        QR_Matrix[i][j] = !QR_Result_Bits[QR_Result_Bits_index];
                    }

                    if((i + j - 1) % 2 == 0)
                    {
                        QR_Matrix[i][j - 1] = QR_Result_Bits[QR_Result_Bits_index + 1];
                    }
                    else
                    {
                        QR_Matrix[i][j - 1] = !QR_Result_Bits[QR_Result_Bits_index + 1];
                    }

                    QR_Result_Bits_index += 2;

                }
                else if(QR_Matrix[i][j] == 2 && QR_Matrix[i][j - 1] != 2)
                {
                    if((i + j) % 2 == 0)
                    {
                        QR_Matrix[i][j] = QR_Result_Bits[QR_Result_Bits_index];
                    }
                    else
                    {
                        QR_Matrix[i][j] = !QR_Result_Bits[QR_Result_Bits_index];
                    }
                    QR_Result_Bits_index++;
                }
                else if(QR_Matrix[i][j] != 2 && QR_Matrix[i][j - 1] == 2)
                {
                    if((i + j - 1) % 2 == 0)
                    {
                        QR_Matrix[i][j - 1] = QR_Result_Bits[QR_Result_Bits_index];
                    }
                    else
                    {
                        QR_Matrix[i][j - 1] = !QR_Result_Bits[QR_Result_Bits_index];
                    }
                    QR_Result_Bits_index++;
                }
            }
            up = false;
        }
        else
        {
            for(int i = 0; i < height; i++)
            {
                if(QR_Matrix[i][j] == 2 && QR_Matrix[i][j - 1] == 2)
                {
                    if((i + j) % 2 == 0)
                    {
                        QR_Matrix[i][j] = QR_Result_Bits[QR_Result_Bits_index];
                    }
                    else
                    {
                        QR_Matrix[i][j] = !QR_Result_Bits[QR_Result_Bits_index];
                    }

                    if((i + j - 1) % 2 == 0)
                    {
                        QR_Matrix[i][j - 1] = QR_Result_Bits[QR_Result_Bits_index + 1];
                    }
                    else
                    {
                        QR_Matrix[i][j - 1] = !QR_Result_Bits[QR_Result_Bits_index + 1];
                    }
                    QR_Result_Bits_index += 2;
                }
                else if(QR_Matrix[i][j] == 2 && QR_Matrix[i][j - 1] != 2)
                {
                    if((i + j) % 2 == 0)
                    {
                        QR_Matrix[i][j] = QR_Result_Bits[QR_Result_Bits_index];
                    }
                    else
                    {
                        QR_Matrix[i][j] = !QR_Result_Bits[QR_Result_Bits_index];
                    }
                    QR_Result_Bits_index++;
                }
                else if(QR_Matrix[i][j] != 2 && QR_Matrix[i][j - 1] == 2)
                {
                    if((i + j - 1) % 2 == 0)
                    {
                        QR_Matrix[i][j - 1] = QR_Result_Bits[QR_Result_Bits_index];
                    }
                    else
                    {
                        QR_Matrix[i][j - 1] = !QR_Result_Bits[QR_Result_Bits_index];
                    }
                    QR_Result_Bits_index++;
                }
            }
            up = true;
        }
    }

    FILE *fp = fopen("qr.png", "wb");

    unsigned char header[62] =   {0x42, 0x4d, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36,
                                  0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
                                  0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0xff, 0xff, 0xff, 0x00};

    header[22] = header[18] = width;
    // Выделение рамки
    header[22] = header[18] += 16;
    int width_actual_margin = ((header[18] + 31) - (header[18] + 31) % 32) / 8;

    // Вычисление байтов
    int length_margin = header[22] * width_actual_margin;
    header[35] = length_margin >> 8;
    header[34] = length_margin;

    unsigned char* qr = new unsigned char[length_margin];
    for(int i = 0; i < header[22]; i++)
    {
        for(int j = 0; j < width_actual_margin; j++)
        {
            qr[i*width_actual_margin + j] = 0xff;
        }
    }

    matrix_to_bytes(QR_Matrix, height, width, qr, length_margin, header[22]);

    for(int i = 0; i < 62; i++)
    {
        fwrite(&header[i], sizeof(char), 1, fp);
    }
    // Рамка сверху
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < width_actual_margin; j++)
        {
            unsigned char margin_byte = 0xff;
            fwrite(&margin_byte, sizeof(char), 1, fp);
        }
    }
    for(int i = height-1; i >= 0; i--)
    {
        unsigned char margin_byte = 0xff;
        fwrite(&margin_byte, sizeof(char), 1, fp);
        for(int j = 0; j < width_actual_margin-1; j++)
        {
            fwrite(&qr[i * width_actual_margin + j], sizeof(char), 1, fp);
        }
    }
    // Рамка снизу
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < width_actual_margin; j++)
        {
            unsigned char margin_byte = 0xff;
            fwrite(&margin_byte, sizeof(char), 1, fp);
        }
    }
    fclose(fp);

    QPixmap img("qr.png");
    QSize img_size(212, 212);
    img = img.scaled(img_size, Qt::KeepAspectRatio);
    ui->label->setPixmap(img);
}

void QR::matrix_to_bytes(QVector <QVector <int>> QR_Matrix, int h, int w, unsigned char* Result, int length, int height_actual) {
    int index, byte_num, width_actual = length / height_actual;
    unsigned char temp_byte;

    for(int i = 0; i < h; i++)
    {
        byte_num = 0;
        index = 0;
        temp_byte = 0; // Заполняем байт

        for(int j = 0; j < w; j++)
        {
            index++; // Номер бита
            if((bool)QR_Matrix[i][j])
            {
                temp_byte |= 1;
            }
            if(index == 8)
            {
                index = 0;
                Result[byte_num + width_actual * i] = temp_byte; // Сохраняем в массиве
                temp_byte = 0;
                byte_num++;
            }
            else
            {
                temp_byte <<= 1;
            }
        }
        if(index != 0)
        {
            temp_byte <<= 7 - index;
            int pos = 1;

            for(int j = 0; j <= 7 - index; j++)
            {
                temp_byte |= pos;
                pos *= 2;
            }
            Result[byte_num + width_actual * i] = temp_byte; // Сохраняем в массиве то, что набралось
        }
    }
}

void QR::on_ExitpushButton_clicked()
{
    this->close();
}

void QR::on_DatatextEdit_textChanged()
{
    ui->InfotextBrowser->clear();
    QString temp_Data = ui->DatatextEdit->toPlainText();
    QString Message = "Длина сообщения: " + QString::number(temp_Data.length()) + " символов(а).";

    if(temp_Data.length() == 0)
    {
        ui->InfotextBrowser->setText(Message);
        return;
    }

    temp_Data = temp_Data.toUpper();

    int Check_mode = 0;
    for(int i = 0; i < temp_Data.length(); i++)
    {
        if(Alphabet.indexOf(temp_Data[i]) == -1)
        {
            ui->InfotextBrowser->setText("Введены некорректные данные!");
            return;
        }

        if(Alphabet.indexOf(temp_Data[i]) >= 0 && Alphabet.indexOf(temp_Data[i]) <= 9)
        {
            Check_mode++;
        }
    }

    Encoding_Mode.fill(false);
    int Encode_ID = 0; //0 - цифровое, 1 - буквенно-цифровое
    if(Check_mode != temp_Data.length())
    {
        Encode_ID = 1;
    }

    if(temp_Data.length() > Data_Size[Encode_ID][Data_Size[Encode_ID].length() - 1])
    {
        ui->InfotextBrowser->insertPlainText(" Данные слишком велики! Программа работает с версиями QR-кода 1-9.");
        return;
    }

    //Определение версии QR по кол-ву заданных символов
    int temp_Version = 1; //Версия QR
    for(int i = 0; i < 9; i++)
    {
        if(temp_Data.length() > Data_Size[Encode_ID][i])
        {
            temp_Version = i + 2;
        }
    }

    ui->InfotextBrowser->setText(Message + "\nВерсия QR-кода: " + QString::number(temp_Version));

}
