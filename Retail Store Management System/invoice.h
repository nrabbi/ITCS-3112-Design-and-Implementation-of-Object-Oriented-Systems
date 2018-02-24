#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>

/**
 * class to store a date value
 * */
class Date{
        int year;
        int month;
        int day;
        string months[12]={ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    public:
        /**
         * Date constructor
         * @param m, d, y - integers representing month, day and year respectively
         * @return none
         * */
        Date(int m, int d, int y);
        
        /**
         * overrided output operator to ouptut customized date
         * @param os - passed by system during output (cout, outputfile, etc.)
         * @param date - date object to be printed
         * @return returns an ofstream containing customized output
         * */
        friend ostream& operator<<(ostream& os, Date date);
};

Date::Date(int m, int d, int y)
{
    month=m;
    day=d;
    year=y;
}

ostream& operator<< (ostream& os, Date date)
{
    os << date.month<< "/"<<date.day<<"/"<<date.year;
    return os;
}


/**
 * Invoice class to hold orders, both outgoing and incoming, and the name of their
 * respective files
 * */
class Invoice{
    private:
        string prefix="/Users/nrabbi/Documents/QT/term_project_3112/invoices/";
        vector<Item> items;
        char type='S';
        int id;
        bool open=true;
        string InvoiceFile;
        string customerName;
    public:
        /**
         * Default constructor
         * @param none
         * @return none
         * */
        Invoice()=default;
        
        /** 
         * Invoice constructor. initializes an invoice with an id and customer
         * name but no items
         * @param file - name of the file where this invoice will be stored (string of one character 
         * followed by an integer)
         * @param name - name of the customer
         * @return none
         * */
        Invoice(string file, string name)
        {
            upcase(file);
            type=file[0];
            id=stoi(file.substr(1));
            InvoiceFile=file;
            customerName=name;
            if (type!='B')
            {
                type='S';
            }
        }
        
        /**
         * Invoice constructor. Reads in already created invoice file and stores all the data associated with it
         * @param completeFile - name of invoice file to be read in
         * @return none
         * */
        Invoice(string completeFile)
        {
            ifstream inFile;
            inFile.open((prefix+completeFile+".txt").c_str());
            string brand;
            type=completeFile[0];
            if (type!='B')
            {
                type='S';
            }
            id=stoi(completeFile.substr(1));
            InvoiceFile=completeFile;

            while (getline(inFile,brand,',')){
                string category;
                string name;

                double buy;
                double sell;
                int count;

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
                Item pass(brand, name, category, buy, sell, count);
                items.emplace_back(pass);
                if (inFile.eof())
                {
                    break;
                }
            }
        }
        
        /** getter for items vector
         * @param none
         * @return items - a vector of all items on this invoice
         * */
        vector<Item> getItems()
        {
            return items;
        }
        
        
        /** setter for items vector
         * @param items - a vector of all items to be put on this invoice
         * @return none
         * */
        void setItems(vector<Item> items)
        {
            this -> items=items;
        }
        /**
         * getter for type
         * @param none
         * @return type of invoice (B for incoming, S for outgoing)
         * */
        char getType()
        {
            return type;
        }
        /**
         * setter for type
         * @param a - char of type to be set (must be B or S; default to S if invalid choice)
         * @return none
         * */
        void setType(char a)
        {
            type=a;
            if (type!='B')
            {
                type='S';
            }
        }
        /**
         * setter for open
         * @param a
         * @return
         * */
        void setBool(bool a)
        {
            open=a;
        }
        /**
         * getter for open
         * @param none
         * @return open
         * */
        bool getBool()
        {
            return open;
        }
        /**
         * getter for invoiceFile
         * @param none
         * @return InvoiceFile
         * */
        string getFileName()
        {
            return InvoiceFile;
        }
        /**
         * setter for InvoiceFile
         * @param file
         * @return none
         * */
        void setFileName(string file)
        {
            InvoiceFile=file;
        }
        /**
         * getter for customer name
         * @param none
         * @return none
         * */
        string getCustomerName()
        {
            return customerName;
        }
        /**
         * setter for customer name
         * @param name
         * @return none
         * */
        void setCustomerName(string name)
        {
            upcase(name);
            customerName=name;
        }
        
        /**
         * getter for id
         * @param none
         * @return id
         * */
        int getId(){ return id; }
        /**
         * setter for id
         * @param id
         * @return none
         * */
        void setId(int id){ this->id=id; }

        /** adds an item to the invoice by emplacing it in the vector of items
         * @param a - Item to be added
         * @return none
         * */
        void addItem(Item a)
        {
            items.emplace_back(a);
        }
        
        /** removes an item from the invoice
         * @param a - Item to be remove
         * @return none
         * */
        void removeItem(Item a)
        {
            for (vector<Item>::iterator i=items.begin(); i!=items.end(); i++)
            {
                if (*i==a)
                {
                    items.erase(i);
                }
            }
        }
    
        /**
         * calculates the total price based off of type of invoice (retail price for outgoing, wholesale
         * for incoming) and returns the value
         * @param none
         * @return total price based off of type
         * */
        double totalPrice()
        {
            double total=0;
            for (vector<Item>::iterator i=items.begin(); i!=items.end(); i++)
            {
                if (type=='B')
                {
                    total+=i->getBuyPrice()*i->getStockCount();
                }
                else{
                    total+=i->getSellPrice()*i->getStockCount();
                }
            }
            return total;
        }
        
        /** writes the invoice data to the file specified
         * @param none
         * @return none
         * */
        void write()
        {
            ofstream outFile;
            outFile.open((prefix+InvoiceFile+".txt").c_str());
            for (int i=0; i<items.size(); i++)
            {
                if (i!=0)
                {
                    outFile<<endl;
                }
                outFile<<items[i].getBrand()<<","<<items[i].getName()<<","<<items[i].getCategory()<<","<<items[i].getBuyPrice()<<","<<items[i].getSellPrice()<<","<<items[i].getStockCount();
            }
            outFile.close();
        }




};

