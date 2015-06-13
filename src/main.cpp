// PAULO BRUNO DE SOUSA SERAFIM, 2014, Fortaleza - Ce, Brasil

#include <QApplication>
#include <QColor>
#include <QImage>
#include <QLabel>

#include <string>
#include <iostream>
#include <fstream>

#include "SobelOp.h"
#include "CalcPath.h"


#define REP 70
#define VERT 1


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QImage img("icon.png");   // 28x28
    //QImage img("flor.jpg");   // 50x37
    //QImage img("tower.png");  // 274x186
    QImage img("../assets/1l.jpg");     // 400x300
    //QImage img("valve.PNG");  // 640x480
    //QImage img("psg1.jpg");   // 1200x800
    //QImage img("motivation2.jpg");    // 1024x1024
    //QImage img("psg2.jpg");     // 1920x1080


    int H = img.height();
    int W = img.width();

    QImage grayImg(W, H, QImage::Format_RGB32);     // imagem em escala de cinza
    QImage sobelImg(W, H, QImage::Format_RGB32);    // imagem apos aplicacao filtro Sobel
    QImage redImg(W, H, QImage::Format_RGB32);      // imagem com caminho selecionado em vermelho

    IMG_TYPE m[H][W];       // imagem a ser alterada
    unsigned char g[H][W];  // imagem com valores em cinza
    unsigned int c[H][W];   // matriz para ccalculo do caminho



    //****************************************************
    // transformar para escala cinza

    std::ofstream out("img_gray.txt");

    out << W << ' ' << H << '\n';

    for (int h = 0; h < H; ++h)
    {
        for (int w = 0; w < W; ++w)
        {
            int gray = qGray(img.pixel(w,h));
            if (255 <= gray) gray = 254;

            g[h][w] = gray;

            grayImg.setPixel(w,h,qRgb(gray,gray,gray));
            sobelImg.setPixel(w,h,qRgb(gray,gray,gray));

            c[h][w] = 0;
            m[h][w] = gray;

            out << gray << ' ';
        }
        out << '\n';
    }

    // fim transformar para escala cinza
    //****************************************************



    //****************************************************
    // Sobel operator

    sobel_detection(*m, *g, W, H);

    // Imagem com filtro Sobel

    std::ofstream mout("img_sobel.txt");

    for (int h = 0; h < H; ++h)
    {
        for (int w = 0; w < W; ++w)
        {
            sobelImg.setPixel(w,h,qRgb(m[h][w],m[h][w],m[h][w]));
            mout << (int)m[h][w] << ' ';
        }
        mout << '\n';
    }

    // fim Sobel operator
    //****************************************************



    //****************************************************
    // loop principal

    for (int rep = 0; rep < REP; ++rep)
    {
        // VERTICAL
        if (VERT)
        {
            // calcula caminho vertical
            calc_path_ver(*c, *m, W, H);

            // selecionar caminho minimo vertical
            select_path_ver(*m, *c, W, H);
        }
        // HORIZONTAL
        else
        {
            // calcula caminho horizontal
            calc_path_hor(*c, *m, W, H);

            // selecionar caminho minimo horizontal
            select_path_hor(*m, *c, W, H);
        }


        // criar imagem vermelha

        std::ofstream redout("img_red.txt");

        for (int h = 0; h < H; ++h)
        {
            for (int w = 0; w < W; ++w)
            {
                if ( MAX_VALUE == m[h][w] )
                {
                    redImg.setPixel(w,h,qRgb(255,0,0));
                    redout << (int)m[h][w] << ' ';
                }
                else
                {
                    redImg.setPixel(w,h,sobelImg.pixel(w,h));
                    redout << (int)m[h][w] << ' ';
                }
            }
            redout << '\n';
        }
    }

    // fim loop principal
    //***************************************************************



    //***************************************************************
    // imagem recortada

    QImage cutImg;

    // cria imagem recortada vertical
    if (VERT)
    {
        cutImg = QImage(W-REP, H, QImage::Format_RGB32);

        for (int h = 0; h < H; ++h)
        {
            for (int w = 0, wid = 0; w < W; ++w, ++wid)
            {
                if ( MAX_VALUE != m[h][w] )
                {
                    cutImg.setPixel(wid,h,img.pixel(w,h));
                }
                else
                {
                    --wid;
                }
            }
        }
    }
    // cria imagem recortada horizontal
    else
    {
        cutImg = QImage(W, H-REP, QImage::Format_RGB32);

        for (int w = 0; w < W; ++w)
        {
            for (int h = 0, hei = 0; h < H; ++h, ++hei)
            {
                if ( MAX_VALUE != m[h][w] )
                {
                    cutImg.setPixel(w,hei,img.pixel(w,h));
                }
                else
                {
                    --hei;
                }
            }
        }
    }

    // fim imagem recortada
    //***************************************************************



    //***************************************************************
    // Labels

    QLabel labelImg, labelSobel, labelRed, labelCut;

    if (VERT)
    {
        labelImg.setScaledContents(true);
        labelImg.setPixmap(QPixmap::fromImage(img));
        labelImg.resize(W-REP,H);
        labelImg.show();
    }
    else
    {
        labelImg.setScaledContents(true);
        labelImg.setPixmap(QPixmap::fromImage(img));
        labelImg.resize(W,H-REP);
        labelImg.show();
    }

    labelSobel.setScaledContents(true);
    labelSobel.setPixmap(QPixmap::fromImage(sobelImg));
    labelSobel.resize(W,H);
    labelSobel.show();

    labelRed.setScaledContents(true);
    labelRed.setPixmap(QPixmap::fromImage(redImg));
    labelRed.resize(W,H);
    labelRed.show();

    labelCut.setScaledContents(true);
    labelCut.setPixmap(QPixmap::fromImage(cutImg));
    labelCut.resize(cutImg.width(), cutImg.height());
    labelCut.show();

    // fim Labels
    //***************************************************************



    return a.exec();
}
