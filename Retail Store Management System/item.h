#include <string>

using namespace std;

/**
 * Capitalizes all letters in the passed string
 * @param value, a string to be upcased
 * @return none
 * */
void upcase(string& value)
{
    for (int i=0; i<value.length(); i++)
    {
        if (value[i]>='a' && value[i]<='z')
        {
            value[i]-=32;
        }
    }
}
/**
 * An Item class. Holds information for individual items such as retail and wholesale price, stock,
 * name, brand and category
 * */
class Item
{
    private:
        string name;
        string brand;
        double buyPrice;
        double sellPrice;
        int stockCount;
        string category;

    public:
        /**
         * Default constructor for Item class
         * @param none
         * @return none
         * */
        Item();
        /**
         * Constructor for the Item class that initializes all values
         * @param brand - a string of the item's brand
         * @param name - a string of the item's name
         * @param category - a string of the item's category
         * @param buy - a double with the wholesale price (buying price)
         * @param sell - a double with the retail price (selling price)
         * @param count - an integer with the amount of stock
         * @return none
         * */
        Item(string brand, string name, string category, double buy, double sell, int count);
        
        /**
         * Compares this item with a passed item to check for equality
         * @param a - Item to be compared with this class
         * @return true if equivalent, false otherwise
         * */
        bool equals(Item a);
        
        /**
         * Overrides the == operator for Item class
         * @param a - Item to be compared with current class
         * @return true if equivalent, false otherwise
         * */
        bool operator==(Item a);
        
        /**
         * decrements stock count by x and returns the total sell price
         * @param x - number of items to sell
         * @return retail price of x items
         * */
        double sellX(int x); ///
        
        /**
         * increments stock count by x and returns the total buy price
         * @param x - number of items to sell
         * @return wholesale price of x items
         * */
        double buyX(int x);
        
        /**
         * increments stock count by amount passed
         * @param count - number to be added to stock count
         * @return none
         * */
        void addStock(int count);
        
        /**
         * dencrements stock count by amount passed
         * @param count - number to be removed from stock count
         * @return none
         * */
        void removeStock(int count);
        
        /**
         * setter for stockcount
         * @param stockCount
         * @return none
         * */
        void setStockCount(int stockCount);
        
        /**
         * getter for stock count
         * @param none
         * @return stockcount
         * */
        int getStockCount();

        
        /** setter for buy price
         * @param buyPrice
         * @return none
         * */
        void setBuyPrice(double buyPrice);
        
        /**
         * getter for buy price
         * @param none
         * @return buyPrice
         * */
        double getBuyPrice();
        
        /** setter for sellPrice
         * @param sellPrice
         * @return none
         * */
        void setSellPrice(double sellPrice);
        
        /**
         * getter for sellPrice
         * @param none
         * @return sellPrice
         * */
        double getSellPrice();
        
        /** setter for name
         * @param name
         * @return none
         * */
        void setName(string name);
        
        /**
         * getter for name
         * @param none
         * @return name
         * */
        string getName() const;
        
        /** setter for brand
         * @param brand
         * @return none
         * */
        void setBrand(string brand);
        
        /**
         * getter for brand
         * @param none
         * @return brand
         * */
        string getBrand () const;
        
        /** setter for category
         * @param category
         * @return none
         * */
        void setCategory(string category);
        
        /**
         * getter for category
         * @param none
         * @return category
         * */
        string getCategory() const;

        

};



Item::Item()
{
    buyPrice=0;
    sellPrice=0;
    stockCount=0;
}

Item::Item(string brand, string name, string category,  double buy, double sell, int count)
{
    upcase(name);
    upcase(brand);
    upcase(category);
    this->name=name;
    this -> brand = brand;
    this -> category = category;
    buyPrice=buy;
    sellPrice=sell;
    stockCount=count;
}

bool Item::equals(Item a)
{
    if (a.getName()==this->name && a.getBrand()==brand )
    {
        return true;
    }
    return false;
}

bool Item::operator==(Item a)
{
    if (a.getName()==this->name && a.getBrand()==this -> brand )
    {
        return true;
    }
    return false;
}

double Item::sellX(int x)
{
    stockCount-=x;
    return (sellPrice*x);
}

double Item::buyX(int x)
{
    stockCount+=x;
    return (buyPrice*x);
}

void Item::setStockCount(int stockCount) { this->stockCount = stockCount; }
void Item::addStock(int count) {this ->stockCount+=count; }
void Item::removeStock(int count) {this -> stockCount-=count; }
int Item::getStockCount() { return this->stockCount; }

void Item::setBuyPrice(double buyPrice) { this->buyPrice = buyPrice; }
double Item::getBuyPrice() { return this->buyPrice; }

void Item::setSellPrice(double sellPrice) { this->sellPrice = sellPrice; }
double Item::getSellPrice() { return this->sellPrice; }

void Item::setCategory(string category) { this->category = category; }
string Item::getCategory() const { return this->category; }

void Item::setName(string name) {this->name=name; }
string Item::getName() const {return name;}

void Item::setBrand(string brand) { this->brand = brand; }
string Item::getBrand() const { return this->brand; }
