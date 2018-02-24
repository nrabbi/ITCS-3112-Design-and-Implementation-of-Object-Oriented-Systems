#include "login.h"
#include "ui_login.h"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include "QRegExp"
#include "mainwindow.h"
#include "global.h"

// full directory path is specified instead of just user.txt beacause of issues with mac osx
QFile file("/Users/nrabbi/Documents/QT/term_project_3112/user.txt");

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // removes the minimuze, maximize and exit button from the title bar
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

Login::~Login()
{
    delete ui;
}

// action for exit button
void Login::on_exitButton_clicked()
{
    QApplication::quit();
}

// checks to make sure the employee login info is correct
void Login::on_loginButton_clicked()
{
    int counter = 0;
    bool match = false;

    // reads the user information file
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in (&file);

        // read whole content
        QString content = file.readAll();
        // extract words into a list
        QStringList list = content.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        // checks if the user login input matches the login data on the user information file
        while (counter < list.size()){
            if ((ui->userInput->text() == list[counter]) && (ui->passInput->text() == list[counter+1]) ){
                match = true;
                currentUser = ui->userInput->text();
            }

            counter+=2;
        }

        // if the login info matches the database the following code is run
        if (match == true){
            QMessageBox msgBox;

            msgBox.setText(("You have successfully logged in."));
            QAbstractButton* pButtonYes = msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
            msgBox.exec();

            // if the login info is correct then the user is redirected  back to home page window
            if (msgBox.clickedButton()==pButtonYes) {
                MainWindow *mainPage = new MainWindow();

                this->close(); // hides the login window
                mainPage->show(); // shows the home page window
                mainPage->activateWindow(); // activates the home page window
                mainPage->raise(); // makes sure the home page window is on top/focused
            }
        }
        else
            QMessageBox::about(this, "Employee Verification", "Error! wrong employee information, Please try again..");

        file.close();
    }

}
