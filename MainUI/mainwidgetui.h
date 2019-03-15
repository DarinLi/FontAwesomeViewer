#ifndef MAINWIDGETUI_H
#define MAINWIDGETUI_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include <QFont>
#include <QSettings>
#include <QClipboard>
#include <QPushButton>
#include <QButtonGroup>
#include <QScopedPointer>

#include "flowlayout.h"

namespace Ui {
class MainWidgetUI;
}

class MainWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidgetUI(QWidget *parent = nullptr);
    ~MainWidgetUI() override;

public:
    QVariant iniFilesValueRead(const QString &key1, const QString &key2);
    void iniFilesSetValue(const QString &key1, const QString &key2, const QVariant &value);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void onButtonClicked(int id);

private:
    class MainWidgetUIPrivate;
    const QScopedPointer<MainWidgetUIPrivate> d;

private:
    Ui::MainWidgetUI *ui;
};

#endif // MAINWIDGETUI_H
