#include "ShoppingCart.h"
#include <numeric>

// TODO1: Implement the addProduct method in the ShoppingCart class.
// Objective: Understand how to use std::vector to store and manage a collection of objects.
// Hints: You can directly use STL algorithm for implement.
void ShoppingCart::addProduct(const Product& product) {
    products.push_back(product);
}

// TODO2: Implement the getTotalPrice method in the ShoppingCart class.
// Objective: Understand how to use STL algorithms to operate elements from a vector.
double ShoppingCart::getTotalPrice() const {
    // double total_price = 0;
    // std::for_each(products.begin(), products.end(),
    // [&total_price](Product& product){total_price += product.price;});
    // return total_price;
    return std::accumulate(products.begin(), products.end(), 0.0,
                           [](double sum, const Product& product) {
                               return sum + product.price;
                           });

}

// TODO3: Implement the removeProduct method in the ShoppingCart class, which removes the product from cart.
// Objective: Understand how to use STL algorithms to search and remove an element from a vector.
// Hints: You can use find_if() & erase() or erase() & remove_if() for implement.
void ShoppingCart::removeProduct(const std::string& productName) {
    products.erase(std::remove_if(products.begin(), products.end(),[&productName](const Product& product) {
            return product.name == productName;
        }),products.end());
}

// TODO4.1: Implement the sortByPrice method in the ShoppingCart class.
// Objective: Understand how to use STL algorithms to sort a vector of objects based on a specific criteria.
// You can Use the std::sort algorithm to sort the products vector and define a lambda function or a functor to specify the sorting criteria based on the price member of the Product class.
void ShoppingCart::sortByPrice() {
    std::sort(products.begin(),products.end(), Product::compareByPrice);
}

// TODO4.2: Implement the sortByName method in the ShoppingCart class.
// Objective: Understand how to use STL algorithms to sort a vector of objects based on a specific criteria.
void ShoppingCart::sortByName() {
    std::sort(products.begin(),products.end(),
    [](const Product& prod1, const Product& prod2){return prod1.name < prod2.name;});
}

// TODO5: Implement the applyDiscount method in the ShoppingCart class.
// Hints: You can use std::transform.
void ShoppingCart::applyDiscount(double discountRate) {
    // std::transform(products.begin(),products.end(),
    // products.begin(),[discountRate](Product& prod){ return prod.price * (1-discountRate);});
    std::for_each(products.begin(),products.end(),[discountRate](Product& product) {
                      product.price = product.price * discountRate;
                  });
}

// TODO6: Implement the getProductsInPriceRange method in the ShoppingCart class.
std::vector<Product> ShoppingCart::getProductsInPriceRange(double minPrice, double maxPrice) {
    std::vector<Product> inRangeProducts;

    std::copy_if(products.begin(), products.end(), std::back_inserter(inRangeProducts),
                [minPrice, maxPrice](const Product& p) { return p.price >= minPrice && p.price <= maxPrice; });
    return inRangeProducts;
}

// GIVEN: Implement the getExpensiveProducts method in the ShoppingCart class.
// You should filter out expensive products (>threshold) and sort them by price;
// Hints: You can use std::copy_if algorithm and std::sort algorithm, you also need compareByPrice() and isExpensive().
std::vector<Product> ShoppingCart::getExpensiveProducts(double threshold) const {
    std::vector<Product> expensiveProducts;

    std::copy_if(products.begin(), products.end(), std::back_inserter(expensiveProducts),
                [&threshold](const Product& p) { return Product::isExpensive(p, threshold); });

    std::sort(expensiveProducts.begin(), expensiveProducts.end(), Product::compareByPrice);
    return expensiveProducts;
}
