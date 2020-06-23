#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    static Dialog *m_psDialog;


    static void gpio_ISR(int gpio, int level, uint32_t tick);

public slots:

    void on_Recevie_sig();

signals:

    void emit_sig();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
