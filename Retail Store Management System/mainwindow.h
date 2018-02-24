/*
 *  mainwindow.h
 *
 *	ITCS 3112
 *	Term Project : Retail Store Management System
 *
 *  Created on   : Nov 15, 2017
 *  Updated on   : Dec 08, 2017
 *      Author   : Nazmul Rabbi
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
	 	*  Constructor initializes the main window
	 	*  @param none
	*/
    explicit MainWindow(QWidget *parent = 0);
    
    /**
	 	*  Destructor terminates the main window
	 	*  @param none
	*/
    ~MainWindow();

private slots:
    /**
		 *	exits the program
		 *  @param none
	  	 *	@return none
	*/
    void on_exitButton_clicked();
    
    /**
		 *	opens the lookup stock form
		 *  @param none
	  	 *	@return none
	*/
    void on_lookupStockButton_clicked();
    
    /**
		 *	action button that allows the user to lookup, add, update and remove stock from the database
		 *  @param none
	  	 *	@return none
	*/
    void on_searchButton_clicked();
    
    /**
		 *	opens the add stock form
		 *  @param none
	  	 *	@return none
	*/
    void on_addStockButton_clicked();
    
    /**
		 *	resets the program to its default state
		 *  @param none
	  	 *	@return none
	*/
    void on_resetButton_clicked();
    
    /**
		 *	opens the update stock form
		 *  @param none
	  	 *	@return none
	*/
    void on_updateStockButton_clicked();
    
    /**
		 *	opens the sell item form
		 *  @param none
	  	 *	@return none
	*/
    void on_sellItemButton_clicked();
    
    /**
		 *	opens the customer invoice form
		 *  @param none
	  	 *	@return none
	*/
    void on_customerInvoiceButton_clicked();
    
    /**
		 *	opens the delete invoice form
		 *  @param none
	  	 *	@return none
	*/
    void on_deleteInvoiceButton_clicked();
    
    /**
		 *	allows the user to sign out
		 *  @param none
	  	 *	@return none
	*/
    void on_signoutButton_clicked();
    
    /**
		 *	action button that allows the user to sell item, lookup, receive, and remove invoice from the database
		 *  @param none
	  	 *	@return none
	*/
    void on_searchButton_2_clicked();
    
    /**
		 *	allows the user to add multiple items to the cart
		 *  @param none
	  	 *	@return none
	*/
    void on_cartButton_clicked();
    
    /**
		 *	opens the delete stock form
		 *  @param none
	  	 *	@return none
	*/
    void on_deleteStockButton_clicked();
    
    /**
		 *	opens the shipment invoice form
		 *  @param none
	  	 *	@return none
	*/
    void on_shipmentInvoiceButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
