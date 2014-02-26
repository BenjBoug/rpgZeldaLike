#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    chipsetView = new ChipsetView();
    ui->graphicsViewChipset->setScene(chipsetView);

    createGroupButtons();

    connect(UndoSingleton::getInstance(),SIGNAL(redoEmpty(bool)),ui->actionRedo,SLOT(setEnabled(bool)));
    connect(UndoSingleton::getInstance(),SIGNAL(undoEmpty(bool)),ui->actionUndo,SLOT(setEnabled(bool)));

    connect(ui->actionRedo,SIGNAL(triggered()),UndoSingleton::getInstance(),SLOT(redo()));
    connect(ui->actionUndo,SIGNAL(triggered()),UndoSingleton::getInstance(),SLOT(undo()));

    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(setActiveSubWindow(QWidget*)));

    updateMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chipsetView;
}

MdiChild *MainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::newMap()
{
    MdiChild *child = createMdiChild();
    child->newMap();
    child->show();
    changeChipset();
    UndoSingleton::getInstance()->clearUndo();
}

MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild(chipsetView);
    ui->mdiArea->addSubWindow(child);
    return child;
}
void MainWindow::openMap()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a map", QString(), "Map Zelda (*.k2x)");
    if (!fileName.isEmpty()) {

        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        MdiChild *child = createMdiChild();
        if (child->openMap(fileName)) {
            statusBar()->showMessage(tr("File loaded"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}

void MainWindow::maximizeMap()
{
    if (activeMdiChild())
    {
        QTransform matrix;
        matrix.scale(0.5,0.5);
        activeMdiChild()->setTransform(matrix);
    }
}

void MainWindow::minimizeMap()
{
    if (activeMdiChild())
    {
        QTransform matrix;
        matrix.scale(1,1);
        activeMdiChild()->setTransform(matrix);
    }
}

void MainWindow::lowerLayer()
{
    if (activeMdiChild())
        activeMdiChild()->lowerLayer();
}

void MainWindow::higherLayer()
{
    if (activeMdiChild())
        activeMdiChild()->higherLayer();
}

void MainWindow::collisionLayer()
{
    if (activeMdiChild())
        activeMdiChild()->collisionLayer();
}

void MainWindow::visuaLayer()
{
    if (activeMdiChild())
        activeMdiChild()->visuaLayer();
}

void MainWindow::changeChipset()
{
    if (activeMdiChild())
        activeMdiChild()->changeChipset();
}

void MainWindow::clearMap()
{
    if (activeMdiChild())
        activeMdiChild()->clearMap();
}

void MainWindow::brushTool()
{
    if (activeMdiChild())
        activeMdiChild()->brushTool();
}

void MainWindow::paintPotTool()
{
    if (activeMdiChild())
        activeMdiChild()->paintPotTool();
}

void MainWindow::pipetteTool()
{
    if (activeMdiChild())
        activeMdiChild()->pipetteTool();
}

void MainWindow::save()
{
    if (activeMdiChild() && activeMdiChild()->save())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::saveAs()
{
    if (activeMdiChild() && activeMdiChild()->saveAs())
        statusBar()->showMessage(tr("File saved"), 2000);
}
void MainWindow::changeName()
{
    if (activeMdiChild())
        activeMdiChild()->changeName();
}

void MainWindow::gridLayer(bool enable)
{
    if (activeMdiChild())
        activeMdiChild()->gridLayer(enable);
}

void MainWindow::createGroupButtons()
{
    groupZoom.addAction(ui->actionZoom_1_1);
    groupZoom.addAction(ui->actionZoom_1_2);

    groupLayers.addAction(ui->actionLawer_layer);
    groupLayers.addAction(ui->actionHigh_layer);
    groupLayers.addAction(ui->actionCollision_layer);
    groupLayers.addAction(ui->actionVisualization);

    groupTools.addAction(ui->actionBrush);
    groupTools.addAction(ui->actionCircle);
    groupTools.addAction(ui->actionRectangle);
    groupTools.addAction(ui->actionPipette);
    groupTools.addAction(ui->actionPaint_pot);
}

void MainWindow::updateMenus()
{
    bool hasMdiChild = (activeMdiChild() != 0);
    ui->actionSave->setEnabled(hasMdiChild);
    ui->actionSave_as->setEnabled(hasMdiChild);
    ui->actionClose->setEnabled(hasMdiChild);
    ui->actionClose_All->setEnabled(hasMdiChild);
    ui->actionTile->setEnabled(hasMdiChild);
    ui->actionCascade->setEnabled(hasMdiChild);
    ui->actionNext->setEnabled(hasMdiChild);
    ui->actionPrevious->setEnabled(hasMdiChild);
    ui->actionLawer_layer->setEnabled(hasMdiChild);
    ui->actionHigh_layer->setEnabled(hasMdiChild);
    ui->actionCollision_layer->setEnabled(hasMdiChild);
    ui->actionVisualization->setEnabled(hasMdiChild);
    ui->actionBrush->setEnabled(hasMdiChild);
    ui->actionPaint_pot->setEnabled(hasMdiChild);
    ui->actionPipette->setEnabled(hasMdiChild);
    ui->actionShow_Grid->setEnabled(hasMdiChild);
    ui->actionZoom_1_1->setEnabled(hasMdiChild);
    ui->actionZoom_1_2->setEnabled(hasMdiChild);
}

void MainWindow::updateChipset()
{
    if (activeMdiChild())
        activeMdiChild()->updateChipset();
}

void MainWindow::updateWindowMenu()
{
    ui->menuWindow->clear();
    ui->menuWindow->addAction(ui->actionClose);
    ui->menuWindow->addAction(ui->actionClose_All);
    ui->menuWindow->addSeparator();
    ui->menuWindow->addAction(ui->actionTile);
    ui->menuWindow->addAction(ui->actionCascade);
    ui->menuWindow->addSeparator();
    ui->menuWindow->addAction(ui->actionNext);
    ui->menuWindow->addAction(ui->actionPrevious);
    QAction * actionSeparator = ui->menuWindow->addSeparator();

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = ui->menuWindow->addAction(text);
        action->setCheckable(true);
        action->setChecked(child == activeMdiChild());

        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}
