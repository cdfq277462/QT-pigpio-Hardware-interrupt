# **QT-pigpio-Hardware-interrupt**

>Hello everyone, this is I first time wirted down my experience in develop QT on raspberry Pi 4. I was explored a lot of website, and finanly got some achievement to got my application work easily and simplily.
So let's go!

### **Before Start...**
>Before we get start you nned to prepare some stuff.

1.	Linux ubuntu 20.04 LTS  _(also in WIndows, but I was not to try)_
2.	Raspberry Pi4 2GB
3.	Install [pigpio](http://abyz.me.uk/rpi/pigpio/) on RPI
>Unfortunately, wiringPi's author said he won't update any more.
4.	A lot of patient

### **First Step : Cross Compile QT for RPI**
>If you just wonna do something simple GUI application for RPI, you may not to cross compile QT for RPI.
>But if want to use something awesome, e.g QChart, unfortunately.
>I'll put a link below, the videos help me a lot.

>>btw I just did this step almost cost 2 months, until this Youtuber post it.

[Qt for Raspberry Pi - Qt 5.14.2 cross compilation for Raspberry Pi 4 model B - Run Qt on Raspberry](https://www.youtube.com/watch?v=TmtN3Rmx9Rk)


### **Second Step : Coding**
>Ok, I lost my patient. So I'll put everything up and explain them.

in **Myinterrpt.pro**

```
#add this line
LIBS += -lpigpio -lrt -lpthread
```

in **dialog.h**
```cpp
public:
//m_psDialog is ISR to excute Dialog function pointer
	 static Dialog *m_psDialog;
//ISR function define in pigpio.h, connot change
	 static void gpio_ISR(int gpio, int level, uint32_t tick);
	 
public slots:
	void on_Recevie_sig();
	
signals:
	void emit_sig();
```

in **dialog.cpp**

```cpp
//define which gpio pin you want to be hardware interrupt
#define ISR_pin 27
//initialise  m_psDialog
Dialog* Dialog::m_psDialog = nullptr;
```
```cpp
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
//[[[IMPORTANT]]] set m_psDialog pointer to this
    m_psDialog = this;
	
//Initialise pgpio
	gpioInitialise();
	gpioSetMode(ISR_pin, PI_INPUT); //set ISR_pin is input
	gpioSetPullUpDown(ISR_pin, PI_PUD_DOWN); 
	time_sleep(0.001);
	gpioSetISRFunc(ISR_pin, FALLING_EDGE, 0, gpio_ISR); //ISR

	//connect gpio_ISR emit signal to whatever slot you prefer
	connect(this, SIGNAL(emit_sig()),  \
				this, SLOT(on_Recevie_sig()));
}
void Dialog::gpio_ISR(int gpio, int level, uint32_t tick)
{
	emit m_psDialog->emit_sig();
	//also  m_psDialog->on_Recevie_sig();
}

void Dialog::on_Recevie_sig()
{
/*****************whatever you want to do	********************/
    ui->label->setText("Hello World!");
    ui->pushButton->setText("I did it!");
/****************************************************************/
}
```
