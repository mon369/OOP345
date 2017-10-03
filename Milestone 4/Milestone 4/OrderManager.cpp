#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "OrderManager.h"
#include "ItemManager.h"
#include "Item.h"
#include "CustomerOrder.h"

CustomerOrder&& OrderManager::extract() {
    std::unique_ptr<CustomerOrder> order(new CustomerOrder(std::move(back())));
	return std::move(*order);
}


void OrderManager::validate(const ItemManager& im, std::ostream& cerr) {
	//OUTER LOOP, Looping through each Customer Order
	for (auto &co : *this) {
		//INNER LOOP, Looping through each item the current customer ordered.
		for (unsigned int ci = 0; ci < co.noOrders(); ci++) {
			std::string customer_item = co[ci];
			//INNER INNER Loop, Looping through the items inventory to see if the item ordered
			//by the customer is available and in stock.
			auto item_found = std::find_if(im.begin(), im.end(), [customer_item] (Item item) {
				if (customer_item == item.getName()) {
					return true;
				}
				return false;
			});
			if (item_found == im.end()) {
				cerr << customer_item << " is unavailable" << std::endl;
			}
		}
	}
}

void OrderManager::display(std::ostream& os) const {
	if(!empty()){
        for (auto& co : *this) {
            co.display(os);
        }
	}
}
