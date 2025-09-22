#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>

using namespace std;
//extension: discount
struct Discount {
    string type;   // "flat" or "percentage"
    float value;   // 50 for flat | 0.10 for 10%
};

//Product class
class Product {
    private:
        string name;
        double price;
        int quantity;
    public:
        Product(string n, double p, int q) : name(n), price(p), quantity(q) {}
        
        string getName() const {
            return name;
        }
        
        double getPrice() const {
            return price;
        }
        
        int getQuantity() const {
            return quantity;
        }
        
        void setQuantity(int q) {
            quantity = q;
        }

        float getTotalPrice() const {
            return (price * quantity);
        }

};

// Cart class
class Cart{
    private:
        vector<Product> products;
    public:
        unordered_map<string, Discount> discountCodes = {
            {"SAVE10", {"percentage", 0.10}},
            {"WELCOME5", {"percentage", 0.05}},
            {"FREESHIP", {"flat", 50.00}}
        };
        void addProduct(const Product& p){
            products.push_back(p);
        }

        float calculateTotal() const {
            float total = 0.0;
            for(auto& product : products){
                total += product.getTotalPrice();
            }
            return total;
        }

        void displayCart() const {
            cout << "===========================" << endl;
            cout << "Cart Items:" << endl;
            for(auto const& product : products){
                cout << "Product Name: " << product.getName() << endl;
                cout << "Price: $" << product.getPrice() << endl;
                cout << "Quantity: " << product.getQuantity() << endl;
                cout << "Total Price: $" << product.getTotalPrice() << endl;
                cout << "---------------------------" << endl;
            }
            cout << "Total Amount: $" << calculateTotal() << endl;
            cout << "===========================" << endl;
        }

        void clearCart() {
            products.clear();
        }

};

// Credit card class
class CreditCard{
    private:
        string cardNumber;
        string cardHolderName;
        float balance;
    public:
        CreditCard(string number, string holderName, float bal) 
            : cardNumber(number), cardHolderName(holderName), balance(bal) {}

        string getCardNumber() const {
            return cardNumber;
        }

        string getCardHolderName() const {
            return cardHolderName;
        }

        float getBalance() const {
            return balance;
        }

        void setBalance(float bal) {
            balance = bal;
        }

        bool charge(float amount){
            if(amount <= balance){
                balance -= amount;
                return true;
            }
            else {
                cout << "Insufficient balance!" << endl;
                return false;
            }
        }

        //validate card number -> Luhn's algorithm
        bool validate() const {
            int sum = 0; 
            bool doubleDigit = false;
            for(int i = cardNumber.length() - 1; i >= 0; i--){
                int digit = cardNumber[i] - '0';
                if(doubleDigit) {
                    digit *= 2;
                    if(digit > 9) {
                        digit -= 9;
                    }
                }
                else{
                    digit = digit;
                }
                sum += digit;
                doubleDigit = !doubleDigit;
            }
            return (sum % 10 == 0);
        }
};


int main(int argc, char *argv[]) {
    //bank database of credit cards
    vector<CreditCard> bank_db = {
        CreditCard("4111111111111111", "Ali", 5000),       // Visa ✅
        CreditCard("4012888888881881", "Sara", 3000),      // Visa ✅
        CreditCard("6011111111111117", "Hamza", 7000),     // Discover ✅
        CreditCard("378282246310005", "Ayesha", 9000),     // Amex ✅
        CreditCard("5105105105105100", "Fatima", 4000)     // MasterCard ✅
    };


    //inventory of products
    unordered_map<string, double> inventory = {
        // Grocery Essentials
        {"Rice (5kg)", 1200},
        {"Wheat Flour (10kg)", 1800},
        {"Sugar (1kg)", 180},
        {"Salt (1kg)", 80},
        {"Cooking Oil (1L)", 550},
        {"Ghee (1kg)", 720},
        {"Tea (500g)", 550},
        {"Milk (1L)", 220},
        {"Eggs (Dozen)", 360},
        {"Bread (Large)", 180},

        // Personal Care
        {"Shampoo (400ml)", 500},
        {"Soap (Pack of 3)", 150},
        {"Toothpaste (150g)", 300},
        {"Toothbrush", 120},
        {"Hand Sanitizer (100ml)", 250},
        {"Face Wash (200ml)", 480},
        {"Lotion (300ml)", 650},
        {"Deodorant", 400},

        // Household Items
        {"Detergent (1kg)", 800},
        {"Dishwashing Liquid (500ml)", 350},
        {"Floor Cleaner (1L)", 450},
        {"Tissue Roll (Pack of 10)", 300},
        {"Garbage Bags (Large Pack)", 400},
        {"Mosquito Spray", 550},
        {"Matchbox", 20},

        // Snacks & Beverages
        {"Chips (Large Pack)", 200},
        {"Biscuits (Pack)", 180},
        {"Chocolate Bar", 250},
        {"Juice (1L)", 300},
        {"Soft Drink (1.5L)", 280},
        {"Energy Drink", 350},
        {"Popcorn (Microwave Pack)", 180},

        // Frozen Foods
        {"Frozen Paratha (Pack of 20)", 850},
        {"Frozen Nuggets (1kg)", 1200},
        {"Frozen French Fries (1kg)", 900},
        {"Ice Cream Tub (1L)", 700},

        // Fruits & Vegetables (Fixed prices for simulation)
        {"Bananas (Dozen)", 200},
        {"Apples (1kg)", 350},
        {"Oranges (1kg)", 300},
        {"Potatoes (1kg)", 150},
        {"Onions (1kg)", 180},
        {"Tomatoes (1kg)", 200},
        {"Cucumber (1kg)", 120},
        {"Carrots (1kg)", 170},

        // Baby Products
        {"Diapers (Pack of 40)", 2400},
        {"Baby Wipes (Pack of 80)", 600},
        {"Baby Powder", 450},

        // Health & Medicine (Basic simulation)
        {"Panadol (Pack of 20)", 70},
        {"Bandages (Pack of 10)", 120},
        {"Thermometer", 850}
    };


    cout << "============ Welcome to Imtiaz Billing System ============" << endl;
    cout << endl;
    cout << "Available Products:" << endl;
    for(const auto& item : inventory) {
        cout << item.first << " - $" << item.second << endl;
    }
    Cart cart;
    while(true){
        cout << "MENU:\nPress the preceding number to select an option:" << endl;
        cout << "1. Add Product to Cart" << endl;
        cout << "2. View Cart" << endl;
        cout << "3. Checkout" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
        if(choice == 4) {
            cout << "Thank you for using Imtiaz Billing System!" << endl;
            break;
        }
        else if(choice == 1){
            string pName;
            int pQuantity;
            cout << "Enter Product Name: ";
            getline(cin, pName);
            cout << "Enter Quantity: ";
            cin >> pQuantity;
            cin.ignore(); // Clear the newline character from the input buffer
            if(inventory.find(pName) != inventory.end() && pQuantity > 0){
                double price = inventory[pName];
                Product p(pName, price, pQuantity);
                cart.addProduct(p);
                cout << "Product added to cart!" << endl;
            }
            else{
                cout << "Invalid product name or quantity!" << endl;
            }
        }
        else if(choice == 2){
            if(cart.calculateTotal() > 0){
                cart.displayCart();
            } 
            else{
                cout << "Your cart is empty!" << endl;
            }
        }
        else if(choice == 3){
            if(cart.calculateTotal() > 0){
                cart.displayCart();

                string creditCardNo, cardHolderName;
                cout << "Enter Credit Card Number: ";
                getline(cin, creditCardNo);
                cout << "Enter Card Holder Name: ";
                getline(cin, cardHolderName);

                // Validate card number using Luhn's algorithm
                CreditCard tempCard(creditCardNo, cardHolderName, 0);
                if(!tempCard.validate()){
                    cout << "Invalid card number (Luhn check failed)!" << endl;
                    continue;
                }

                bool cardFound = false;

                for(auto& bankCard : bank_db){
                    if(bankCard.getCardNumber() == creditCardNo && bankCard.getCardHolderName() == cardHolderName){
                        cardFound = true;
                        float totalAmount = cart.calculateTotal();

                        // Handle Discount
                        string discountCode;
                        cout << "Enter Discount Code (or press Enter to skip): ";
                        getline(cin, discountCode);
                        if(!discountCode.empty()){
                            auto it = cart.discountCodes.find(discountCode);
                            if(it != cart.discountCodes.end()){
                                Discount d = it->second;
                                if(d.type == "flat"){
                                    totalAmount -= d.value;
                                }
                                else if(d.type == "percentage"){
                                    totalAmount -= totalAmount * d.value;
                                }
                                cout << "Discount Applied! New Total: $" << totalAmount << endl;
                            }
                            else{
                                cout << "Invalid Discount Code! No discount applied." << endl;
                            }
                        }

                        // Check balance and charge
                        if(bankCard.charge(totalAmount)){
                            cout << "Payment successful! Your order has been placed." << endl;
                            cart.clearCart(); // Clear the cart after successful payment
                            cout << "Thank you for shopping with us!" << endl;
                        }
                        else{
                            cout << "Payment failed due to insufficient balance!" << endl;
                        }

                        break; // Card found, exit loop
                    }
                }

                if(!cardFound){
                    cout << "Card not found in our system!" << endl;
                }

            }
            else{
                cout << "Your cart is empty!" << endl;
            }
        }

        else{
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}
