#include "item.h"
#include "invoice.h"
#include <fstream>
#include <algorithm>
#include <array>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>      // std::out_of_range
#include <typeinfo>
#include <sstream>
#include <iomanip>

using namespace std;

int invoiceId=30000;

/**
 * main class for the system. Holds the database of items and invoices as well as most
 * of the methods used to run the database
 * */
class Inventory
{
private:
    map<string, Item> stock;

    string dbFile;
    double profit=0.00;
    map<string, Invoice> invoices;
    string* categories;
    string* brands;
    int catIndex=0;
    int brandIndex=0;
    int catSize=0;
    int brandSize=0;
public:
    /**
     * Default constructor for Inventory
     * @param none
     * @return none
     * */
    Inventory();
    
    /**
     * Constructor for inventory. name of database file is passed to it and 
     * then read in
     * @param database - name of the database file containing all the stock and item information
     * @return none
     * */
    Inventory(string database);
    
    /**
     * Destructor for Inventory class
     * @param none
     * @return none
     * */
    ~Inventory();
    
    /**
     * Reads in the specified file and then adds items to the database. Can read in 
     * incoming invoices or main database file
     * @param filename - name of file to read in
     * @return none
     * */
    void readFile(string filename);
    
    /**
     * read in all the invoices that are listed in the invoice master file
     * @param none
     * @return none
     * */
    void readInvoices();
    
    /**
     * adds an item to the database. If the item already exists, it overwrites
     * it.
     * @param a - Item to be added to database
     * @return none
     * */
    void addItem(Item a);
    
    /**
     * Removes an amount specified by parameter of a certain item from the database and
     * then returns a pointer to a new item created with its stock set to amount and
     * the rest of the attributes the same. Used for removing items from inventory and
     * then adding subtracted amount to invoice. Returns NULL if item doesn't exist
     * or amount is greater than current stock.
     * @param brand - brand of item
     * @param name - name of item
     * @param amount - amount to be sold
     * @return pointer to new Item to be added to invoice or NULL
     * */
    Item* sellItem(string brand, string name, int amount);
    /**
     * deletes an item from the database
     * @param a - Item to be deleted
     * @return none
     * */
    void removeItem(Item a);
    
    /**
     * splits a string into a number of strings specified by num separated by commas
     * @param str - string to be split
     * @param num - num of strings after split
     * @return pointer to dynamic array of split strings
     * */
    string* split(string str, int num);
    
    /**
     * returns true if item exists, false if it doesn't. Used
     * by interfacing program to check for valid items before
     * running methods
     * @param brand, name, category - attributes of item to be searched
     * @return true if item exists in database, false otherwise
     * */
    bool exists(string brand, string name, string category);
    
    /**
     * lookups up an item in the database based on attributes and returns a pointer
     * to that item if it exists. If it doesn't exist, returns NULL. Used
     * by interfacing program to check validity of items before running operations
     * on it
     * @param name, brand, category - name, brand and category of item to be searched
     * @return pointer to item if it exists in database, NULL otherwise
     * */
    Item* lookupItem(string name, string brand, string category);
    
    /**
     * writes the database to a file. File specified in constructor
     * @param none
     * @return none
     * */
    void write();
    
    /**
     * adds a category to the dynamic array of categories
     * @param category to be added
     * @return none
     * */
    void addCategory(string category);
    
    /**
     * adds a brand to the dynamic array of brands
     * @param brand to be added
     * @return none
     * */
    void addBrand(string brand);
    
    /**
     * getter for categories array
     * @param none
     * @return dynamic array of categories
     * */
    string* getCategories(){ return categories; }
    
    /**
     * getter for brands array
     * @param none
     * @return dynamic array of brands
     * */
    string* getBrands() {return brands; }

    //void generateInvoice(vector<Item> items,string customerName);
    //void generateInvoice(string* itemNames, string* itemBrands, int* quantity, int numOfItems, string customerName);
    
    /**
     * Generates an invoice based on items' attributes passed in the items string array for the customerName
     * passed. Returns a string of the filename. Error checking for item validity occurs in the interface program
     * @param items - dynamic array of item attributes to add including name, brand and quantity. One string per item
     * @param numOfItems - number of entries in dynamic array
     * @param customerName - customer's name
     * @return string of invoice file name
     * */
    string generateInvoice(string* items, int numOfItems, string customerName);
    
    /**
     * Reads in an incoming invoice and adds the items to the database
     * @param fileName - file name of incoming invoice
     * @param supplierName - name of entity that shipped the incoming invoice
     * @return none
     * */
    void receiveInvoice(string fileName, string supplierName);
    
    /**
     * closes outgoing invoice and returns the revenue generated
     * @param id - id of invoice to close. Ensures only outgoing invoices can be closed
     * @return revenue generated from invoice
     * */
    double closeInvoice(int id);
    
    /**
     * Deletes an invoice from the database
     * @param id - filename of invoice to delete
     * @return string with message with error message if invoice doesn't exist, successful message otherwise
     * */
    string deleteInvoice(string id);
    
    /**
     * writes invoices to the master file with their filename, customer/supplier name
     * @param none
     * @return none
     * */
    void writeInvoicesToFile();
    
    /**
     * returns a string with the invoice information formatted to print out a receipt
     * @param id - filename of invoice to print
     * @return string formatted with all invoice information
     * */
    string printInvoice(string id);
    
    /**
     * checks whether an invoice exists
     * @param id of invoice to check
     * @return true if invoice exists, false otherwise
     * */
    bool invoiceExists(string id);
    
    /**
     * writes all the items to the database and invoices to their files and master files. Call when
     * program exits to save all information
     * @param none
     * @return none
     * */
    void close();
};

Inventory::Inventory()=default;


Inventory::Inventory(string database)
{
    categories=new string[10];
    brands=new string[10];
    catSize=10;
    brandSize=10;
    dbFile=database;
    readFile(database);
    readInvoices();
}

void Inventory::readInvoices()
{
    ifstream inFile;
    inFile.open("/Users/nrabbi/Documents/QT/term_project_3112/invoice_master.txt");
    string temp;
    getline(inFile,temp);
    invoiceId=atoi(temp.c_str());
    string type;
    string id;
    string customer;
    bool isOpen;
    int tempBool;
    while (getline(inFile,type,','))
    {
        getline(inFile,customer,',');
        getline(inFile,id,',');
        upcase(type);
        upcase(customer);
        upcase(id);
        inFile>>tempBool;
        inFile.ignore();
        if (tempBool!=1)
        {
            isOpen=false;
        }
        else{
            isOpen=true;
        }
        Invoice temp(id);
        temp.setCustomerName(customer);
        invoices[id]=temp;
        invoices[id].setType('B');
        if (type=="OUTGOING")
        {
            invoices[id].setType('S');
        }
        if (inFile.eof())
        {
            break;
        }

    }
    inFile.close();

}
void Inventory::readFile(string filename)
{
    ifstream inFile;
    inFile.open(filename.c_str());
    while (true)
    {
        string category;
        string brand;
        string name;


        double buy;
        double sell;
        int count;

        getline(inFile,brand,',');
        getline(inFile,name,',');
        getline(inFile,category,',');

        string temp1, temp2, temp3;
        getline(inFile,temp1,',');
        getline(inFile,temp2,',');
        getline(inFile,temp3);
        buy=atof(temp1.c_str());
        sell=atof(temp2.c_str());
        count=atoi(temp3.c_str());

        upcase(category);
        upcase(brand);
        upcase(name);
        addCategory(category);

        addBrand(brand);


        try
        {
            stock.at(brand+name);
            stock[brand+name].addStock(count);
        }
        catch (const std::out_of_range& oor)
        {
            Item pass(brand, name, category, buy, sell, count);
            stock[brand + name]=pass;
        }
        if (inFile.eof())
        {
            break;
        }

    }
    inFile.close();
}
void Inventory::addItem(Item a)
{
    stock[a.getBrand()+a.getName()]=a;
}


void Inventory::removeItem(Item a)
{
    stock.erase(a.getBrand()+a.getName());
}

bool Inventory::exists(string brand, string name, string category)
{
    try
    {
        stock.at(brand+name);
        return true;
    }
    catch (const std::out_of_range& oor)
    {
        return false;
    }
}

Item* Inventory::lookupItem(string name, string brand, string category)
{
    upcase(name);
    upcase(brand);
    upcase(category);
    try
    {
        stock.at(brand+name);
    }
    catch (const std::out_of_range& oor)
    {
        return NULL;
    }
    Item *temp=&stock[brand+name];
    if (temp->getCategory()!=category && category!="ALL")
    {
        return NULL;
    }
    return temp;

}


string* Inventory::split(string str, int size)
{
    upcase(str);
    string* temp=new string[size];
    int index=0;
    for (int x=0; x<size; x++)
    {
        index=str.find(',');
        temp[x]=str.substr(0, index);
        str=str.substr(index+1);
    }
    return temp;
}

void Inventory::write()
{
    ofstream outFile;
    outFile.open(dbFile.c_str());
    Item temp;
    for (map<string,Item>::iterator i=stock.begin(); i != stock.end(); i++)
    {
        if (i!=stock.begin())
        {
            outFile<<endl;
        }
        temp = i->second;
        outFile<<temp.getBrand()<<","<<temp.getName()<<","<<temp.getCategory()<<","<<temp.getBuyPrice()<<","<<temp.getSellPrice()<<","<<temp.getStockCount();
    }
}

Inventory::~Inventory()
{
    delete [] categories;
    delete [] brands;
}

void Inventory::addCategory(string category)
{
    bool exists=false;
    for (int i=0; i<catSize; i++)
    {
        if (categories[i]==category)
        {

            exists=true;
            break;
        }
    }
    if (!exists)
    {
        if (catIndex==catSize)
        {
            string *temp=new string[catIndex+1];
            for (int i=0; i<catSize; i++)
            {
                temp[i]=categories[i];
            }
            delete [] categories;
            categories=temp;
            catSize=catIndex+1;
        }
        categories[catIndex]=category;
        catIndex++;
    }

}
void Inventory::addBrand(string brand)
{
    bool exists=false;
    for (int i=0; i<brandSize; i++)
    {
        if (brands[i]==brand)
        {
            exists=true;
        }
    }
    if (!exists)
    {
        if (brandIndex==brandSize)
        {
            int num=brandIndex++;
            string *temp=new string[brandIndex+1];
            for (int i=0; i<brandSize; i++)
            {

                temp[i]=brands[i];
            }
            delete [] brands;
            brands=temp;
            brandSize=brandIndex+1;
        }
        brands[brandIndex]=brand;
        brandIndex++;
    }


}


string Inventory::generateInvoice(string* items, int numOfItems, string customerName)
{
    Invoice invoice("S"+to_string(invoiceId),customerName);
    invoiceId++;
    for (int x=0; x<numOfItems; x++)
    {
        string *temp=split(items[x],3);
        if (exists(temp[0],temp[1],"ALL")){
            invoice.addItem(*sellItem(temp[0],temp[1],atoi(temp[2].c_str())));
        }


    }
    invoices[invoice.getFileName()]=invoice;
    invoice.write();
    writeInvoicesToFile();
    return invoice.getFileName();
}

Item* Inventory::sellItem(string brand, string name, int amount)
{
    Item* temp=lookupItem(name,brand,"all");
    if (temp==NULL)
    {
        return NULL;
    }
    /* handle in user interface */
    if (amount > temp->getStockCount()){
        return NULL;
    }

    Item *returnValue=new Item(brand,name,temp->getCategory(),temp->getBuyPrice(),temp->getSellPrice(),amount);
    temp->removeStock(amount);
    return returnValue;

}

string Inventory::printInvoice(string id)
{
    int spacing=24;
    time_t now = time(0);
   
   // convert now to string form
    string dt = ctime(&now);
    dt=dt.substr(0,dt.length()-1);

    try
    {
        invoices.at(id);
        dt=dt+"\t"+id+"\t\t\t"+invoices[id].getCustomerName()+"\n";
        string output="Item";
        for (int x=0; x<(spacing-4)/2; x++){
            output=" "+output;
            output+=" ";
        }
        output+= " Quantity  Cost Per Item   Total for Item\n";
        vector<Item> temp=invoices[id].getItems();
        stringstream stream2;
        int format;
        for (int i=0; i<temp.size(); i++)
        {
            string nextLine=temp[i].getBrand() + " " + temp[i].getName();
            format=nextLine.length();
            if (format>spacing)
            {
                format-=spacing;
            }
            else{
                format=spacing-format;
                for (int x=0; x<(format/2)+format%2; x++)
                {
                    nextLine=" "+nextLine;
                }
                for (int x=0; x<(format/2); x++)
                {
                    nextLine+=" ";
                }
                format=0;
            }
            nextLine+=" ";
            for (int x=format; x<3; x++)
            {
                nextLine+=" ";
            }
            format=0;
            nextLine+=to_string(temp[i].getStockCount());
            if (temp[i].getStockCount()>100){
                format=-1;
            }
            else if (temp[i].getStockCount()<10){
                format=1;
            }
            for (int x=0; x<8+format; x++)
            {
                nextLine+=" ";
            }
            double price=0;
            if (id[0]=='B')
            {
                price=temp[i].getBuyPrice();
            }
            else
            {
                price=temp[i].getSellPrice();
            }
            stringstream stream;
            stream << fixed << setprecision(2) << price;
            string s = stream.str();
            format=("$"+s).length();
            nextLine+="$"+s;
            for (int x=format; x<7; x++){
                nextLine+=" ";
            }
            if (format<=7){
                format=0;
            }
            else{
                format-=7;
            }
            for (int x=0; x<9-format;x++)
            {
                nextLine+=" ";
            }


            double total=price*temp[i].getStockCount();
            stream2 << fixed << setprecision(2) << total;
            string totalStr=stream2.str();
            nextLine+="$"+totalStr;
            output+=nextLine+"\n";
            stream2.str(string());
            stream2.clear();

        }

        stream2<<fixed<<setprecision(2)<<invoices[id].totalPrice();
        format=stream2.str().length();
        output+="\n\t\t\t\t      Total Price: ";
        for (int x=format; x<11; x++)
        {
            output+=" ";
        }
        output+="$"+stream2.str();
        output=dt+output;
        return output;

    }
    catch (const std::out_of_range& oor)
    {
        return "That invoice number does not exist";
    }
}

bool Inventory::invoiceExists(string id)
{
    try{
        invoices.at(id);
        return true;
    }
    catch (const std::out_of_range& oor)
    {
        cout<<"exists not working"<<endl;
        return false;
    }
}

double Inventory::closeInvoice(int id)
{
    invoices["S"+to_string(id)].setBool(false);
}

string Inventory::deleteInvoice(string id)
{
    if(invoices.erase(id)==1){
        remove(("/Users/nrabbi/Documents/QT/term_project_3112/invoices/"+id+".txt").c_str());
        return "Invoice successfully removed!";
    }
    else
    {
        return "Invoice not found in database!";
    }
    writeInvoicesToFile();
}

void Inventory::receiveInvoice(string filename, string supplierName)
{
   
   try
   {
       invoices.at(filename);
   }
   catch(const std::out_of_range& oor)
   {
       readFile("/Users/nrabbi/Documents/QT/term_project_3112/invoices/"+filename+".txt");
       Invoice temp(filename);
       temp.setCustomerName(supplierName);
       temp.setBool(false);
       invoices[filename]=temp;
       profit-=temp.totalPrice();
       writeInvoicesToFile();
   }
}

void Inventory::writeInvoicesToFile()
{
    ofstream outFile;
    outFile.open("/Users/nrabbi/Documents/QT/term_project_3112/invoice_master.txt");
    outFile<<invoiceId;
    if (!invoices.empty())
    {
        outFile<<endl;
    }
    for (map<string,Invoice>::iterator i=invoices.begin(); i != invoices.end(); i++)
    {
        Invoice temp;
        if (i!=invoices.begin())
        {
            outFile<<endl;
        }
        temp =i -> second;
        string type;
        type = "INCOMING";
        if (temp.getType()=='S')
        {
            type = "OUTGOING";
        }
        outFile<<type<<","<<temp.getCustomerName()<<","<<temp.getFileName()<<","<<temp.getBool();
    }
    outFile.close();
}

void Inventory::close()
{
    write();
    writeInvoicesToFile();
}
