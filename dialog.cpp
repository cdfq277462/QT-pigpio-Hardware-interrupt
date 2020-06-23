#include "dialog.h"
#include "ui_dialog.h"
#include "pigpio.h"

#define ISR_pin 27

Dialog* Dialog::m_psDialog = nullptr;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_psDialog = this;

    gpioInitialise();
    gpioSetMode(ISR_pin, PI_INPUT);
    gpioSetPullUpDown(ISR_pin, PI_PUD_DOWN); //set trig_pin to edge trig
    time_sleep(0.001);
    gpioSetISRFunc(ISR_pin, FALLING_EDGE, 0, gpio_ISR); //ISR

    connect(this, SIGNAL(emit_sig()),  \
            this, SLOT(on_Recevie_sig()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::gpio_ISR(int gpio, int level, uint32_t tick)
{
    emit m_psDialog->emit_sig();
}

void Dialog::on_Recevie_sig()
{
    ui->label->setText("Hello World!");
    ui->pushButton->setText("I did it!");
}
