#include <iostream>
#include <vector>
#include "ItemManager.h"
#include "Item.h"

void ItemManager::display(std::ostream& os, bool full) const {
    if(!empty()){
        for (auto& i : *this) {
            i.display(os, full);
        }
    }
}
