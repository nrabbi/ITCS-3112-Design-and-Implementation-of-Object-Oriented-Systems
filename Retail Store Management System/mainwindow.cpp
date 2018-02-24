#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QTextStream"
#include "inventory.h"
#include "login.h"
#include "global.h"
#include "iostream"
#include "string"
#include "fstream"

// full directory path is specified instead of just data.txt beacause of issues with mac osx
Inventory inv("/Users/nrabbi/Documents/QT/term_project_3112/data.txt");
string *cart = new string[10];
QTextStream out(stdout);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Welcome " + currentUser);

    // removes the minimuze, maximize and exit button from the title bar
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    // hides manage stock interface objects
    ui->brandLabel->hide();
    ui->brandInput->hide();
    ui->itemLabel->hide();
    ui->itemInput->hide();
    ui->categoryLabel->hide();
    ui->categoryList->hide();
    ui->searchButton->hide();
    ui->amountLabel->hide();
    ui->amountInput->hide();
    ui->priceLabel->hide();
    ui->priceInput->hide();
    ui->wholesaleLabel->hide();
    ui->wholesaleInput->hide();

    // hides manage invoice interface objects
    ui->nameLabel->hide();
    ui->nameInput->hide();
    ui->invoiceLabel->hide();
    ui->invoiceInput->hide();
    ui->brandLabel_2->hide();
    ui->brandInput_2->hide();
    ui->itemLabel_2->hide();
    ui->itemInput_2->hide();
    ui->categoryLabel_2->hide();
    ui->categoryList_2->hide();
    ui->searchButton_2->hide();
    ui->cartButton->hide();
    ui->amountLabel_2->hide();
    ui->amountInput_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// action for exit program button
void MainWindow::on_exitButton_clicked()
{
    inv.close();
    QApplication::quit();
}

// action for lookup stock button
void MainWindow::on_lookupStockButton_clicked()
{
    // hides/shows interface objects
    ui->brandLabel->show();
    ui->brandInput->show();
    ui->itemLabel->show();
    ui->itemInput->show();
    ui->categoryLabel->show();
    ui->categoryList->show();
    ui->searchButton->show();
    ui->amountLabel->hide();
    ui->amountInput->hide();
    ui->priceLabel->hide();
    ui->priceInput->hide();
    ui->wholesaleLabel->hide();
    ui->wholesaleInput->hide();

    // modifies default object values
    ui->leftTopLabel->setText("Lookup Stock");
    ui->brandInput->setText("");
    ui->itemInput->setText("");
    ui->categoryList->setCurrentRow(0);
    ui->lookupStockButton->setEnabled(false);
    ui->addStockButton->setEnabled(true);
    ui->updateStockButton->setEnabled(true);
    ui->deleteStockButton->setEnabled(true);
    ui->searchButton->setText("Search");
    ui->categoryLabel->move(170,245);
    ui->categoryList->move(110,265);
    ui->searchButton->move(155,320);
}

// action for left hand side search action
void MainWindow::on_searchButton_clicked()
{
    // action for lookup stock
    if (ui->searchButton->text() == "Search"){
        // checks if the user input is empty or not
        if (ui->brandInput->text() != "" && ui->itemInput->text() != "") {
            Item *temp=inv.lookupItem(ui->itemInput->text().toStdString() , ui->brandInput->text().toStdString() , ui->categoryList->currentItem()->text().toStdString());

            // if the item is found on database this code is run
            if (temp != NULL){
                int stock = inv.lookupItem(ui->itemInput->text().toStdString(), ui->brandInput->text().toStdString(), ui->categoryList->currentItem()->text().toStdString())->getStockCount();
                QString amount = QString("%1").arg(stock); // converts stock variable to type QString
                QMessageBox::about(this, "Lookup Stock", "Category\n" + ui->categoryList->currentItem()->text() + "\n\nBrand\n" + ui->brandInput->text() + "\n\nItem Name\n" + ui->itemInput->text() + "\n\nAvailable Units\n" + amount);
            }
            // if the item is not found on database this code is run
            else
                QMessageBox::about(this, "Lookup Stock", "Not Found!");
        }
    }

    // action for add stock
    if (ui->searchButton->text() == "Add"){
        if (ui->brandInput->text() != "" && ui->itemInput->text() != "" && ui->amountInput->value() > 0 && ui->priceInput->value() > 0 && ui->wholesaleInput->value() > 0){
            inv.addItem(Item(ui->brandInput->text().toStdString(), ui->itemInput->text().toStdString(), ui->categoryList->currentItem()->text().toStdString(), ui->wholesaleInput->value(), ui->priceInput->value(), ui->amountInput->value()));
            inv.close();
            QMessageBox::about(this, "Add Stock", "Added to the database, successfully!");
        }
    }

    // action for update stock
    if (ui->searchButton->text() == "Update"){
        if (ui->brandInput->text() != "" && ui->itemInput->text() != "" && ui->amountInput->value() >= 0 && ui->priceInput->value() > 0 && ui->wholesaleInput->value() > 0){
            Item *temp=inv.lookupItem(ui->itemInput->text().toStdString(), ui->brandInput->text().toStdString(), ui->categoryList->currentItem()->text().toStdString());

            if (temp!=NULL){
                temp->setStockCount(ui->amountInput->value());
                temp->setBuyPrice(ui->wholesaleInput->value());
                temp->setSellPrice(ui->priceInput->value());
                QMessageBox::about(this, "Update Stock", "Database updated, successfully!");
            }
            else{
                QMessageBox::about(this, "Update Stock", "Error! data doesn't exist");
            }

        }
    }

    // action for delete stock
    if (ui->searchButton->text() == "Delete"){
        // checks if the user input is empty or not
        if (ui->brandInput->text() != "" && ui->itemInput->text() != "") {
            Item *temp=inv.lookupItem(ui->itemInput->text().toStdString(), ui->brandInput->text().toStdString(), ui->categoryList->currentItem()->text().toStdString());

            if (temp==NULL){
                //did not delete item. not found
                QMessageBox::about(this, "Delete Stock", "Error! data doesn't exist");
            }
            else{
                inv.removeItem(*temp);
                QMessageBox::about(this, "Delete Stock", "The data is removed from the database, successfully!");
            }

        }
    }
}

// action for the add stock button
void MainWindow::on_addStockButton_clicked()
{
    // hides/shows interface objects
    ui->brandLabel->show();
    ui->brandInput->show();
    ui->itemLabel->show();
    ui->itemInput->show();
    ui->categoryLabel->show();
    ui->categoryList->show();
    ui->searchButton->show();
    ui->amountLabel->show();
    ui->amountInput->show();
    ui->priceLabel->show();
    ui->priceInput->show();
    ui->wholesaleLabel->show();
    ui->wholesaleInput->show();

    // modifies default object values
    ui->leftTopLabel->setText("   Add Stock");
    ui->brandInput->setText("");
    ui->itemInput->setText("");
    ui->amountInput->setValue(0);
    ui->priceInput->setValue(0.0);
    ui->wholesaleInput->setValue(0.0);
    ui->categoryList->setCurrentRow(0);
    ui->lookupStockButton->setEnabled(true);
    ui->addStockButton->setEnabled(false);
    ui->updateStockButton->setEnabled(true);
    ui->deleteStockButton->setEnabled(true);
    ui->searchButton->setText("Add");
    ui->categoryLabel->move(170,375);
    ui->categoryList->move(110,395);
    ui->searchButton->move(155,450);
}

// action for the reset button
void MainWindow::on_resetButton_clicked()
{
    // hides manage stock interface objects
    ui->brandLabel->hide();
    ui->brandInput->hide();
    ui->itemLabel->hide();
    ui->itemInput->hide();
    ui->categoryLabel->hide();
    ui->categoryList->hide();
    ui->searchButton->hide();
    ui->amountLabel->hide();
    ui->amountInput->hide();
    ui->priceLabel->hide();
    ui->priceInput->hide();
    ui->wholesaleLabel->hide();
    ui->wholesaleInput->hide();

    // hides manage invoice interface objects
    ui->nameLabel->hide();
    ui->nameInput->hide();
    ui->invoiceLabel->hide();
    ui->invoiceInput->hide();
    ui->brandLabel_2->hide();
    ui->brandInput_2->hide();
    ui->itemLabel_2->hide();
    ui->itemInput_2->hide();
    ui->categoryLabel_2->hide();
    ui->categoryList_2->hide();
    ui->searchButton_2->hide();
    ui->cartButton->hide();
    ui->amountLabel_2->hide();
    ui->amountInput_2->hide();
    ui->currentCartSize->hide();

    // modifies default object values
    ui->leftTopLabel->setText("Manage Stock");
    ui->rightTopLabel->setText("Sell Item/Manage Invoice");
    ui->brandInput->setText("");
    ui->itemInput->setText("");
    ui->amountInput->setValue(0);
    ui->priceInput->setValue(0.0);
    ui->wholesaleInput->setValue(0.0);
    ui->categoryList->setCurrentRow(0);
    ui->nameInput->setText("");
    ui->brandInput_2->setText("");
    ui->itemInput_2->setText("");
    ui->amountInput_2->setValue(0);
    ui->categoryList_2->setCurrentRow(0);
    ui->lookupStockButton->setEnabled(true);
    ui->addStockButton->setEnabled(true);
    ui->updateStockButton->setEnabled(true);
    ui->deleteStockButton->setEnabled(true);
    ui->sellItemButton->setEnabled(true);
    ui->customerInvoiceButton->setEnabled(true);
    ui->deleteInvoiceButton->setEnabled(true);
    ui->shipmentInvoiceButton->setEnabled(true);

    // resets cart
    cartLimit = 0;
    cart = new string[10];
    ui->currentCartSize->display(1);
}

// action for update stock button
void MainWindow::on_updateStockButton_clicked()
{
    // hides/shows interface objects
    ui->brandLabel->show();
    ui->brandInput->show();
    ui->itemLabel->show();
    ui->itemInput->show();
    ui->categoryLabel->show();
    ui->categoryList->show();
    ui->searchButton->show();
    ui->amountLabel->show();
    ui->amountInput->show();
    ui->priceLabel->show();
    ui->priceInput->show();
    ui->wholesaleLabel->show();
    ui->wholesaleInput->show();

    // modifies default object values
    ui->leftTopLabel->setText("Update Stock");
    ui->lookupStockButton->setEnabled(true);
    ui->addStockButton->setEnabled(true);
    ui->updateStockButton->setEnabled(false);
    ui->deleteStockButton->setEnabled(true);
    ui->brandInput->setText("");
    ui->itemInput->setText("");
    ui->amountInput->setValue(0);
    ui->priceInput->setValue(0.0);
    ui->wholesaleInput->setValue(0.0);
    ui->categoryList->setCurrentRow(0);
    ui->searchButton->setText("Update");
    ui->categoryLabel->move(170,375);
    ui->categoryList->move(110,395);
    ui->searchButton->move(155,450);
}

// action for sell item button
void MainWindow::on_sellItemButton_clicked()
{
    // hides/shows interface objects
    ui->nameLabel->show();
    ui->nameInput->show();
    ui->invoiceLabel->hide();
    ui->invoiceInput->hide();
    ui->brandLabel_2->show();
    ui->brandInput_2->show();
    ui->itemLabel_2->show();
    ui->itemInput_2->show();
    ui->categoryLabel_2->show();
    ui->categoryList_2->show();
    ui->searchButton_2->show();
    ui->cartButton->show();
    ui->amountLabel_2->show();
    ui->amountInput_2->show();
    ui->currentCartSize->hide();

    // modifies default object values
    ui->rightTopLabel->setText("                Sell Item");
    ui->nameLabel->setText("Customer Name");
    ui->nameInput->setText("");
    ui->brandInput_2->setText("");
    ui->itemInput_2->setText("");
    ui->amountInput_2->setValue(0);
    ui->categoryList_2->setCurrentRow(0);
    ui->sellItemButton->setEnabled(false);
    ui->customerInvoiceButton->setEnabled(true);
    ui->deleteInvoiceButton->setEnabled(true);
    ui->shipmentInvoiceButton->setEnabled(true);
    ui->nameLabel->move(590,190);
    ui->searchButton_2->setText("Sell");
    ui->searchButton_2->move(590,480);
}

// action for customer invoice button
void MainWindow::on_customerInvoiceButton_clicked()
{
    // hides/shows interface objects
    ui->nameLabel->hide();
    ui->nameInput->hide();
    ui->invoiceLabel->show();
    ui->invoiceInput->show();
    ui->brandLabel_2->hide();
    ui->brandInput_2->hide();
    ui->itemLabel_2->hide();
    ui->itemInput_2->hide();
    ui->categoryLabel_2->hide();
    ui->categoryList_2->hide();
    ui->searchButton_2->show();
    ui->cartButton->hide();
    ui->amountLabel_2->hide();
    ui->amountInput_2->hide();
    ui->currentCartSize->hide();

    // modifies default object values
    ui->rightTopLabel->setText("       Customer Invoice");
    ui->invoiceInput->setText("");
    ui->sellItemButton->setEnabled(true);
    ui->customerInvoiceButton->setEnabled(false);
    ui->deleteInvoiceButton->setEnabled(true);
    ui->shipmentInvoiceButton->setEnabled(true);
    ui->searchButton_2->setText("Lookup");
    ui->invoiceLabel->move(615,190);
    ui->invoiceInput->move(570,210);
    ui->searchButton_2->move(590,245);
}

// action for delete invoice button
void MainWindow::on_deleteInvoiceButton_clicked()
{
    // hides/shows interface objects
    ui->nameLabel->hide();
    ui->nameInput->hide();
    ui->invoiceLabel->show();
    ui->invoiceInput->show();
    ui->brandLabel_2->hide();
    ui->brandInput_2->hide();
    ui->itemLabel_2->hide();
    ui->itemInput_2->hide();
    ui->categoryLabel_2->hide();
    ui->categoryList_2->hide();
    ui->searchButton_2->show();
    ui->cartButton->hide();
    ui->amountLabel_2->hide();
    ui->amountInput_2->hide();
    ui->currentCartSize->hide();

    // modifies default object values
    ui->rightTopLabel->setText("          Delete Invoice");
    ui->invoiceInput->setText("");
    ui->sellItemButton->setEnabled(true);
    ui->customerInvoiceButton->setEnabled(true);
    ui->deleteInvoiceButton->setEnabled(false);
    ui->shipmentInvoiceButton->setEnabled(true);
    ui->searchButton_2->setText("Delete");
    ui->invoiceLabel->move(615,190);
    ui->invoiceInput->move(570,210);
    ui->searchButton_2->move(590,245);
}

// action for sign out button
void MainWindow::on_signoutButton_clicked()
{
    Login logOut;

    logOut.setModal(true); // sets the sign in window
    this->hide(); // hides the main menu window
    logOut.exec(); // shows the sign in window
}

// action for right hand side search action
void MainWindow::on_searchButton_2_clicked()
{
    // action for sell item
    if (ui->searchButton_2->text() == "Sell"){
        if (ui->nameInput->text() != "" && ui->brandInput_2->text() != "" && ui->itemInput_2->text() != "" && ui->amountInput_2->value() > 0){
            int count = 0;
            string invoiceId=inv.generateInvoice(cart, cartLimit, ui->nameInput->text().toStdString());
            QString ID = QString::fromStdString(invoiceId);

            // resets cart
            cartLimit = 0;
            cart = new string[10];
            ui->currentCartSize->display(1);

            QMessageBox::about(this, "Sell Item", "Item was sold Successfully!\n\nInvoice ID# " + ID);
        }
    }

    // action for customer invoice
    if (ui->searchButton_2->text() == "Lookup"){
        if (ui->invoiceInput->text() != ""){
            QString output=QString::fromStdString(inv.printInvoice(ui->invoiceInput->text().toStdString()));

            QMessageBox *msg = new QMessageBox(QMessageBox::Information, "Customer Invoice",
                                     "Customer Invoice # " + ui->invoiceInput->text() + "\n\n" + output,
                                      QMessageBox::Ok, this);
            QFont font = QFont("Courier New");
            msg->setFont(font);
            msg->setBaseSize(QSize(700, 400));
            msg->exec();
        }
    }

    // action for shipment invoice
    if (ui->searchButton_2->text() == "Receive"){
        if (ui->invoiceInput->text() != ""){
            QString firstChar = ui->invoiceInput->text().left(1);

            if (firstChar == "B") //id starts with a 'B'
            {
                ifstream temp;
                temp.open("/Users/nrabbi/Documents/QT/term_project_3112/invoices/"+ui->invoiceInput->text().toStdString()+".txt");
                if (temp.good()){
                    inv.receiveInvoice(ui->invoiceInput->text().toStdString(), ui->nameInput->text().toStdString());
                    QMessageBox::about(this, "Shipment Invoice", "Shipment Invoice # " + ui->invoiceInput->text() + "\nThe Invoice from " + ui->nameInput->text() + " has been received.");
                }
                else{
                    //file doesn't exist
                    QMessageBox::about(this, "Shipment Invoice", "Shipment Invoice # " + ui->invoiceInput->text() + " doesnt exist.");
                }
            }
            else{
                //invalid invoice
                QMessageBox::about(this, "Shipment Invoice", "Shipment Invoice # " + ui->invoiceInput->text() + " is invalid.");
            }
        }
    }

    // action for delete invoice
    if (ui->searchButton_2->text() == "Delete"){
        if (ui->invoiceInput->text() != ""){
            QString output=QString::fromStdString(inv.deleteInvoice(ui->invoiceInput->text().toStdString()));
            QMessageBox::about(this, "Delete Invoice", "Invoice # " + ui->invoiceInput->text() + "\n\n" + output);
        }
    }
}

// action for add to cart button
void MainWindow::on_cartButton_clicked()
{
    if (cartLimit < 10 && ui->amountInput_2->value() > 0){
        if (inv.lookupItem(ui->itemInput_2->text().toStdString(), ui->brandInput_2->text().toStdString(), ui->categoryList_2->currentItem()->text().toStdString())!=NULL){
            if (inv.lookupItem(ui->itemInput_2->text().toStdString(), ui->brandInput_2->text().toStdString(), ui->categoryList_2->currentItem()->text().toStdString())->getStockCount()>=ui->amountInput_2->value()){
                //add item to cart
                cart[cartLimit] = ui->brandInput_2->text().toStdString() + "," + ui->itemInput_2->text().toStdString() + "," + ui->amountInput_2->text().toStdString();
                cartLimit++;
                ui->currentCartSize->show();
                ui->currentCartSize->display(cartLimit);
            }
            else{
                //not enough stock
                QMessageBox::about(this, "Sell Item", "Error! insuffient stock.");
            }

        }
        else{
            //item does not exist
            QMessageBox::about(this, "Sell Item", "Error! item does not exist.");
        }
    }
    else{
        QMessageBox::about(this, "Sell Item", "Cart Limit Reached!");
    }
}

// action for delete stock button
void MainWindow::on_deleteStockButton_clicked()
{
    // hides/shows interface objects
    ui->brandLabel->show();
    ui->brandInput->show();
    ui->itemLabel->show();
    ui->itemInput->show();
    ui->categoryLabel->show();
    ui->categoryList->show();
    ui->searchButton->show();
    ui->amountLabel->hide();
    ui->amountInput->hide();
    ui->priceLabel->hide();
    ui->priceInput->hide();
    ui->wholesaleLabel->hide();
    ui->wholesaleInput->hide();
    ui->currentCartSize->hide();

    // modifies default object values
    ui->leftTopLabel->setText(" Delete Stock");
    ui->brandInput->setText("");
    ui->itemInput->setText("");
    ui->categoryList->setCurrentRow(0);
    ui->lookupStockButton->setEnabled(true);
    ui->addStockButton->setEnabled(true);
    ui->updateStockButton->setEnabled(true);
    ui->deleteStockButton->setEnabled(false);
    ui->searchButton->setText("Delete");
    ui->categoryLabel->move(170,245);
    ui->categoryList->move(110,265);
    ui->searchButton->move(155,320);
}

// action for shipment invoice button
void MainWindow::on_shipmentInvoiceButton_clicked()
{
    // hides/shows interface objects
    ui->nameLabel->show();
    ui->nameInput->show();
    ui->invoiceLabel->show();
    ui->invoiceInput->show();
    ui->brandLabel_2->hide();
    ui->brandInput_2->hide();
    ui->itemLabel_2->hide();
    ui->itemInput_2->hide();
    ui->categoryLabel_2->hide();
    ui->categoryList_2->hide();
    ui->searchButton_2->show();
    ui->cartButton->hide();
    ui->amountLabel_2->hide();
    ui->amountInput_2->hide();

    // modifies default object values
    ui->rightTopLabel->setText("       Shipment Invoice");
    ui->invoiceInput->setText("");
    ui->nameInput->setText("");
    ui->sellItemButton->setEnabled(true);
    ui->customerInvoiceButton->setEnabled(true);
    ui->deleteInvoiceButton->setEnabled(true);
    ui->shipmentInvoiceButton->setEnabled(false);
    ui->searchButton_2->setText("Receive");
    ui->nameLabel->setText("Supplier");
    ui->nameLabel->move(615,190);
    ui->invoiceLabel->move(615,240);
    ui->invoiceInput->move(570,260);
    ui->searchButton_2->move(590,295);
}
