#include <iostream>
#include <vector>
#include <algorithm>
#include "Task.h"
#include "TaskManager.h"
#include "ItemManager.h"
#include "Item.h"

void TaskManager::validate(std::ostream& cerr) {
	for (size_t this_task = 0; this_task < size(); this_task++) {
		bool validated = false;
		for (size_t other_task = 0; other_task < size() && !validated; other_task++) {
			if (this->at(this_task).getName() != this->at(other_task).getName()) {
				//for readability..
				validated = this->at(this_task).validate(this->at(other_task));
			}
		}
		if (!validated) {
			cerr << "The task " << this->at(this_task).getName() << " is not validated." << std::endl;
		}
	}
}

void TaskManager::validate(const ItemManager& im, std::ostream& cerr) {
	
	//OUTER LOOP, iterate each item in our inventory list.
	for (auto this_item = im.begin(); this_item != im.end(); this_item++) {
		//INNER LOOP, for every item, iterate through the task list, to check
		//if the item's installer task is in the task list.
		auto filler_found = std::find_if(begin(), end(), [this_item](Task t) {
			if (this_item->getFiller() == t.getName()) {
				return true;
			}
			return false;
		});	
		if (filler_found == end()) {
			cerr << this_item->getFiller() << " is unavailable" << std::endl;
		}
		//AND THEN THE SAME LOOP TO FIND REMOVER...
		auto remover_found = std::find_if(begin(), end(), [this_item](Task t) {
			if (this_item->getRemover() == t.getName()) {
				return true;
			}
			return false;
		});
		if (remover_found == end()) {
			cerr << this_item->getRemover() << " is unavailable" << std::endl;
		}
	}
}

void TaskManager::display(std::ostream& os) const {
	for (auto& t : *this) {
		t.display(os);
	}
}

