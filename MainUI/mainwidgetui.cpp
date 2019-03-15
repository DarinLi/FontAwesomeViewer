#include "mainwidgetui.h"
#include "ui_mainwidgetui.h"

class MainWidgetUI::MainWidgetUIPrivate
{
public:
    QList<QPushButton *> pushButtonList;

    QButtonGroup *buttonGroup = nullptr;

    QClipboard *m_clipBoard = nullptr;
};

MainWidgetUI::MainWidgetUI(QWidget *parent) :
    QWidget(parent),
    d(new MainWidgetUIPrivate),
    ui(new Ui::MainWidgetUI)
{
    ui->setupUi(this);

    FlowLayout *flowLayout = new FlowLayout(5,5,5);

    d->buttonGroup = new QButtonGroup(this);
    d->buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
    d->buttonGroup->setExclusive(true);

    QFont font;
    QString m_string;
    QString m_IconString;
    QString m_IconStringName;
    QString m_IconStringCode;

    bool ok;
    int iconNameMultiplex = 1;
    int icon_max = 0;

    QSettings iniFileRead("./theme/ThemeConfig.ini", QSettings::IniFormat);
    icon_max = iniFileRead.value("ICON_Total/num").toInt();

    for (int i = 0; i < icon_max; i++) {
        d->pushButtonList<<new QPushButton(this);
        d->pushButtonList[i]->setFixedSize(36, 36);
        d->pushButtonList[i]->setCheckable(true);

        font = d->pushButtonList[i]->font();
        font.setFamily("FontAwesome");
        font.setPixelSize(24);
        d->pushButtonList[i]->setFont(font);

        m_IconString = iniFileRead.value(QString("ICON_Total/icon%1").arg(i)).toString();
        m_IconStringCode = m_IconString.section(",", 0, 0, QString::SectionDefault);
        iconNameMultiplex = m_IconString.section(",", 1, 1, QString::SectionDefault).toInt();
        m_IconStringName = m_IconString.section(",", 2, (1 + iconNameMultiplex), QString::SectionDefault);

        d->pushButtonList[i]->setText(QChar(m_IconStringCode.toInt(&ok, 16)));

        m_string = QString(tr("Unicode: %1\nName   : %2\n"
                              "Click to copy unicode to clipboard"))
                .arg(m_IconStringCode).arg(m_IconStringName);

        d->pushButtonList[i]->setToolTip(m_string);

        d->buttonGroup->addButton(d->pushButtonList[i], i);

        flowLayout->addWidget(d->pushButtonList[i]);
    }

    d->pushButtonList[0]->setChecked(true);

    connect(d->buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWidgetUI::onButtonClicked);

    ui->ContentWidget->setLayout(flowLayout);

    font = ui->IconLabelShow->font();
    font.setFamily("FontAwesome");
    font.setPixelSize(72);
    ui->IconLabelShow->setFont(font);
    ui->IconLabelShow->setText(QChar(0xf000));
    ui->IconLabelShow->setAlignment(Qt::AlignCenter);

    ui->CodeLineEditShow->setText("0xf000");
    ui->CodeLineEditShow->setReadOnly(true);

    ui->NameLineEditShow->setText("fa_glass");
    ui->NameLineEditShow->setReadOnly(true);

    d->m_clipBoard =  QApplication::clipboard();
}

MainWidgetUI::~MainWidgetUI()
{
    delete ui;
}

void MainWidgetUI::onButtonClicked(int id)
{
    QSettings iniFileRead("./theme/ThemeConfig.ini", QSettings::IniFormat);
    QString m_IconString = iniFileRead.value(QString("ICON_Total/icon%1").arg(id)).toString();
    QString m_IconStringCode = m_IconString.section(",", 0, 0, QString::SectionDefault);
    int iconNameMultiplex = m_IconString.section(",", 1, 1, QString::SectionDefault).toInt();
    QString m_IconStringName = m_IconString.section(",", 2, (1 + iconNameMultiplex), QString::SectionDefault);

    ui->CodeLineEditShow->setText(m_IconStringCode);
    ui->NameLineEditShow->setText(m_IconStringName);

    ui->IconLabelShow->setText(d->pushButtonList[id]->text());

    d->m_clipBoard->setText(m_IconStringCode);
}

void MainWidgetUI::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QVariant MainWidgetUI::iniFilesValueRead(const QString &key1, const QString &key2)
{
    QSettings iniFileRead("./theme/ThemeConfig.ini", QSettings::IniFormat);

    return iniFileRead.value(key1 + "/" + key2);
}

void MainWidgetUI::iniFilesSetValue(const QString &key1, const QString &key2, const QVariant &value)
{
    QSettings iniFile("./theme/ThemeConfig.ini", QSettings::IniFormat);

    iniFile.setValue(key1 + "/" + key2, value);
}
