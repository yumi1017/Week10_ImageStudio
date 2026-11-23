#include "mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QStyle>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Image Studio | Week 10"));
    resize(800, 500);

    auto *workspace = new QLabel(tr("Image Workspace"), this);
    workspace->setAlignment(Qt::AlignCenter);
    setCentralWidget(workspace);

    statusBar()->showMessage(tr("Ready"));

    auto *openAction = new QAction(
        style()->standardIcon(QStyle::SP_DialogOpenButton),
        tr("&Open Image..."), this);
    openAction->setShortcut(QKeySequence::Open);

    auto *saveAction = new QAction(
        style()->standardIcon(QStyle::SP_DialogSaveButton),
        tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);

    auto *exitAction = new QAction(
        style()->standardIcon(QStyle::SP_DialogCloseButton),
        tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence(QStringLiteral("Ctrl+Q")));

    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addMenu(tr("&Image"));
    menuBar()->addMenu(tr("&Edit"));

    auto *toolBar = addToolBar(tr("File Tools"));
    toolBar->setObjectName(QStringLiteral("fileToolBar"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveImage);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
}

MainWindow::~MainWindow() = default;

void MainWindow::openImage()
{
    const QString path = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        QString(),
        tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    if (path.isEmpty()) {
        return;
    }

    selectedImagePath = path;
    statusBar()->showMessage(
        tr("Selected: %1").arg(QFileInfo(selectedImagePath).fileName()));
}

void MainWindow::saveImage()
{
    statusBar()->showMessage(
        tr("Save activated. Image saving is unavailable in V1."));
}