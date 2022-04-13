#include "mainwindow.h"
#include<hakkinda.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSize screenSize = qApp->screens()[0]->size();
    boy=screenSize.height()/153.6;
    //qDebug()<<boy;
    fontsize=boy*7;
    radius=boy*5;
    this->setFixedSize(120*boy,120*boy);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
    this->setWindowTitle("e-carp");
    auto appIcon = QIcon(":/icons/e-carp.svg");
    this->setWindowIcon(appIcon);

    statusLabel=new QLabel(this);
    statusLabel->setFixedSize(this->width(),boy*5);
    statusLabel->move(0,this->height()-statusLabel->height());
    statusLabel->setText("Yeni Oyun Başlatın..");


    winplayer = new QMediaPlayer();
    winplayer->setVolume(70);
    winplayer->setMedia(QUrl::fromLocalFile("/usr/share/e-carp/win.mp3"));

    clickplayer = new QMediaPlayer();
    clickplayer->setVolume(70);
    clickplayer->setMedia(QUrl::fromLocalFile("/usr/share/e-carp/click.mp3"));




/**********************************************************************/
    QPixmap newhumanhumanpix(":/icons/humanhuman.svg");
    QPixmap newpchumanpix(":/icons/pchuman.svg");

    QPixmap aboutpix(":/icons/about.svg");
    QPixmap quitpix(":/icons/close.svg");

    QToolBar *toolbar = addToolBar("main toolbar");
    QAction *newgamepchuman=toolbar->addAction(QIcon(newpchumanpix), "Pc-İnsan");
    QAction *newgamehumanhuman=toolbar->addAction(QIcon(newhumanhumanpix), "İnsan-İnsan");

    QAction *hak=toolbar->addAction(QIcon(aboutpix), "Hakkında");
    toolbar->addSeparator();
    QAction *quit = toolbar->addAction(QIcon(quitpix),"Çık");
    connect( newgamepchuman, SIGNAL(triggered()), this, SLOT(newGamePcHuman()));
    connect( newgamehumanhuman, SIGNAL(triggered()), this, SLOT(newGameHumanHuman()));
    connect( hak, SIGNAL(triggered()), this, SLOT(about()));
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
//newGame();

    QPixmap pic(":/icons/e-carp.svg");
    back=new QLabel(this);

    back->setFixedSize(this->width()-boy*20,this->width()-boy*20);
    back->move(this->width()/2-back->width()/2,this->height()/2-back->height()/2);

    back->setPixmap(pic);
    back->setScaledContents(true);


}
void   MainWindow::about(){
    QSize screenSize = qApp->screens()[0]->size();
   // qDebug()<<screenSize.width()/65<<screenSize.height()/35;

    QWidget *hk=hakkinda();

    hk->show();
    hk->move(screenSize.width()/2-hk->width()/2,screenSize.height()/2-hk->height()/2);
     hk->setWindowTitle("e-carp");
     auto appIcon = QIcon(":/icons/about.svg");
     hk->setWindowIcon(appIcon);



}
void  MainWindow::newGamePcHuman()
{
    back->hide();
    newGameKind=true;
    gameFinishStatus=false;
    if(newGameStatus==true)
    {
        for(int i=0;i<=8;i++)
        {
            delete player1[i];
            delete player2[i];
        }

        for(int i=0;i<=35;i++)
        {

                delete butonSayilarListe[i];


        }
        delete slw;
        delete ap1;
        delete ap2;

    }
    selectNumberPlayer1=0;
    selectNumberPlayer2=0;
    sonuc=0;

    slw=sayiListeWidget();  slw->show();
    ap1=addPlayer1();       ap1->show();
    ap2=addPlayer2();       ap2->show();
    newGameStatus=true;
    statusLabel->setText("Oyun Başladı..");

    player1AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
       player1[j-1]->setEnabled(true);
       player1AutoSelectList.append(j);
    }
    player1AutoSelectClick();




}

void  MainWindow::newGameHumanHuman()
{
    back->hide();
    newGameKind=false;
    gameFinishStatus=false;

    if(newGameStatus==true)
    {
        for(int i=0;i<=8;i++)
        {
            delete player1[i];
            delete player2[i];
        }

        for(int i=0;i<=35;i++)
        {

                delete butonSayilarListe[i];


        }
        delete slw;
        delete ap1;
        delete ap2;

    }
    selectNumberPlayer1=0;
    selectNumberPlayer2=0;
    sonuc=0;

    slw=sayiListeWidget();  slw->show();
    ap1=addPlayer1();       ap1->show();
    ap2=addPlayer2();       ap2->show();
    newGameStatus=true;
    statusLabel->setText("Oyun Başladı..");

    player1AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
       player1[j-1]->setEnabled(true);
       player1AutoSelectList.append(j);
    }


}


QWidget* MainWindow::sayiListeWidget()
{
    butonSayilarListe.clear();

     addSayiListe();/// sayilar eklendi
   auto widget = new QWidget(this);
     auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);

    for(int i=0;i<=5;i++)
    {
        for(int j=0;j<=5;j++)
        {
            QToolButton *btn=new QToolButton();
            btn->setText(QString::number(sayiSec()));
            btn->setToolTip("0");
            matrix[i][j].number=btn->text().toInt();
            matrix[i][j].player=0;
            btn->setFixedSize(boy*12,boy*12);
            btn->setStyleSheet("QToolButton{background-color:rgba(200,200,200,200);"
                               "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                               "font-weight: 400;font-size:"+QString::number(fontsize)+"px;}");

            butonSayilarListe.append(btn);
            layout->addWidget(btn,i,j,1,1);
        }
    }
    widget->setFixedSize(80*boy-boy*2,80*boy-boy*2);
   // widget->setStyleSheet("background-color:rgba(0,200,0,50);border: 1px solid gray;border-radius: 5px;");
    widget->move(this->width()/2-widget->width()/2,this->height()/2-widget->height()/2);


    return widget;
}


QWidget* MainWindow::addPlayer1()
{

    player1.clear();
   auto widget = new QWidget(this);
     auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);

    for(int j=1;j<=9;j++)
    {
        QToolButton *btn=new QToolButton(widget);
       // int islem=i*j;
        btn->setText(QString::number(j));
        btn->setFixedSize(8*boy,8*boy);
        btn->setStyleSheet("QToolButton{background-color:rgba(200,200,200,200);"
                           "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                           "font-weight: 400;font-size:"+QString::number(fontsize)+"px;}");

        connect(btn, &QToolButton::clicked, [=]() {
           player1Click(btn->text().toInt());
           });


        player1.append(btn);
        layout->addWidget(btn, j,0,1,1);

    }
    widget->setFixedSize(10*boy,80*boy-boy*2);
    widget->setObjectName("player1");
   // widget->setStyleSheet("QWidget#player1{background-color:rgba(0,200,0,50);border: 1px solid gray;border-radius: 5px;}");
    widget->move(boy*2,this->height()/2-widget->height()/2);

    return widget;
}

QWidget* MainWindow::addPlayer2()
{
    player2.clear();
   auto widget = new QWidget(this);
     auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);

    for(int j=1;j<=9;j++)
    {
        QToolButton *btn=new QToolButton(widget);
       // int islem=i*j;
        btn->setText(QString::number(j));
         btn->setFixedSize(8*boy,8*boy);
         btn->setStyleSheet("QToolButton{background-color:rgba(200,200,200,200);"
                            "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                            "font-weight: 400;font-size:"+QString::number(fontsize)+"px;}");

        connect(btn, &QToolButton::clicked, [=]() {
          player2Click(btn->text().toInt());
           });
        player2.append(btn);
        layout->addWidget(btn, j,0,1,1);


    }
    widget->setFixedSize(10*boy,80*boy-boy*2);
     widget->setObjectName("player2");
   // widget->setStyleSheet("QWidget#player2{background-color:rgba(0,200,0,50);border: 1px solid gray;border-radius: 5px;}");

    widget->move(this->width()-boy*12,this->height()/2-widget->height()/2);

    return widget;
}

void  MainWindow::player1Click(int btnnumber)
{
    if(gameFinishStatus==true) return;
    for(int i=1;i<=9;i++)
    {
       player1[i-1]->setStyleSheet("background-color:rgba(200,200,200,200);"
                                   "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                   "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");

    }


        player1[btnnumber-1]->setStyleSheet("background-color:rgba(0,0,200,100);"
                                            "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                            "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
       // qDebug()<<player1[btnnumber-1]->text().toInt();
        selectNumberPlayer1=player1[btnnumber-1]->text().toInt();
        ap1->setEnabled(false);
        ap2->setEnabled(true);
        if(selectNumberPlayer1!=0&&selectNumberPlayer2!=0)
        {
            for(int i=1;i<=9;i++)
            {
                player2[i-1]->setStyleSheet("background-color:rgba(200,200,200,200);"
                                            "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                            "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");

            }
            sonuc=selectNumberPlayer1*selectNumberPlayer2;

            selectNumberPlayer2=0;
            sayiListeSelect(sonuc,1);


        }
         clickplayer->play();


}
void  MainWindow::player2Click(int btnnumber)
{
    if(gameFinishStatus==true) return;

    for(int i=1;i<=9;i++)
    {
       player2[i-1]->setStyleSheet("background-color:rgba(200,200,200,200);"
                                   "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                   "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");

    }
    player2[btnnumber-1]->setStyleSheet("background-color:rgba(200,0,0,100);"
                                        "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                        "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");

   // qDebug()<<btn->text();
    selectNumberPlayer2=player2[btnnumber-1]->text().toInt();
    ap1->setEnabled(true);
    ap2->setEnabled(false);
    if(selectNumberPlayer1!=0&&selectNumberPlayer2!=0)
    {
        for(int i=1;i<=9;i++)
        {
           player1[i-1]->setStyleSheet("background-color:rgba(200,200,200,200);"
                                       "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                       "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
        }
        sonuc=selectNumberPlayer1*selectNumberPlayer2;

        selectNumberPlayer1=0;
        sayiListeSelect(sonuc,2);

    }

     clickplayer->play();

}

void MainWindow::sayiListeSelect(int sy,int player)
{


   for(int i=0;i<butonSayilarListe.count();i++)
   {
      if(butonSayilarListe[i]->text().toInt()==sy&&player==1)
      {
          butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,200,50);"
                                              "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                              "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
          butonSayilarListe[i]->setToolTip(QString::number(player));
          //qDebug()<<"sonuc:"<<sy<<player<<butonSayilarListe[i]->toolTip();
          matrixMarker(sy,player);
          player2Disable(sy);
          player1WinControl();


      }
      if(butonSayilarListe[i]->text().toInt()==sy&&player==2)
      {
          butonSayilarListe[i]->setStyleSheet("background-color:rgba(200,0,0,50);"
                                              "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                              "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
          butonSayilarListe[i]->setToolTip(QString::number(player));
         // qDebug()<<"sonuc:"<<sy<<player<<butonSayilarListe[i]->toolTip();
          matrixMarker(sy,player);
          player1Disable(sy);
          player2WinControl();

         if(newGameKind==true) player1AutoSelectClick();

      }

   }

}
void MainWindow::player1AutoSelectClick()
{
    // player1Click(5);
     srand (time(NULL));
     int randomNumber = rand() % player1AutoSelectList.count() + 1;//1-9 random size sayiListe.count()=36
    // qDebug()<<"auto select player1 number:"<<randomNumber<<player1AutoSelectList.count()<<player1AutoSelectList<<player1AutoSelectList[randomNumber-1];
    // player1Click(player1[player1AutoSelectList[randomNumber-1]-1]->text().toInt());
     //  player1Click(5);
     for(int i=0;i<9;i++)
     {
      if(player1[i]->text().toInt()==player1AutoSelectList[randomNumber-1])
      {
          //player1AutoSelectList.removeAt(i);
         // qDebug()<<"auto select player1 number:"<<player1[i]->text().toInt();
           player1Click(player1[i]->text().toInt());
      }
     }
}
void MainWindow::player1Disable(int number)
{
    player1AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
       player1[j-1]->setEnabled(true);
       player1AutoSelectList.append(j);
    }

    for(int k=0;k<butonSayilarListe.count();k++)
    {
        if(butonSayilarListe[k]->toolTip()!="0")
        {
            //qDebug()<<"select:"<<butonSayilarListe[k]->text()<<selectNumberPlayer2;
            for(int j=1;j<=9;j++)
            {
                if(butonSayilarListe[k]->text().toInt()==j*selectNumberPlayer2)
                {
                    player1[j-1]->setEnabled(false);
                   /***************************seçim**************************/
                    for(int i=0;i<player1AutoSelectList.count();i++)
                    {
                     if(player1AutoSelectList[i]==player1[j-1]->text().toInt())player1AutoSelectList.removeAt(i);
                    }
                    /******************************************************/

                }

            }
        }
    }

}
void MainWindow::player2Disable(int number)
{
    player2AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
       player2[j-1]->setEnabled(true);
    }

    for(int k=0;k<butonSayilarListe.count();k++)
    {
        if(butonSayilarListe[k]->toolTip()!="0")
        {
           // qDebug()<<"select:"<<butonSayilarListe[k]->text()<<selectNumberPlayer1;
            for(int j=1;j<=9;j++)
            {
                if(butonSayilarListe[k]->text().toInt()==j*selectNumberPlayer1)
                {
                    player2[j-1]->setEnabled(false);
                    player2AutoSelectList.append(j-1);
                }

            }
        }
    }


}
void MainWindow::addSayiListe()
{
    sayiListe.append(1); sayiListe.append(2); sayiListe.append(3); sayiListe.append(4);
    sayiListe.append(5); sayiListe.append(6); sayiListe.append(7); sayiListe.append(8);
    sayiListe.append(9); sayiListe.append(10); sayiListe.append(12); sayiListe.append(14);
    sayiListe.append(15);sayiListe.append(16); sayiListe.append(18); sayiListe.append(20);
    sayiListe.append(21);sayiListe.append(24); sayiListe.append(25); sayiListe.append(27);
    sayiListe.append(28);sayiListe.append(30); sayiListe.append(32); sayiListe.append(35);
    sayiListe.append(36);sayiListe.append(40); sayiListe.append(42); sayiListe.append(45);
    sayiListe.append(48);sayiListe.append(49); sayiListe.append(54); sayiListe.append(56);
    sayiListe.append(63);sayiListe.append(64);sayiListe.append(72); sayiListe.append(81);
    sayiListe1=sayiListe;
}

int MainWindow::sayiSec()
{
    srand (time(NULL));
    int randomNumber = rand() % sayiListe.count() + 1;//1-36 random size sayiListe.count()=36
   // qDebug()<<"rastgelesayi"<<randomNumber<<sayiListe.count();
    int temp=sayiListe[randomNumber-1];
    sayiListe.removeAt(randomNumber-1);
    return temp;
}
void MainWindow::matrixMarker(int number,int player)
{
   for(int i=0;i<=5;i++)
   {
       for(int j=0;j<=5;j++)
       {
          // qDebug()<<matrix[i][j];
           if(matrix[i][j].number==number)
               matrix[i][j].player=player;
       }

   }
}
void MainWindow::player1WinControl()
 {
    int player=1;
     bool status=false;
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=4;j++)
        {
            //ust-orta-alt
           if(matrix[i][j].player==matrix[i-1][j].player&&
                   matrix[i][j].player==matrix[i+1][j].player&&
                   matrix[i][j].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][j].number,matrix[i-1][j].number,matrix[i+1][j].number,player);
           }
            //ustsol-orta-altsag
           if(matrix[i][j].player==matrix[i-1][j-1].player&&
                   matrix[i][j].player==matrix[i+1][j+1].player&&
                   matrix[i][j].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][j].number,matrix[i-1][j-1].number,matrix[i+1][j+1].number,player);
           }
             //ustsag-orta-altsol
           if(matrix[i][j].player==matrix[i-1][j+1].player&&
                   matrix[i][j].player==matrix[i+1][j-1].player&&
                   matrix[i][j].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][j].number,matrix[i-1][j+1].number,matrix[i+1][j-1].number,player);
           }
            //sag-orta-sol
          if(matrix[i][j].player==matrix[i][j+1].player&&
                  matrix[i][j].player==matrix[i][j-1].player&&
                  matrix[i][j].player!=0)
          {
              status=true;
              buttonWinMarker(matrix[i][j].number,matrix[i][j+1].number,matrix[i][j-1].number,player);
          }

                  // qDebug()<<matrix[i][j];
        }

    }

    for(int i=1;i<=4;i++)
    {

            //sol dik
           if(matrix[i][0].player==matrix[i-1][0].player&&
                   matrix[i][0].player==matrix[i+1][0].player&&
                   matrix[i][0].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][0].number,matrix[i-1][0].number,matrix[i+1][0].number,player);
           }
      }
    for(int i=1;i<=4;i++)
    {

            //sağ dik
           if(matrix[i][5].player==matrix[i-1][5].player&&
                   matrix[i][5].player==matrix[i+1][5].player&&
                   matrix[i][5].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][5].number,matrix[i-1][5].number,matrix[i+1][5].number,player);
           }
      }
    for(int i=1;i<=4;i++)
    {

            //ust yatay
           if(matrix[0][i].player==matrix[0][i-1].player&&
                   matrix[0][i].player==matrix[0][i+1].player&&
                   matrix[0][i].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[0][i].number,matrix[0][i-1].number,matrix[0][i+1].number,player);
           }
      }
    for(int i=1;i<=4;i++)
    {

            //alt yatay
           if(matrix[5][i].player==matrix[5][i-1].player&&
                   matrix[5][i].player==matrix[5][i+1].player&&
                   matrix[5][i].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[5][i].number,matrix[5][i-1].number,matrix[5][i+1].number,player);
           }
      }

    if(status)
    {
       /* QMessageBox msgBox;
        msgBox.setText("Tebrikler MAVİ Oyuncu Oyunu Kazandınız"
                       "\n\nYeni Oyuna Devam Etmek İstiyor Musunuz?");
         msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Çarpanga Oyunu !");
       // QPixmap icon(":/icons/bell.svg");
        //msgBox.setWindowIcon(icon);
        QAbstractButton *tamamButton;
       // QAbstractButton *hayirButton;

       tamamButton =msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
       //hayirButton =msgBox.addButton(tr("Hayır"), QMessageBox::ActionRole);

           msgBox.exec();*/
           statusLabel->setText("Oyunu MAVİ Oyuncu Kazandı..");
           gameFinishStatus=true;///oyun bitti
          /* if(msgBox.clickedButton()==evetButton)
           {
           // qDebug()<<"devam";
               newGame();
           }*/
    }
 }

void MainWindow::player2WinControl()
 {

       int player=2;
        bool status=false;
       for(int i=1;i<=4;i++)
       {
           for(int j=1;j<=4;j++)
           {
               //ust-orta-alt
              if(matrix[i][j].player==matrix[i-1][j].player&&
                      matrix[i][j].player==matrix[i+1][j].player&&
                      matrix[i][j].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[i][j].number,matrix[i-1][j].number,matrix[i+1][j].number,player);
              }
               //ustsol-orta-altsag
              if(matrix[i][j].player==matrix[i-1][j-1].player&&
                      matrix[i][j].player==matrix[i+1][j+1].player&&
                      matrix[i][j].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[i][j].number,matrix[i-1][j-1].number,matrix[i+1][j+1].number,player);
              }
                //ustsag-orta-altsol
              if(matrix[i][j].player==matrix[i-1][j+1].player&&
                      matrix[i][j].player==matrix[i+1][j-1].player&&
                      matrix[i][j].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[i][j].number,matrix[i-1][j+1].number,matrix[i+1][j-1].number,player);
              }
               //sag-orta-sol
             if(matrix[i][j].player==matrix[i][j+1].player&&
                     matrix[i][j].player==matrix[i][j-1].player&&
                     matrix[i][j].player!=0)
             {
                 status=true;
                 buttonWinMarker(matrix[i][j].number,matrix[i][j+1].number,matrix[i][j-1].number,player);
             }

                     // qDebug()<<matrix[i][j];
           }

       }

       for(int i=1;i<=4;i++)
       {

               //sol dik
              if(matrix[i][0].player==matrix[i-1][0].player&&
                      matrix[i][0].player==matrix[i+1][0].player&&
                      matrix[i][0].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[i][0].number,matrix[i-1][0].number,matrix[i+1][0].number,player);
              }
         }
       for(int i=1;i<=4;i++)
       {

               //sağ dik
              if(matrix[i][5].player==matrix[i-1][5].player&&
                      matrix[i][5].player==matrix[i+1][5].player&&
                      matrix[i][5].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[i][5].number,matrix[i-1][5].number,matrix[i+1][5].number,player);
              }
         }
       for(int i=1;i<=4;i++)
       {

               //ust yatay
              if(matrix[0][i].player==matrix[0][i-1].player&&
                      matrix[0][i].player==matrix[0][i+1].player&&
                      matrix[0][i].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[0][i].number,matrix[0][i-1].number,matrix[0][i+1].number,player);
              }
         }
       for(int i=1;i<=4;i++)
       {

               //alt yatay
              if(matrix[5][i].player==matrix[5][i-1].player&&
                      matrix[5][i].player==matrix[5][i+1].player&&
                      matrix[5][i].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[5][i].number,matrix[5][i-1].number,matrix[5][i+1].number,player);
              }
         }

    if(status)
    {
     /*   QMessageBox msgBox;
        msgBox.setText("Tebrikler KIRMIZI Oyuncu Oyunu Kazandınız"
                       "\n\nYeni Oyuna Devam Etmek İstiyor Musunuz?");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Çarpanga Oyunu !");
       // QPixmap icon(":/icons/bell.svg");
        //msgBox.setWindowIcon(icon);
        QAbstractButton *tamamButton;
        //QAbstractButton *hayirButton;

       tamamButton =msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
      // hayirButton =msgBox.addButton(tr("Hayır"), QMessageBox::ActionRole);

           msgBox.exec();
           */
        statusLabel->setText("Oyunu KIRMIZI Oyuncu Kazandı..");

           gameFinishStatus=true;///oyun bitti

          /* if(msgBox.clickedButton()==evetButton)
           {
            //qDebug()<<"devam";
               newGame();
           }*/
    }
 }

void MainWindow::buttonWinMarker(int a1,int a2,int a3,int player)
{
   // qDebug()<<"kazanan sayılar"<<a1<<a2<<a3<<player;

    if(player=1)
    {
        for(int i=0;i<butonSayilarListe.count();i++)
        {
            if(butonSayilarListe[i]->text().toInt()==a1&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,200,150);"
                                                    "border: 1px solid gray;border-radius:"+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            }
            if(butonSayilarListe[i]->text().toInt()==a2&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,200,150);"
                                                    "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            }
            if(butonSayilarListe[i]->text().toInt()==a3&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,200,150);"
                                                    "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            }
        }

    }

    if(player=2)
    {
        for(int i=0;i<butonSayilarListe.count();i++)
        {
            if(butonSayilarListe[i]->text().toInt()==a1&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(200,0,0,150);"
                                                    "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            }
            if(butonSayilarListe[i]->text().toInt()==a2&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(200,0,0,150);"
                                                    "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            }
            if(butonSayilarListe[i]->text().toInt()==a3&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(200,0,0,150);"
                                                    "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            }
        }

    }
     winplayer->play();


}
MainWindow::~MainWindow()
{

}
