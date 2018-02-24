/*
 *  login.h
 *
 *	ITCS 3112
 *	Term Project : Retail Store Management System
 *
 *  Created on   : Nov 29, 2017
 *  Updated on   : Dec 08, 2017
 *      Author   : Nazmul Rabbi
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    /**
	 	*  Constructor initializes the login window
	 	*  @param none
	*/
    explicit Login(QWidget *parent = 0);
    
    /**
	 	*  Destructor terminates the login window
	 	*  @param none
	*/
    ~Login();

private slots:
    /**
		 *	exits the program
		 *  @param none
	  	 *	@return none
	*/
    void on_exitButton_clicked();
    
    /**
		 *	allows the user to log into the main program
		 *  @param none
	  	 *	@return none
	*/
    void on_loginButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
