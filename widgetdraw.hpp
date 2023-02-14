//
// Created by Rogelio Rast on 2/14/23.
//

#ifndef DRAWCSV_WIDGETDRAW_HPP
#define DRAWCSV_WIDGETDRAW_HPP

#include <QWidget>
#include <QtWidgets/qpushbutton.h>
#include <QGraphicsView>
#include <QGridLayout>
#include <QtWidgets/qlineedit.h>
#include <QProgressDialog>
#include <QCommonStyle>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <vector>
#include <fstream>
#include <sstream>

class widgetDraw : public QWidget {
Q_OBJECT

public:
    widgetDraw();

    void setupUi(QWidget *twin);
    void setupWindow();
    void setupLineEdit();
    void setupButtons();
    void setupScene();
    void clickedOpenButton();
    void clickedNextButton();
    void clickedPrevButton();
    void layoutElements();

    virtual ~widgetDraw();

private:
    QWidget *win;
    QLabel *answerCsv;
    QPushButton *buttonNext;
    QPushButton *buttonPrev;
    QPushButton *buttonOpen;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QGridLayout *gridLayout;
    QLineEdit *lineEditPath;
    std::vector<std::pair<std::string, std::vector<int>>> captures;
    std::vector<std::pair<std::string, std::vector<int>>>::iterator pict;
    QProgressDialog *progressDialog;
    QHBoxLayout *box;
};


#endif //DRAWCSV_WIDGETDRAW_HPP
