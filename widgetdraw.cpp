//
// Created by Rogelio Rast on 2/14/23.
//

#include "widgetdraw.hpp"


widgetDraw::widgetDraw(){
    setupUi(this);
}

widgetDraw::~widgetDraw() {
    delete buttonNext;
    delete buttonOpen;
    delete graphicsView;
    delete scene;
    delete lineEditPath;
    delete answerCsv;
    delete box;
    delete gridLayout;
}

void widgetDraw::setupUi(QWidget *twin) {
    this->win = twin;
    setupWindow();
    setupLineEdit();
    setupButtons();
    setupScene();
    layoutElements();
}

void widgetDraw::setupWindow() {
    win->setWindowTitle("Draw CSV");
    gridLayout = new QGridLayout(this);
    this->setLayout(gridLayout);
    answerCsv = new QLabel(win);
    answerCsv->setStyleSheet("QLabel { color: red; }");
}

void widgetDraw::setupButtons() {
    QCommonStyle style;
    buttonNext = new QPushButton(style.standardIcon(QStyle::SP_ArrowForward), "Next", win);
    buttonPrev = new QPushButton(style.standardIcon(QStyle::SP_ArrowBack), "Prev", win);
    buttonOpen = new QPushButton(style.standardIcon(QStyle::SP_DialogOpenButton), "Open", win);
    connect(buttonOpen, &QPushButton::clicked, [this]{ clickedOpenButton();});
    connect(buttonNext, &QPushButton::clicked, [this]{ clickedNextButton();});
    connect(buttonPrev, &QPushButton::clicked, [this]{ clickedPrevButton();});
}

void widgetDraw::setupScene() {
    graphicsView = new QGraphicsView(win);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setFixedSize(280, 280);
    scene = new QGraphicsScene;
    scene->setSceneRect(graphicsView->rect());
    graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(Qt::white));
}

void widgetDraw::setupLineEdit() {
    lineEditPath = new QLineEdit(win);
    lineEditPath->setPlaceholderText("Open file");
    lineEditPath->setMaximumWidth(280);
    lineEditPath->setEnabled(false);
}

void widgetDraw::clickedOpenButton() {
    scene->clear();
    captures.clear();
    QString filepath = QFileDialog::getOpenFileName(win, "Open file", "~", "CSV files(*.csv)");
    lineEditPath->setText(filepath);
    progressDialog = new QProgressDialog("Read file", nullptr, 0, 1, win);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setValue(0);
    progressDialog->show();

    std::ifstream csvFile(filepath.toStdString());
    std::string line;
    while (getline(csvFile, line))
    {
        std::string tmp, answer;
        std::stringstream ss(line);
        std::vector<int> vals;
        getline(ss, answer, ',');
        while(getline(ss, tmp, ',')){
            vals.push_back(std::stoi(tmp));
        }
        captures.push_back(std::pair<std::string, std::vector<int>>(std::string(1, stoi(answer) + 64), vals));
    }
    csvFile.close();
    pict = captures.begin();
    answerCsv->setText(QString::fromStdString("Answer: " + pict->first));
    int yp = -1;
    for (int xp = 0; xp < pict->second.size(); xp++){
        if (xp % 28 == 0)
            yp++;
        scene->addRect(yp * 10, (xp % 28) * 10, 10, 10, QPen(Qt::NoPen),QBrush(QColor(255 - pict->second[xp], 255 - pict->second[xp], 255 - pict->second[xp])));
    }
    progressDialog->setValue(1);
}

void widgetDraw::clickedNextButton() {
    if (lineEditPath->text().isEmpty())
        return;
    pict++;
    if (pict == captures.end())
        pict = captures.begin();
    scene->clear();
    answerCsv->setText(QString::fromStdString("Answer: " + pict->first));
    int yp = -1;
    for (int xp = 0; xp < pict->second.size(); xp++){
        if (xp % 28 == 0) {
            yp++;
        }
        scene->addRect(yp * 10, (xp % 28) * 10, 10, 10, QPen(Qt::NoPen),QBrush(QColor(255 - pict->second[xp], 255 - pict->second[xp], 255 - pict->second[xp])));
    }
}

void widgetDraw::layoutElements() {
    box = new QHBoxLayout;
    box->addWidget(buttonPrev);
    box->addWidget(buttonNext);
    gridLayout->addWidget(lineEditPath, 0, 0);
    gridLayout->addWidget(buttonOpen, 0, 1);
    gridLayout->addWidget(graphicsView, 1, 0);
    gridLayout->addWidget(answerCsv, 1, 1);
    gridLayout->addLayout(box, 2, 0);
    win->setFixedSize(win->sizeHint());
}

void widgetDraw::clickedPrevButton() {
    if (lineEditPath->text().isEmpty())
        return;
    if (pict == captures.begin()) {
        pict = captures.end();
    }
    pict--;
    scene->clear();
    answerCsv->setText(QString::fromStdString("Answer: " + pict->first));
    int yp = -1;
    for (int xp = 0; xp < pict->second.size(); xp++){
        if (xp % 28 == 0) {
            yp++;
        }
        scene->addRect(yp * 10, (xp % 28) * 10, 10, 10, QPen(Qt::NoPen),QBrush(QColor(255 - pict->second[xp], 255 - pict->second[xp], 255 - pict->second[xp])));
    }
}
